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
 * Abstract: this is declaretion of file reader/writer
 *
 */

#ifndef FILEWORK_HPP
#define FILEWORK_HPP

#include <fstream>
#include <iostream>
#include <bitset>
#include <unordered_set>
#include <future>
#include <algorithm>
#include <cstring>

#include "../Cinder/include/cinder/ObjLoader.h"
#include "geometry.hpp"
#include "ChocolataSlicerMesh.h"

/**
 * My ideas
 *  maybe impl vertex tree in nemespace Filework? (not in class STL)
*/

namespace Filework
{
    /**
     * @class STL is a structure for reading writing Mesh in format "binary STL"
     *
     * Base class: Mesh
     *
     * construction: with @class Mesh make_fuunction
    */
    class STL : public Mesh
    {
        private:        // TYPES
            using _number_t = uint32_t;
            using _header_t = char;

        private:  // STL_POLIGON_IMPL
            /**
             * @struct Poligon is helper, for read/write in/out STL binary file
             *
             * construction: desable.
            */
            struct Poligon
            {
                private:  // COPY_OPERATIONS
                    /**
                     * all copy or move operations delete
                    */
                    Poligon(const Poligon&) = delete;

                    Poligon&
                    operator = (const Poligon&) = delete;

                public:  // CONSTRUCTOR_DESTRUCTOR
                    /**
                     * (constructor) and (destructor) generate compiler.
                    */
                    Poligon() = default;
                    ~Poligon() = default;

                private: // DATA
                    float normalX;   float normalY;   float normalZ;        // normal coordinate
                    float point_A_X; float point_A_Y; float point_A_Z;      // first vertex coordinate
                    float point_B_X; float point_B_Y; float point_B_Z;      // second vertex coordinate
                    float point_C_X; float point_C_Y; float point_C_Z;      // third vertex coordinate

                    char bytecount1 = 0; char bytecount2 = 0;               // alignment

                public:
                    /**
                     * @brief call function operator have two overloads:
                     *
                     * first: used in read binary STL data
                     *
                     * @brief set triangle in model
                     *
                     * @param model STL object reference
                     *
                     * this overload no change the Poligon
                     *
                     * this overload no throw exeption
                     *
                     *
                     * second: used in write binary data in STL file
                     *
                     * @param triangle const pointer on original triangle
                     *
                     * this overload no throw exeption
                    */
                    void operator()(STL& model) const noexcept
                    { model.__triangleData.emplace_back ( std::make_shared < Geometry::Triangle > (
                                             Geometry::Vector ( normalX,   normalY,   normalZ   ),
                        model.findOrCreate ( Geometry::Vertex ( point_A_X, point_A_Y, point_A_Z )),
                        model.findOrCreate ( Geometry::Vertex ( point_B_X, point_B_Y, point_B_Z )),
                        model.findOrCreate ( Geometry::Vertex ( point_C_X, point_C_Y, point_C_Z )))); }

                    void operator()(const _trianglePtr& triangle) noexcept
                    {
                        normalX   = triangle -> getNormal()   .  getX();
                        normalY   = triangle -> getNormal()   .  getY();
                        normalZ   = triangle -> getNormal()   .  getZ();
                        point_A_X = triangle -> getVertex_A() -> getX();
                        point_A_Y = triangle -> getVertex_A() -> getY();
                        point_A_Z = triangle -> getVertex_A() -> getZ();
                        point_B_X = triangle -> getVertex_B() -> getX();
                        point_B_Y = triangle -> getVertex_B() -> getY();
                        point_B_Z = triangle -> getVertex_B() -> getZ();
                        point_C_X = triangle -> getVertex_C() -> getX();
                        point_C_Y = triangle -> getVertex_C() -> getY();
                        point_C_Z = triangle -> getVertex_C() -> getZ();
                    }
            }; // STRUCT_POLIGON

        private:  //SPECIFIC_STL_INFO
            _header_t __header[80];     // 80 byte of header in file begin
            _number_t __number;     // triangle number in model

        public:   // CONSTRUCTOR_DESTRUCTOR_ASSIGNMENT_OPERATOR
            /**
             * @brief (constructor) for class STL
             *
             * @param filename current path for read/write file
             *
             * this method no throw exeption
            */
            STL(_filename_t filename) noexcept
                : Mesh(filename)
            { }

