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

#ifndef MESH_H
#define MESH_H

#include <list>
#include <string>
#include <algorithm>
#include "geometry.hpp"

using Geometry::_vectorPtr;
using Geometry::_vertexPtr;
using Geometry::_trianglePtr;

class Mesh
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

    public:    // TYPES
        using _meshPtr_t    = std::unique_ptr < Mesh >;
        using _triangleData = std::list < _trianglePtr >;
        using _vertexData   = std::list < _vertexPtr >;
        using _filename_t   = std::string;
        using _stat_t       = uint64_t;

    protected:   // DATA
        _filename_t   __filename;
        _vertexData   __vertexData;
        _triangleData __triangleData;

    private:    // DATA
        _stat_t _vertices;
        _stat_t _triangles;
    
    public:
        bool _valid = false;

    public:    // STATISTICS_GETTER
        const _stat_t
        getVertices( ) const noexcept;

        const _stat_t
        getTriangles( ) const noexcept;

        void stat() noexcept;

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

#endif // MESH_H