/**
 * Copyright (C) 2020 Chocolata Printer oficial software, All right reserved.
 *
 * Autors: Abernihin Ilia & Velichko Bohdan
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided
 * that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this list of conditions and
 * the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
 * the following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Abstract:
 */

#ifndef VERTEXCLOUD_HPP
#define VERTEXCLOUD_HPP

#include <map>
#include <list>
#include <vector>
#include <algorithm>

#include "ChocolataSlicerMesh.h"
#include "ContentTree.h"

namespace Slicer
{
  using height      = float;
  using layerPoint  = Geometry::Point2d;
  using closeFlag   = bool;
  using closedCurve = std::list <       layerPoint       >;     // or circular linked list (need impliment)
  using curve       = std::pair < closeFlag, closedCurve >;
  using layer       = std::list <         curve          >;
  using vertexCloud = std::map  <      height, layer     >;
  using tempLayer   = std::list <     Geometry::cut_t    >;



  namespace
  {
      void
      generateStaticLayerHeight(vertexCloud& cloud, const float gabarits) noexcept
      {
          const float layerh = *cfg::get<f>(CfgNames::LAYER);
          while(cloud.rbegin() -> first < gabarits - layerh)
                cloud.emplace ( std::make_pair ( layerh, layer() ) );
      }

      void
      generateDynamicLayerHeight(vertexCloud& cloud, const float gabarits) noexcept
      {
          float max = *cfg::get<f>(CfgNames::MAX_LAYER);

          while(cloud.rbegin() -> first < gabarits - max)
          {
              float layerHeight = cloud.rbegin() -> first + max;
              std::for_each
              (
                  ContentTree::getInstance()._items.cbegin(),
                  ContentTree::getInstance()._items.cend(),
                  [&cloud, &layerHeight] (auto item) mutable -> void
                  {
                      if (!item -> _meshPtr -> _sliced)
                      {
                          if (auto layHeigh = item -> _meshPtr
                              -> nextLayerHeight(cloud.rbegin() -> first);
                          layHeigh) { if (layerHeight >= *layHeigh ) layerHeight = *layHeigh; }
                          else item -> _meshPtr -> _sliced = true;
                      }
                  }
              );
              cloud.emplace ( std::make_pair ( layerHeight, layer() ) );
          }
          if (gabarits - cloud.rbegin()->first > *cfg::get<f>(CfgNames::MIN_LAYER)) cloud.emplace
             (
               std::make_pair
               (
                   gabarits,
                   layer()
               )
             );
      }

      inline bool isClosed(const closedCurve& curve) noexcept
      { return *curve.begin() == *curve.rbegin(); }

      bool allClosed(const layer& lay) noexcept
      { bool res = true; for(auto [close, curve] : lay) !close ? res = false : res; return res; }
      //
      bool onLine(const layerPoint& first, const layerPoint& second, const layerPoint& third) noexcept
      { return Geometry::is_equal((third.x - first.x) * (second.y - first.y), (third.y - first.y) * (second.x - first.x)); }

