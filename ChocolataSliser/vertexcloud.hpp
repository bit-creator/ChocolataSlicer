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

#ifndef VERTEXCLOUD_H
#define VERTEXCLOUD_H

#include <map>
#include <list>
#include <algorithm>

#include "../docLoader/geometry.hpp"
#include "../docLoader/ChocolataSlicerMesh.h"
#include "../ContentTree.h"

namespace Slicer
{
  using height      = float;
  using coord_t     = float;
  using layerPoint  = std::pair < coord_t, coord_t >;
  using layer       = std::list <    layerPoint    >;
  using vertexCloud = std::map  <   height, layer  >;
  using tempLayer   = std::list <  Geometry::cut_t >;

  void
  generateVertexCloud(vertexCloud& cloud) noexcept
  {
      cloud.clear();

      cloud.emplace
      (
        std::make_pair
        (
            0.2,
            layer()
        )
      );

      std::for_each
      (
        ContentTree::getInstance()._items.cbegin(),
        ContentTree::getInstance()._items.cend(),
        [] (auto item) -> void
        {
            if(true);
        }
    );

      std::for_each
      (
        ContentTree::getInstance()._items.cbegin(),
        ContentTree::getInstance()._items.cend(),
        [] (auto item) -> void
        {
            // if(true);


            std::for_each
            (
                item -> _meshPtr -> getTriangleArray().cbegin(),
                item -> _meshPtr -> getTriangleArray().cend(),
                [] (auto triangle) -> void
                {

                }
            );
        }
    );
  }

}; // Slice

#endif //VERTEXCLOUD_H
