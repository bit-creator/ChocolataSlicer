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

#include "geometry.hpp"
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
  using coord_t     = float;
  using layerPoint  = std::pair < coord_t, coord_t >;
  using layer       = std::list <    layerPoint    >;
  using vertexCloud = std::map  <   height, layer  >;
  using tempLayer   = std::list <  Geometry::cut_t >;

  namespace
  {
      void
      generateStaticLayerHeight(vertexCloud& cloud) noexcept
      {

      }

      void
      generateDynamicLayerHeight(vertexCloud& cloud) noexcept
      {
          float max = 0.3;  // need defined configs value

          cloud.clear();

          cloud.emplace
          (
            std::make_pair
            (
                0.2,
                layer()
            )
          );

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

          while(cloud.rbegin() -> first < gabarits - max)
            std::for_each
            (
                ContentTree::getInstance()._items.cbegin(),
                ContentTree::getInstance()._items.cend(),
                [&cloud] (auto item) -> void
                {
                    if (auto layHeigh = item -> _meshPtr
                        -> nextLayerHeight(cloud.rbegin() -> first);
                    layHeigh)           // condition
                    cloud.emplace
                    (
                        std::make_pair
                        (
                            *layHeigh,
                            layer()
                        )
                    );
                }
            );
      }
  };

  void
  generateVertexCloud(vertexCloud& cloud) noexcept
  {
      generateDynamicLayerHeight(cloud);

  //     std::for_each
  //     (
  //       ContentTree::getInstance()._items.cbegin(),
  //       ContentTree::getInstance()._items.cend(),
  //       [] (auto item) -> void
  //       {
  //           std::for_each
  //           (
  //               item -> _meshPtr -> getTriangleArray().cbegin(),
  //               item -> _meshPtr -> getTriangleArray().cend(),
  //               [] (auto triangle) -> void
  //               {
  //
  //               }
  //           );
  //       }
  //   );
  }

//  ____________________TEMPORARY________________________ //

  void
  heightInTerminal(vertexCloud& cloud) noexcept
  {
      int count = 0;
      auto prev = cloud.begin();
      std::for_each
      (
        ++cloud.cbegin(),
        cloud.cend(),
        [&count, &prev] (auto layer) -> void
        { std::cout << ++count << "\t" << layer.first << '\t' << (layer.first - prev->first) << '\n'; ++prev; }
      );
  }

//  ________________END_OF_TEMPORARY_____________________ //

}; // Slicer

#endif //VERTEXCLOUD_HPP