            STL(const Mesh& mesh) noexcept
                : Mesh(mesh)
            { }

            /**
             * copy/move oparation generate compiler
            */
            STL ( const STL& ) noexcept = default;
            STL ( STL&& ) noexcept = default;

            STL&
            operator = ( const STL& ) noexcept = default;

            STL&
            operator = ( STL&& ) noexcept = default;

            /**
             * @brief (destructor) destroy all of data
             *
             * rhis method no throw exeption
            */
            virtual
            ~STL( ) noexcept
            { destroy(); }

        public:     // OPEN/SAVE SPECIFICATION
            /**
             * @brief read data in the file
             *
             * this method no throw exeption
            */
            virtual bool
            open() noexcept final
            {
                bool result = false;

                // std::async

                std::ifstream in(__filename, std::ios::binary);
                in >> *this;
                _valid = true;

                //end async

                stat();

                std::cout << "\n\n" << getVertices() << "\t" << getTriangles() << "\n\n";

                return result;
            }

            /**
             * @brief save change in a current path
             *
             * this method no throw exeption
            */
            virtual bool
            save() const noexcept final
            {
                bool result = false;
                std::ofstream out(__filename, std::ios::binary);
                out << *this;

                result = true;
                return result;
            }

            /**
             * @brief destroy all of data
            */
            virtual bool
            destroy() noexcept final
            {
                bool result = false;

                __triangleData.clear();
                __vertexData.clear();
                __filename.clear();
                // __header = '/0';
                __number = 0;

                result = true;
                return result;
            }

            /**
             * @brief save mesh in other path
             *
             * @param filename path who must be save
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            void
            saveAs(_filename_t filename) const noexcept
            {
                std::ofstream out(filename, std::ios::binary);
                out << *this;
            }

        private:
            /**
             * @brief this function returns pointer on original vertex
             * equal param vertex, or create if not find
             *
             * @param vertex new vertex
             *
             * @return pointer on this vertex in dataVertex
             *
             * this method no throw exeption
            */
            inline _vertexPtr
            findOrCreate(const Geometry::Vertex&& vertex) noexcept
            {
                auto [iterator, insert] = __vertexData.emplace
                    (
                        std::make_pair
                        (
                            std::make_shared<Geometry::Vertex>(std::move(vertex)),
                            __vertexData.size()
                        )
                    );
                return iterator -> first;
            }


             // STREAM_WORK_OPERATORS
        friend std::ifstream& operator >> (std::ifstream& in, STL& model) noexcept;
        friend std::ofstream& operator << (std::ofstream& out, const STL& model) noexcept;
    };

    /**
     * @class OBJ is a structure for reading writing Mesh in format "ASCII OBJ"
     *
     * Base class: Mesh
     *
     * construction: with @class Mesh make_fuunction
    */
    class OBJ : public Mesh
    {
        public:   // CONSTRUCTOR_DESTRUCTOR_ASSIGNMENT_OPERATOR
            /**
             * @brief (constructor) for class OBJ
             *
             * @param filename current path for read/write file
             *
             * this method no throw exeption
            */
            OBJ(_filename_t filename) noexcept
                : Mesh(filename)
            { }

            OBJ(const Mesh& mesh) noexcept
                : Mesh(mesh)
            { }

            /**
             * copy/move oparation generate compiler
            */
            OBJ ( const OBJ& ) noexcept = default;
            OBJ ( OBJ&& ) noexcept = default;

            OBJ&
            operator = ( const OBJ& ) noexcept = default;

            OBJ&
            operator = ( OBJ&& ) noexcept = default;

            /**
             * @brief (destructor) destroy all of data
             *
             * rhis method no throw exeption
            */
            virtual
            ~OBJ( ) noexcept
            { destroy(); }

        public:     // OPEN/SAVE SPECIFICATION
            /**
             * @brief read data in the file
             *
             * this method no throw exeption
            */
            virtual bool
            open() noexcept final
            {
                bool result = false;

                std::ifstream in(__filename, std::ios::binary);
                in >> *this;

                stat();

                result = true;
                return result;
            }

