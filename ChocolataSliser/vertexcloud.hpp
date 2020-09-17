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
// #include "ContentTree.h"

//  ____________________TEMPORARY________________________ //

class ContentItem { public: Mesh::_meshPtr_t _meshPtr; };

class ContentTree
{
    public:
        static ContentTree&
        getInstance()
        { static ContentTree tree; return tree; }

    public:
        std::vector < std::shared_ptr < ContentItem > >        _items;

    private:
        ContentTree() {  }
};

//  ________________END_OF_TEMPORARY_____________________ //

namespace Slicer
{
  using height      = float;
  // using coord_t     = float;
  using layerPoint  = Geometry::Point2d;
  using layer       = std::list <    layerPoint    >;
  using vertexCloud = std::map  <   height, layer  >;
  using tempLayer   = std::list <  Geometry::cut_t >;

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

      void validate(tempLayer& tmp, layer& arr) noexcept
      {
          bool inserted = 0;

          std::cout << "Validate Start";

          if (tmp.empty()) { std::cout << "Im dont understand how you done that"; return; }

          if (auto& point = *tmp.begin(); arr.empty())
          {
               if (point)
               {
                   if (point -> first) arr.emplace_back(*point -> first);
                   if (point -> second) arr.emplace_back(*point -> second);
               }
               inserted = true;
               // std::cout << "first insert\n";
               // std::cout << "\nnum\t" << tmp.size();
               tmp.erase(tmp.begin());
          }
          else
          {
              if(arr.size() == 1)
              {
                  if (point)
                  {
                     if(point -> first) if (*point -> first == *arr.crbegin())
                        { arr.emplace_back(*point -> second); inserted = true; }

                     if(point -> second) if (*point -> second == *arr.crbegin())
                        { arr.emplace_back(*point -> first); inserted = true; }
                  }
                  if (inserted) tmp.erase(tmp.begin());
                  std::cout << "second insert\n";
              }
              else for (auto pi = tmp.cbegin(); pi != tmp.cend(); ++pi)
              // else for (auto& point : tmp)
              {
                  auto& point = *pi;
                  if (point)
                  {
                     if (point -> first)
                     {
                        if (!inserted) if (*point -> first == *arr.crbegin())
                            { arr.emplace_back(*point -> second); inserted = true; }

                        if (!inserted) if (*point -> first == *arr.cbegin())
                            { arr.emplace_front(*point -> second); inserted = true; }

                     }
                     if (!inserted) if(point -> second)
                     {
                        if (!inserted) if (*point -> second == *arr.crbegin())
                            { arr.emplace_back(*point -> first); inserted = true; }

                        if (!inserted) if (*point -> second == *arr.cbegin())
                            { arr.emplace_front(*point -> first); inserted = true; }
                     }
                  }
                  if (inserted) tmp.erase(pi);
              }
              if(inserted) {validate(tmp, arr); std::cout << "Validate Start now\n";}
          }
      }

  };


  void
  generateVertexCloud(vertexCloud& cloud) noexcept
  {
      std::cout << "generateVertexCloud\n\n";
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

      std::cout << "\nLayer HAS\n";

      std::vector<tempLayer> tmpCloud(cloud.size(), tempLayer());

      std::for_each
      (
          ContentTree::getInstance()._items.cbegin(),
          ContentTree::getInstance()._items.cend(),

          [&cloud, &tmpCloud] (auto item) mutable -> void
          {
              std::for_each
              (
                  item -> _meshPtr -> getTriangleArray().cbegin(),
                  item -> _meshPtr -> getTriangleArray().cend(),

                  [&cloud, &tmpCloud] (auto triangle) mutable -> void
                  {
                      uint32_t index = 0u;
                      std::cout << "\nNewTriangles\n";
                      for ( auto& [ height, layer ] : cloud )
                      {
                          if ( triangle -> getVertex_A() -> getZ() <  height ) break;
                          if ( triangle -> getVertex_C() -> getZ() >  height ) ++index;
                          if ( triangle -> getVertex_C() -> getZ() <= height )
                          {
                                  tmpCloud[index].emplace_back(triangle -> cut(height));
                                  std::cout << "\npre " << layer.size() << " after\n";
                                  validate(tmpCloud[index], layer);
                          }
                      }
                  }
              );
          }
      );
  }

//  ____________________TEMPORARY________________________ //

  void
  heightInTerminal(vertexCloud& cloud) noexcept
  {
      std::cout << "\n\n";
      int count = 0;

      for ( auto& [ height, layer ] : cloud )
      {
          std::cout << ++count << '\t' << height << '\n';
          for ( auto& coord : layer ) std::cout << "X = " << coord.x << '\t' << "Y = " << coord.y << '\t';
          std::cout << "\n\n\n";
      }
  }

//  ________________END_OF_TEMPORARY_____________________ //

}; // Slicer

#endif //VERTEXCLOUD_HPP
