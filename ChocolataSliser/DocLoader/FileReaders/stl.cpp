#include "stl.h"

void err()
{
    
}

STL::STL(_Filename_t filename) noexcept
    : Mesh(filename)
{
            std::ifstream in(filename, std::ios::binary);
            in >> *this;

    tree.clear();
    stat();
}

void STL::saveAsSTL(_Filename_t filename) noexcept
{
    std::ofstream out(filename, std::ios::binary);
    out << *this;
}

std::ifstream& operator >> (std::ifstream& in, STL& model) noexcept
{
    in.read(model.header, 80);
    in.read((char*)&(model.number), 4);

    if(!model.number) { err(); return in; }

    // std::cerr << "triangle capacity " << model.number << '\n';

    // size_t byteSize = model.number * 50 ;
    // char* buff = new char(byteSize);

    // in.read(buff, byteSize);

    STL::Poligon poligon;
    for(uint32_t num = 0; num < model.number; ++num)
    {
        // std::cerr << "Triangle [ " << num + 1 << " / " << model.number << " ] loaded" << '\n';;
        in.read((char*)&(poligon), 50);
        poligon(model);
    }
    // delete [] buff;
    return in;
}


std::ofstream& operator << (std::ofstream& out, STL& model) noexcept
{
    out.write(model.header, 80);
    out.write((char*)&(model.number), 4);

    STL::Poligon poligon;
    for (const auto& triangle : model.__triangleData)
    {
        poligon(triangle);
        out.write((char*)&(poligon), 50);
    }

    return out;
}

Mesh::_vertexPtr_t STL::findOrCreate(const Geometry::Vertex&& vertex) noexcept
{
    if(auto[iterator, insert] = 
        tree.emplace(std::make_shared<Geometry::Vertex>(std::move(vertex)));
    insert)    // COND
    {
        __vertexData.emplace_back(std::make_shared
            <Geometry::Vertex>(std::move(vertex)));
        return *iterator;
    }
    else return *iterator;
}

STL::~STL( ) { }