            /**
             * @brief save change in a current path
             *
             * this method no throw exeption
            */
            virtual bool
            save() const noexcept final
            {
                bool result = false;
                std::ofstream out(__filename, std::ios::binary);
                out << *this;

                result = true;
                return result;
            }

            /**
             * @brief destroy all of data
            */
            virtual bool
            destroy() noexcept final
            {
                bool result = false;

                __triangleData.clear();
                __vertexData.clear();
                __filename.clear();

                result = true;
                return result;
            }

            /**
             * @brief save mesh in other path
             *
             * @param filename path who must be save
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            void
            saveAs(_filename_t filename) const noexcept
            {
                std::ofstream out(filename, std::ios::binary);
                out << *this;
            }

                     // STREAM_WORK_OPERATORS
        friend std::ifstream& operator >> (std::ifstream& in, OBJ& model) noexcept;
        friend std::ofstream& operator << (std::ofstream& out, const OBJ& model) noexcept;
    };

    /**
     * @class AMF is a structure for reading writing Mesh in format "AMF"
     *
     * Base class: Mesh
     *
     * construction: with @class Mesh make_fuunction
    */
    class AMF : public Mesh
    {
        public:   // CONSTRUCTOR_DESTRUCTOR_ASSIGNMENT_OPERATOR
            /**
             * @brief (constructor) for class AMF
             *
             * @param filename current path for read/write file
             *
             * this method no throw exeption
            */
            AMF(_filename_t filename) noexcept
                : Mesh(filename)
            { }

            AMF(const Mesh& mesh) noexcept
                : Mesh(mesh)
            { }

            /**
             * copy/move oparation generate compiler
            */
            AMF ( const AMF& ) noexcept = default;
            AMF ( AMF&& ) noexcept = default;

            AMF&
            operator = ( const AMF& ) noexcept = default;

            AMF&
            operator = ( AMF&& ) noexcept = default;

            /**
             * @brief (destructor) destroy all of data
             *
             * rhis method no throw exeption
            */
            virtual
            ~AMF( ) noexcept
            { destroy(); }

        public:     // OPEN/SAVE SPECIFICATION
            /**
             * @brief read data in the file
             *
             * this method no throw exeption
            */
            virtual bool
            open() noexcept final
            {
                bool result = false;

                std::ifstream in(__filename, std::ios::binary);
                in >> *this;

                stat();

                result = true;
                return result;
            }

            /**
             * @brief save change in a current path
             *
             * this method no throw exeption
            */
            virtual bool
            save() const noexcept final
            {
                bool result = false;
                std::ofstream out(__filename, std::ios::binary);
                out << *this;

                result = true;
                return result;
            }

            /**
             * @brief destroy all of data
            */
            virtual bool
            destroy() noexcept final
            {
                bool result = false;

                __triangleData.clear();
                __vertexData.clear();
                __filename.clear();

                result = true;
                return result;
            }

            /**
             * @brief save mesh in other path
             *
             * @param filename path who must be save
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            void
            saveAs(_filename_t filename) const noexcept
            {
                std::ofstream out(filename, std::ios::binary);
                out << *this;
            }

             // STREAM_WORK_OPERATORS
        friend std::ifstream& operator >> (std::ifstream& in, AMF& model) noexcept;
        friend std::ofstream& operator << (std::ofstream& out, const AMF& model) noexcept;
    };

    /**
     * @class _3MF is a structure for reading writing Mesh in format "3MF"
     *
     * Base class: Mesh
     *
     * construction: with @class Mesh make_fuunction
    */
    class _3MF: public Mesh
    {
        public:   // CONSTRUCTOR_DESTRUCTOR_ASSIGNMENT_OPERATOR
            /**
             * @brief (constructor) for class _3MF
             *
             * @param filename current path for read/write file
             *
             * this method no throw exeption
            */
            _3MF(_filename_t filename) noexcept
                : Mesh(filename)
            { }

            _3MF(const Mesh& mesh) noexcept
                : Mesh(mesh)
            { }

            /**
             * copy/move oparation generate compiler
            */
            _3MF ( const _3MF& ) noexcept = default;
            _3MF ( _3MF&& ) noexcept = default;

            _3MF&
            operator = ( const _3MF& ) noexcept = default;

            _3MF&
            operator = ( _3MF&& ) noexcept = default;

