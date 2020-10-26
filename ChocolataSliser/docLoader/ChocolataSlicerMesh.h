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
 * Abstract: this is declaration of Mesh
 */

#ifndef CHOCOLATASLICERMESH_H
#define CHOCOLATASLICERMESH_H

#include <map>
#include <list>
#include <cmath>
#include <bitset>
#include <future>
#include <cstring>
#include <optional>
#include <algorithm>

#include <boost/functional/hash.hpp>

#include "geometry.hpp"
#include "configs.hpp"
#include "flat_hash_map/unordered_map.hpp"

#include "cinder/TriMesh.h"

using               Geometry::_vectorPtr;         // Pointer on geometric Vector
using               Geometry::_vertexPtr;         // Pointer on geometric Vertex
using               Geometry::_trianglePtr;       // Pointer on triangle
using               dim_t = float;                // Type of coord data
using               cinder::TriMesh;              // Visualizing Mesh

/**
 * @class Mesh is abstract base for 3D Mesh objects
 * Mesh improved vertex and triangle arrays
 * also gabarite sizes for standart axes
 * Mesh this is a cinder::TriMesh derived class,
 * TriMesh improve visualize Mesh
 */
class Mesh : public TriMesh
{
    public:
        /**
         * @class File has MIME type geometry who can be opened
         */
        enum class File
        {
            _STL,
            _OBJ,
            _FBX,
            _AMF,
            _3MF,
            _PLY
        };

        /**
         * @struct _Heasher is functor who ganerate unique Hesh key
         */
        struct _Hesher
        {
          size_t
          operator()(const _vertexPtr value) const noexcept
          {
            size_t res = *(int32_t*)(&(value -> getX()));
            boost::hash_combine(res, *(int32_t*)(&(value -> getY())));
            boost::hash_combine(res, *(int32_t*)(&(value -> getZ())));
            return res;
          }
        }; // STRUCT_HESHER

        /**
         * #struct _Equal is functor who comparisson two geometric vertex
         */
        struct _Equal
        {
                bool
                operator()(const _vertexPtr& lhr, const _vertexPtr& rhr) const noexcept
                { return *(static_cast<Geometry::Primitive*>(lhr.get()))
                          == *(static_cast<Geometry::Primitive*>(rhr.get())); }
        }; // STRUCT__EQUAL

    public:    // TYPES
        using _meshPtr_t    = std::shared_ptr < Mesh >;                         // pointer on Mesh
        using _triangleData = std::list < _trianglePtr >;                       // array of triangle
        // using _vertexData   = std::unordered_map < _vertexPtr, uint32_t,
                                                   // _Hesher   , _Equal >;        // array of verrtex
        using _vertexData   = ska::unordered_map< _vertexPtr, uint32_t, _Hesher, _Equal >;
        using _filename_t   = std::string;                                      // Mesh name type
        using _stat_t       = uint64_t;                                         // type for statict

    protected:   // DATA
        _filename_t                  __filename;                // full or ralative path
        _vertexData                  __vertexData;              // array of this vertex
        _triangleData                __triangleData;            // array of this triangle

    private:   // GABARITS
        float                        _g_x = 0;                  // gabatited sizes
        float                        _g_y = 0;                  // gabatited sizes
        float                        _g_z = 0;                  // gabatited sizes

    public:
        bool _valid = false;            // What is this????
        bool _sliced = false;

    public:    // GETTER
        /**
         * @brief use special type for reeturned value
         * @brief no change object
         * @brief no throw the exeption
         * @return num of verticies
         */
        const _stat_t
        getVertices( ) const noexcept;

        /**
         * @brief use special type for reeturned value
         * @brief no change object
         * @brief no throw the exeption
         * @return num of triangle
         */
        const _stat_t
        getTriangles( ) const noexcept;

        /**
         * @brief getter for data of triangle
         * @brief no change object
         * @brief no throw the exeption
         * @return constant reference on triangle list
         */
        const _triangleData&
        getTriangleArray( ) const noexcept;

        /**
         * @brief needed for vertex cloud only
         * @brief no change object
         * @brief no throw the exeption
         * @return gabarit size on Z axis
         */
        const float
        getModelHeights( ) const noexcept;

        /**
         * @brief calcs the value of model gabarit on X Y Z axis
         * @brief no throw exeption
         */
        void
        calculateGabarit( ) noexcept;

        /**
         * @brief autofixing problems triangle
         * @brief no throw exeption
         */
        void
        fixAllTriangle() noexcept;

        /**
         * @brief calculate next layer use previous
         * @param prev previous layer height
         * return next layer height or std::nullopt_t
         * @brief no change object
         * @brief no throw the exeption
         */
        std::optional < float >
        nextLayerHeight(const float prev) const noexcept;

        /**
         * @brief empty conditional test
         * @brief no throw the exeption
         * @return true if triangle and vertex arrays empty
         */
        bool isEmpty() noexcept;

    public:   // CONSTRUCT
        /**
         * (constructor) create empty model with correct path
         * no throw exeption
         */
        Mesh ( _filename_t filename ) noexcept;

        /**
         * copy/move (constructor) create model equal another
         * nothrow exeption
         * @param mesh another mesh
         */
        Mesh ( const Mesh& mesh ) noexcept;
        Mesh ( const Mesh&& mesh ) noexcept;

        /**
         * copy/move assigned operator create model equal another
         * nothrow exeption
         * @param mesh another mesh
         */
        Mesh& operator = ( const Mesh& mesh ) noexcept;
        Mesh& operator = ( const Mesh&& mesh ) noexcept;

        /**
         * virtual (destructor) no throw exeption
         */
        virtual ~Mesh ( ) noexcept;

    public: // abstract interface for inheritance
        virtual bool open() noexcept = 0;
        virtual bool save() const noexcept = 0;
        virtual bool destroy() noexcept = 0;

    private: // internal method
        /**
         * @brief configurate files data with TriMesh data arrays
         * @brief for visualize model no throw exeption
         */
        void conf() noexcept;

       // FRIEND_FOO_DECL
    friend _meshPtr_t make_mesh(File file_type,
        _filename_t filename) noexcept;

    friend bool add_in_this_mesh(File file_type,
        _meshPtr_t& model, _filename_t filename) noexcept;

    friend bool reinit_mesh(File file_type,
        _meshPtr_t& model, _filename_t filename) noexcept;

    friend void save_mesh_as(File file_type,
       const _meshPtr_t& model, _filename_t filename) noexcept;
};

#endif // CHOCOLATASLICERMESH_H