      void validate(tempLayer& tmp, layer& arr) noexcept
      {
          bool inserted = 0;

          if (tmp.empty()) return;

          if (auto& point = *tmp.begin(); arr.empty() || allClosed(arr))
          {
               if (point)
               {
                   if (point -> first)
                   {
                       arr.emplace_back(curve(false, closedCurve({*point -> first})));
                       if (point -> second) arr.rbegin()->second.emplace_back(*point -> second);
                   }
                   if (point -> second) arr.emplace_back(curve(false, closedCurve({*point -> second})));
               }
               tmp.erase(tmp.begin());
          }
          else
          {
              for(auto& [closed, curve] : arr)
              {
                  if (closed) continue;
                  if(curve.size() == 1)
                  {
                      for (auto pi = tmp.cbegin(); pi != tmp.cend(); ++pi)
                      {
                          auto& point = *pi;

                          if (point)
                          {
                              if(point -> first) if (*point -> first == *curve.crbegin())
                              { if(point -> second) curve.emplace_back(*point -> second); inserted = true; }

                              if(point -> second) if (*point -> second == *curve.crbegin())
                              { if(point -> first) curve.emplace_back(*point -> first); inserted = true; }
                          }
                          if (inserted) {tmp.erase(pi); break;}
                      }
                  }
                  else for (auto pi = tmp.cbegin(); pi != tmp.cend(); ++pi)
                  // else for (auto& point : tmp)
                  {
                      auto& point = *pi;
                      if (point)
                      {
                          if (point -> first)
                          {
                              if (*point -> first == *curve.crbegin())
                              {
                                    if(point -> second)
                                    {
                                        if (*point -> second == *curve.cbegin())
                                        {
                                            if (onLine(*curve.crbegin(), *curve.cbegin(), *++curve.cbegin()))
                                                curve.erase(curve.begin());

                                            if (onLine(*curve.crbegin(), *++curve.crbegin(), *curve.cbegin()))
                                                curve.pop_back();

                                            closed = true;
                                            inserted = true;
                                        }

                                        if (!inserted) onLine(*curve.crbegin(), *++curve.crbegin(), *point -> second)
                                            ? *curve.rbegin() = *point -> second
                                            : curve.emplace_back(*point -> second);
                                    }
                                    inserted = true;
                              }

                              if (!inserted)
                                 if (*point -> first == *curve.cbegin())
                                 {
                                    if(point -> second)
                                    {
                                        if (*point -> second == *curve.crbegin())
                                        {
                                            if (onLine(*curve.crbegin(), *curve.cbegin(), *++curve.cbegin()))
                                                curve.erase(curve.begin());

                                            if (onLine(*curve.crbegin(), *++curve.crbegin(), *curve.cbegin()))
                                                curve.pop_back();

                                            closed = true;
                                            inserted = true;
                                        }

                                        if (!inserted) onLine(*curve.cbegin(), *++curve.cbegin(), *point -> second)
                                            ? *curve.begin() = *point -> second
                                            : curve.emplace_front(*point -> second);
                                    }
                                    inserted = true;
                                 }
                          }

                          if (point -> second)
                          {
                              if (*point -> second == *curve.crbegin())
                              {
                                    if(point -> first)
                                    {
                                        if (*point -> first == *curve.cbegin())
                                        {
                                            if (onLine(*curve.crbegin(), *curve.cbegin(), *++curve.cbegin()))
                                                curve.erase(curve.begin());

                                            if (onLine(*curve.crbegin(), *++curve.crbegin(), *curve.cbegin()))
                                                curve.pop_back();

                                            closed = true;
                                            inserted = true;
                                        }

                                        if (!inserted) onLine(*curve.crbegin(), *++curve.crbegin(), *point -> first)
                                            ? *curve.rbegin() = *point -> first
                                            : curve.emplace_back(*point -> first);
                                    }
                                    inserted = true;
                              }

                              if (!inserted)
                                 if (*point -> second == *curve.cbegin())
                                 {
                                    if(point -> first)
                                    {
                                        if (*point -> first == *curve.crbegin())
                                        {
                                            if (onLine(*curve.crbegin(), *curve.cbegin(), *++curve.cbegin()))
                                                curve.pop_back();

                                            if (onLine(*curve.crbegin(), *++curve.crbegin(), *curve.cbegin()))
                                                curve.pop_back();

                                            closed = true;
                                            inserted = true;
                                        }

                                        if (!inserted) onLine(*curve.cbegin(), *++curve.cbegin(), *point -> first)
                                            ? *curve.begin() = *point -> first
                                            : curve.emplace_front(*point -> first);
                                    }
                                    inserted = true;
                                 }
                          }
                      }
                      if (inserted) {tmp.erase(pi); break;}
                  }
                  if(inserted) validate(tmp, arr);
              }
          }
      }
};


  void
  generateVertexCloud(vertexCloud& cloud) noexcept
  {
      cloud.clear();

      auto gabarits =
      (*std::max_element
        (
            ContentTree::getInstance()._items.cbegin(),
            ContentTree::getInstance()._items.cend(),
            [] (auto item_1, auto item_2) -> bool
            { return item_1 -> _meshPtr -> getModelHeights() >
                     item_2 -> _meshPtr -> getModelHeights(); }
        )
      ) -> _meshPtr -> getModelHeights();


      cloud.emplace
      (
        std::make_pair
        (
            *cfg::get<f>(CfgNames::FIRST_LAYER),
            layer()
        )
      );

      if(cfg::get<b>(CfgNames::DYNAMIC_LAYER)) generateDynamicLayerHeight(cloud, gabarits);
      else                                     generateStaticLayerHeight (cloud, gabarits);

      std::vector<tempLayer> tmpCloud(cloud.size(), tempLayer());

      for (auto& item : ContentTree::getInstance()._items)
              for (auto& triangle : item -> _meshPtr -> getTriangleArray())
              {
                      uint32_t index = 0u;
                      // Geometry::Triangle::onTerm(triangle);
                      for ( auto& [ height, layer ] : cloud )
                      {
                          if ( triangle -> getVertex_A() -> getZ() <  height ) break;
                          if ( triangle -> getVertex_C() -> getZ() >  height ) ++index;
                          if ( triangle -> getVertex_C() -> getZ() <= height )
                          {
                                  tmpCloud[index].emplace_back(triangle -> cut(height));
                                  validate(tmpCloud[index], layer);
                          }
                      }
               }
  }

//  ____________________TEMPORARY________________________ //

  void
  heightInTerminal(vertexCloud& cloud) noexcept
  {
      std::cout << "\n\n";
      int count = 0;

      if  (cloud.empty()) return;

      for ( auto& [ height, layer ] : cloud )
      {
          int c = 0;
          std::cout << ++count << '\t' << height << '\n';
          for ( auto& [closed, coords] : layer ) for(auto& coord : coords) std::cout << "\t\t" << ++c << " point\t" << "X = " << coord.x << '\t' << "Y = " << coord.y << '\n';
          std::cout << "\n\n\n";
      }
  }

//  ________________END_OF_TEMPORARY_____________________ //

}; // Slicer

#endif //VERTEXCLOUD_HPP
