#ifndef STL_H
#define STL_H

#include <fstream>
#include <iostream>
#include <bitset>
#include <unordered_set>
#include <future>
#include <algorithm>

#include "../ChocolataSlicerMesh.h"

class STL : public Mesh
{
    private:   // VERTEX_TREE
        struct _Hesher
        {
            size_t 
            operator()(const _vertexPtr_t value) const noexcept
            { 
                std::bitset < 32 >  bit_x(*(int32_t*)(&(value -> getX())));
                std::bitset < 32 >  bit_y(*(int32_t*)(&(value -> getY())));
                std::bitset < 32 >  bit_z(*(int32_t*)(&(value -> getZ())));

                std::string bits = bit_x.to_string();
                bits.append(bit_y.to_string());
                bits.append(bit_z.to_string());

                std::bitset < 96 > bitsArray(bits);
                std::hash < std::bitset < 96 > > hesher;

                return  hesher(bitsArray); 
            }
        };

        struct _Equal
        {
            bool 
            operator()(const _vertexPtr_t lhr, const _vertexPtr_t rhr) const noexcept
            { return *(static_cast<Geometry::Primitive*>(lhr.get())) 
                  == *(static_cast<Geometry::Primitive*>(rhr.get())); }
        };

        using vertexTree_t = std::unordered_set < _vertexPtr_t, _Hesher, _Equal >;
        
        vertexTree_t tree;

    private:  // STL_POLIGON_IMPL
        struct Poligon
        {
            float normalX;   float normalY;   float normalZ;
            float point_A_X; float point_A_Y; float point_A_Z;
            float point_B_X; float point_B_Y; float point_B_Z;
            float point_C_X; float point_C_Y; float point_C_Z;

            char bytecount1 = 0; char bytecount2 = 0;

            void operator()(STL& model) noexcept
            { model.__triangleData.emplace_back ( std::make_shared < Geometry::Triangle > (
                  std::make_unique < Geometry::Vector > 
                                   ( Geometry::Vector ( normalX,   normalY,   normalZ   )),
                model.findOrCreate ( Geometry::Vertex ( point_A_X, point_A_Y, point_A_Z )),
                model.findOrCreate ( Geometry::Vertex ( point_B_X, point_B_Y, point_B_Z )),
                model.findOrCreate ( Geometry::Vertex ( point_C_X, point_C_Y, point_C_Z )))); }

            void operator()(const _trianglePtr_t& triangle) noexcept
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
        };

    private:  //SPECIFIC_STL_INFO
        char header[80];
        uint32_t number;

    public:   // CONSTRUCT
        STL(_Filename_t filename) noexcept;

        STL ( STL& mesh ) noexcept = default;
        STL ( STL&& mesh ) noexcept = default;

        STL& operator = ( STL& mesh ) noexcept = default;
        STL& operator = ( STL&& mesh ) noexcept = default;

        virtual ~STL ( ) noexcept; 
        
    private:
        _vertexPtr_t findOrCreate(const Geometry::Vertex&& vertex) noexcept;

    public:   // SAVE_FOO
        virtual void saveAsSTL(_Filename_t filename) noexcept final;

         // FRIEND_DECL
    friend std::ifstream& operator >> (std::ifstream& in, STL& model) noexcept;
    friend std::ofstream& operator << (std::ofstream& out, STL& model) noexcept;
};

#endif // STL_H