            /**
             * @brief (destructor) destroy all of data
             *
             * rhis method no throw exeption
            */
            virtual
            ~_3MF( ) noexcept
            { destroy(); }

        public:     // OPEN/SAVE SPECIFICATION
            /**
             * @brief read data in the file
             *
             * this method no throw exeption
            */
            virtual bool
            open() noexcept final
            {
                bool result = false;

                std::ifstream in(__filename, std::ios::binary);
                in >> *this;

                stat();

                result = true;
                return result;
            }

            /**
             * @brief save change in a current path
             *
             * this method no throw exeption
            */
            virtual bool
            save() const noexcept final
            {
                bool result = false;
                std::ofstream out(__filename, std::ios::binary);
                out << *this;

                result = true;
                return result;
            }

            /**
             * @brief destroy all of data
            */
            virtual bool
            destroy() noexcept final
            {
                bool result = false;

                __triangleData.clear();
                __vertexData.clear();
                __filename.clear();

                result = true;
                return result;
            }

            /**
             * @brief save mesh in other path
             *
             * @param filename path who must be save
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            void
            saveAs(_filename_t filename) const noexcept
            {
                std::ofstream out(filename, std::ios::binary);
                out << *this;
            }

             // STREAM_WORK_OPERATORS
        friend std::ifstream& operator >> (std::ifstream& in, _3MF& model) noexcept;
        friend std::ofstream& operator << (std::ofstream& out, const _3MF& model) noexcept;
    };

    /**
     * @class FBX is a structure for reading writing Mesh in format "FBX"
     *
     * Base class: Mesh
     *
     * construction: with @class Mesh make_fuunction
    */
    class FBX : public Mesh
    {
        public:   // CONSTRUCTOR_DESTRUCTOR_ASSIGNMENT_OPERATOR
            /**
             * @brief (constructor) for class FBX
             *
             * @param filename current path for read/write file
             *
             * this method no throw exeption
            */
            FBX(_filename_t filename) noexcept
                : Mesh(filename)
            { }

            FBX(const Mesh& mesh) noexcept
                : Mesh(mesh)
            { }

            /**
             * copy/move oparation generate compiler
            */
            FBX ( const FBX& ) noexcept = default;
            FBX ( FBX&& ) noexcept = default;

            FBX&
            operator = ( const FBX& ) noexcept = default;

            FBX&
            operator = ( FBX&& ) noexcept = default;

            /**
             * @brief (destructor) destroy all of data
             *
             * rhis method no throw exeption
            */
            virtual
            ~FBX( ) noexcept
            { destroy(); }

        public:     // OPEN/SAVE SPECIFICATION
            /**
             * @brief read data in the file
             *
             * this method no throw exeption
            */
            virtual bool
            open() noexcept final
            {
                bool result = false;

                std::ifstream in(__filename, std::ios::binary);
                in >> *this;

                stat();

                result = true;
                return result;
            }

            /**
             * @brief save change in a current path
             *
             * this method no throw exeption
            */
            virtual bool
            save() const noexcept final
            {
                bool result = false;
                std::ofstream out(__filename, std::ios::binary);
                out << *this;

                result = true;
                return result;
            }

            /**
             * @brief destroy all of data
            */
            virtual bool
            destroy() noexcept final
            {
                bool result = false;

                __triangleData.clear();
                __vertexData.clear();
                __filename.clear();

                result = true;
                return result;
            }

            /**
             * @brief save mesh in other path
             *
             * @param filename path who must be save
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            void
            saveAs(_filename_t filename) const noexcept
            {
                std::ofstream out(filename, std::ios::binary);
                out << *this;
            }


             // STREAM_WORK_OPERATORS
        friend std::ifstream& operator >> (std::ifstream& in, FBX& model) noexcept;
        friend std::ofstream& operator << (std::ofstream& out, const FBX& model) noexcept;
    };

    /**
     * @class PLY is a structure for reading writing Mesh in format "binary PLY"
     *
     * Base class: Mesh
     *
     * construction: with @class Mesh make_fuunction
    */
    class PLY : public Mesh
    {
        public:   // CONSTRUCTOR_DESTRUCTOR_ASSIGNMENT_OPERATOR
            /**
             * @brief (constructor) for class PLY
             *
             * @param filename current path for read/write file
             *
             * this method no throw exeption
            */
            PLY(_filename_t filename) noexcept
                : Mesh(filename)
            { }

