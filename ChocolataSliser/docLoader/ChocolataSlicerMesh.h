/**
 * Copyright (C) 2020 Chocolata Printer oficial software (Autor Abernihin Ilia & Velichko Bohdan)
 *
 * All right reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. something :)
 *
 *
 * Abstract: this is declaretion of Mesh
 *
 */

#ifndef CHOCOLATASLICERMESH_H
#define CHOCOLATASLICERMESH_H

#include <list>
#include <string>
#include <algorithm>
#include <map>

#include "geometry.hpp"
#include "cinder/TriMesh.h"

using Geometry::_vectorPtr;
using Geometry::_vertexPtr;
using Geometry::_trianglePtr;

using namespace cinder;

class Mesh : public TriMesh
{
    public:    // FILES
        enum class File
        {
            _STL,
            _OBJ,
            _FBX,
            _AMF,
            _3MF,
            _PLY
        };

        struct _Hesher
        {
            size_t
            operator()(const _vertexPtr value) const noexcept
            {
                char bit[sizeof(*value)];

                std::memcpy(bit, value.get(), 32);

                std::hash < std::string > hesher;

                return  hesher(bit);
            }
        }; // STRUCT__HESHER

        struct _Equal
        {
                bool
                operator()(const _vertexPtr lhr, const _vertexPtr rhr) const noexcept
                { return *lhr == *rhr; }
        }; // STRUCT__EQUALs

    public:    // TYPES
        using _meshPtr_t    = std::unique_ptr < Mesh >;
        using _triangleData = std::list < _trianglePtr >;
        using _vertexData   = std::unordered_map < _vertexPtr, uint32_t,
                                                   _Hesher   , _Equal >;
        using _filename_t   = std::string;
        using _stat_t       = uint64_t;

    protected:   // DATA
        _filename_t                  __filename;
        _vertexData                  __vertexData;
        _triangleData                __triangleData;

    private:    // DATA
        _stat_t                      _vertices;
        _stat_t                      _triangles;

    public:
        bool _valid = false;

    public:    // STATISTICS_GETTER
        const _stat_t
        getVertices( ) const noexcept;

        const _stat_t
        getTriangles( ) const noexcept;

        void stat() noexcept;

        bool isEmpty() noexcept;

    public:   // CONSTRUCT
        Mesh ( _filename_t filename ) noexcept;

        Mesh ( const Mesh& mesh ) noexcept;
        Mesh ( const Mesh&& mesh ) noexcept;

        Mesh& operator = ( const Mesh& mesh ) noexcept;
        Mesh& operator = ( const Mesh&& mesh ) noexcept;

        virtual ~Mesh ( ) noexcept;

    public:
        virtual bool open() noexcept = 0;
        virtual bool save() const noexcept = 0;
        virtual bool destroy() noexcept = 0;

    private:
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
