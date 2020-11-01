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
  using optPoint    = Geometry::optPoint2d;
  using tmpPoint    = Geometry::cut_t;
  using closeFlag   = bool;
  using curve       = std::list <    layerPoint    >;     // or circular linked list (need impliment)
  using layer       = std::list <      curve       >;
  using vertexCloud = std::map  <   height, layer  >;
  using tempLayer   = std::list <     tmpPoint     >;

  class VertexCloudHandler
  {
  private:
      using VCHandler = VertexCloudHandler;

      vertexCloud                                           _cloud;

      VertexCloudHandler() noexcept
      {  }

  public:
      static VCHandler&
      get() noexcept
      { static auto cloud = VCHandler(); return cloud; }

      void
      generateStaticLayerHeight(const float gabarits) noexcept
      {
          const float layerh = *cfg::get<f>(CfgNames::LAYER);
          while(_cloud.rbegin() -> first < gabarits - layerh)
                _cloud.emplace ( std::make_pair ( layerh, layer() ) );
      }

      void
      generateDynamicLayerHeight(const float gabarits) noexcept
      {
          float max = *cfg::get<f>(CfgNames::MAX_LAYER);

          while(_cloud.rbegin() -> first < gabarits - max)
          {
              float layerHeight = _cloud.rbegin() -> first + max;

              for (auto& model : ContentTree::getInstance()._items)
              {
                  if (!model -> _meshPtr -> _sliced)
                  {
                      if (auto layHeigh = model -> _meshPtr
                          -> nextLayerHeight(_cloud.rbegin() -> first);
                      layHeigh)
                      {
                          if (layerHeight >= *layHeigh )
                          layerHeight = *layHeigh;
                      }
                      else model -> _meshPtr -> _sliced = true;
                  }
              }
              _cloud.emplace ( std::make_pair ( layerHeight, layer() ) );
          }

          if (gabarits - _cloud.rbegin()->first > *cfg::get<f>(CfgNames::MIN_LAYER))
            _cloud.emplace (std::make_pair (gabarits, layer()));
      }

      void
      generateVertexCloud() noexcept
      {
          _cloud.clear();

          auto gabarits = (*std::max_element (
            ContentTree::getInstance()._items.cbegin(),
            ContentTree::getInstance()._items.cend(),
            [] (auto item_1, auto item_2) -> bool
            { return item_1 -> _meshPtr -> getModelHeights() >
                     item_2 -> _meshPtr -> getModelHeights(); }
            )) -> _meshPtr -> getModelHeights();

          _cloud.emplace (std::make_pair (*cfg::get<f>(CfgNames::FIRST_LAYER), layer()));

          if(cfg::get<b>(CfgNames::DYNAMIC_LAYER)) generateDynamicLayerHeight(gabarits);
          else                                     generateStaticLayerHeight (gabarits);

          std::vector<tempLayer> tmpCloud(_cloud.size(), tempLayer());

          for (auto& item : ContentTree::getInstance()._items)
            for (auto& triangle : item -> _meshPtr -> getTriangleArray())
            {
              uint32_t index = 0u;
              // Geometry::Triangle::onTerm(triangle);
              for ( auto& [ height, layer ] : _cloud )
              {
                  if ( triangle -> getVertex_A() -> getZ() <  height ) break;
                  if ( triangle -> getVertex_C() -> getZ() >  height ) ++index;
                  if ( triangle -> getVertex_C() -> getZ() <= height )
                     tmpCloud[index].emplace_back(triangle -> cut(height));
              }
            }
          compressCloud(tmpCloud);
      }

  private:
      bool isClosed(const curve& crv) noexcept
      { return *crv.cbegin() == *crv.crbegin(); }

      bool push(curve& crv, tmpPoint& tmp) const noexcept
      {
          auto& [first, second] = *tmp;

          if (*first == crv.front())
          {
              crv.push_front(*second);
              return true;
          }
          if (*second == crv.front())
          {
              crv.push_front(*first);
              return true;
          }
          if (*first == crv.back())
          {
              crv.push_back(*second);
              return true;
          }
          if (*second == crv.back())
          {
              crv.push_back(*first);
              return true;
          }
          return false;
      }

      bool empty(const tmpPoint& tmp) noexcept
      {
          if (tmp)
              if (auto& [first, second] = *tmp; first) return false;
              else if (second) return false;
                   else return true;
          else return true;
      }

      bool single(const tmpPoint& tmp) noexcept
      {
          if (tmp)
              if (auto& [first, second] = *tmp; first && second) return false;
              else return true;
          else return true;
      }

      void compressCloud(std::vector<tempLayer>& temp) noexcept
      {
          auto layerPtr = _cloud.begin();
          for(auto& rowLayer : temp)
          {
              for (auto iter = rowLayer.begin(); iter != rowLayer.end();)
                  if(empty(*iter) || single(*iter)) rowLayer.erase(iter);
                  else ++iter;

              layerPtr -> second.emplace_back(curve());
              curve& crv = layerPtr -> second.back();
              while (!rowLayer.empty())
              {
                  if (isClosed(crv))
                  {
                      layerPtr -> second.emplace_back(curve());
                      crv = layerPtr -> second.back();
                  }
                  else
                  {
                      if (crv.empty())
                      {
                          crv.emplace_back(*rowLayer.front()->first);
                          crv.emplace_back(*rowLayer.front()->second);
                      }
                      else for (auto iter = rowLayer.begin(); iter != rowLayer.end();)
                               if(push(crv, *iter)) rowLayer.erase(iter);
                               else ++iter;
                  }
              }
              if (!isClosed(crv)) crv.push_back(crv.front());
              ++layerPtr;
          }
      }

  };


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
          // for ( auto& [closed, coords] : layer ) for(auto& coord : coords) std::cout << "\t\t" << ++c << " point\t" << "X = " << coord.x << '\t' << "Y = " << coord.y << '\n';
          std::cout << "\n\n\n";
      }
  }

//  ________________END_OF_TEMPORARY_____________________ //

}; // Slicer

#endif //VERTEXCLOUD_HPP