            PLY(const Mesh& mesh) noexcept
                : Mesh(mesh)
            { }

            /**
             * copy/move oparation generate compiler
            */
            PLY ( const PLY& ) noexcept = default;
            PLY ( PLY&& ) noexcept = default;

            PLY&
            operator = ( const PLY& ) noexcept = default;

            PLY&
            operator = ( PLY&& ) noexcept = default;

            /**
             * @brief (destructor) destroy all of data
             *
             * rhis method no throw exeption
            */
            virtual
            ~PLY( ) noexcept
            { destroy(); }

        public:     // OPEN/SAVE SPECIFICATION
            /**
             * @brief read data in the file
             *
             * this method no throw exeption
            */
            virtual bool
            open() noexcept final
            {
                bool result = false;

                std::ifstream in(__filename, std::ios::binary);
                in >> *this;

                stat();

                result = true;
                return result;
            }

            /**
             * @brief save change in a current path
             *
             * this method no throw exeption
            */
            virtual bool
            save() const noexcept final
            {
                bool result = false;
                std::ofstream out(__filename, std::ios::binary);
                out << *this;

                result = true;
                return result;
            }

            /**
             * @brief destroy all of data
            */
            virtual bool
            destroy() noexcept final
            {
                bool result = false;

                __triangleData.clear();
                __vertexData.clear();
                __filename.clear();

                result = true;
                return result;
            }

            /**
             * @brief save mesh in other path
             *
             * @param filename path who must be save
             *
             * this method no change object
             *
             * this method no throw exeption
            */
            void
            saveAs(_filename_t filename) const noexcept
            {
                std::ofstream out(filename, std::ios::binary);
                out << *this;
            }

             // STREAM_WORK_OPERATORS
        friend std::ifstream& operator >> (std::ifstream& in, PLY& model) noexcept;
        friend std::ofstream& operator << (std::ofstream& out, const PLY& model) noexcept;
    };


    std::ifstream& operator >> (std::ifstream& in, STL& model) noexcept
    {
        in.read(model.__header, 80);
        in.read((char*)&(model.__number), 4);

        if(!model.__number) { return in; }

        model.__vertexData.reserve(model.__number / 1.5);

        STL::Poligon poligon;
        for(uint32_t num = 0; num < model.__number; ++num)
        {
            in.read((char*)&(poligon), 50);
            poligon(model);
        }
        return in;
    }

    std::ofstream& operator << (std::ofstream& out, const STL& model) noexcept
    {
        out.write(model.__header, 80);
        out.write((char*)&(model.__number), 4);

        STL::Poligon poligon;
        for (const auto& triangle : model.__triangleData)
        {
            poligon(triangle);
            out.write((char*)&(poligon), 50);
        }

        return out;
    }

    std::ifstream& operator >> (std::ifstream& in, OBJ& model) noexcept
    {
        cinder::ObjLoader loader(std::shared_ptr<cinder::IStreamCinder>(in));

        // auto mesh = cinder::TriMesh::create(loader);

        // model = cinder::TriMesh::create(loader);

        return in;
    }

    std::ofstream& operator << (std::ofstream& out, const OBJ& model) noexcept
    {

        return out;
    }

        std::ifstream& operator >> (std::ifstream& in, AMF& model) noexcept
    {

        return in;
    }

    std::ofstream& operator << (std::ofstream& out, const AMF& model) noexcept
    {

        return out;
    }

        std::ifstream& operator >> (std::ifstream& in, _3MF& model) noexcept
    {

        return in;
    }

    std::ofstream& operator << (std::ofstream& out, const _3MF& model) noexcept
    {

        return out;
    }

        std::ifstream& operator >> (std::ifstream& in, FBX& model) noexcept
    {

        return in;
    }

    std::ofstream& operator << (std::ofstream& out, const FBX& model) noexcept
    {

        return out;
    }

        std::ifstream& operator >> (std::ifstream& in, PLY& model) noexcept
    {

        return in;
    }

    std::ofstream& operator << (std::ofstream& out, const PLY& model) noexcept
    {

        return out;
    }

}; // NAMESPACE_FILEWORK



#endif // FILEWORK_HPP
