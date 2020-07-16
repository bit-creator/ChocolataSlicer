#include "ChocolataSlicerMesh.h"
#include "filework.hpp"

Mesh::Mesh(_filename_t filename) noexcept
    : __filename ( filename )
{

}

Mesh::Mesh(const Mesh& mesh) noexcept
    : __filename    (mesh.__filename    )
    , __vertexData  (mesh.__vertexData  )
    , __triangleData(mesh.__triangleData)
{

}

Mesh::Mesh(const Mesh&& mesh) noexcept
    : __filename    (std::move(mesh.__filename)    )
    , __vertexData  (std::move(mesh.__vertexData)  )
    , __triangleData(std::move(mesh.__triangleData))
{

}

Mesh::~Mesh( ) noexcept
{

}

Mesh& Mesh::operator = ( const Mesh& mesh ) noexcept
{
    if(this == &mesh) return *this;

    __filename     = mesh.__filename    ;
    __vertexData   = mesh.__vertexData  ;
    __triangleData = mesh.__triangleData;

    return *this;
}

Mesh& Mesh::operator = ( const Mesh&& mesh ) noexcept
{
    if(this == &mesh) return *this;

    __filename     = std::move(mesh.__filename    );
    __vertexData   = std::move(mesh.__vertexData  );
    __triangleData = std::move(mesh.__triangleData);

    return *this;
}

void Mesh::conf() noexcept
{
    std::for_each
    (
        __triangleData.cbegin(),
        __triangleData.cend(),
        [this, current = -1](_trianglePtr triangle) mutable -> void
        {
            mNormals.push_back
            (
                vec3
                (
                    triangle -> getNormal().getX(),
                    triangle -> getNormal().getY(),
                    triangle -> getNormal().getZ()
                )
            );

            mPositions.insert
            (
                mPositions.end(),
                {
                    triangle -> getVertex_A() -> getX(),
                    triangle -> getVertex_A() -> getY(),
                    triangle -> getVertex_A() -> getZ(),
                    triangle -> getVertex_B() -> getX(),
                    triangle -> getVertex_B() -> getY(),
                    triangle -> getVertex_B() -> getZ(),
                    triangle -> getVertex_C() -> getX(),
                    triangle -> getVertex_C() -> getY(),
                    triangle -> getVertex_C() -> getZ(),
                }
            );

            mIndices.insert
            (
                mIndices.end(),
                {
                    ++current,
                    ++current,
                    ++current
                }
            );
        }
    );

    // recalculateNormals();
    recalculateTangents();
    recalculateBitangents();
}

Mesh::_meshPtr_t make_mesh(Mesh::File file_type,
    Mesh::_filename_t filename) noexcept
{
    if (file_type == Mesh::File::_STL)
    {
        auto tmp = std::make_unique<Filework::STL>(filename);
        tmp -> open();
        tmp -> conf();
        return tmp;
    }

    if (file_type == Mesh::File::_OBJ)
    {
        auto tmp = std::make_unique<Filework::OBJ>(filename);
        tmp -> open();
        tmp -> conf();
        return tmp;
    }

    if (file_type == Mesh::File::_AMF)
    {
        auto tmp = std::make_unique<Filework::AMF>(filename);
        tmp -> open();
        tmp -> conf();
        return tmp;
    }

    if (file_type == Mesh::File::_3MF)
    {
        auto tmp = std::make_unique<Filework::_3MF>(filename);
        tmp -> open();
        tmp -> conf();
        return tmp;
    }

    if (file_type == Mesh::File::_FBX)
    {
        auto tmp = std::make_unique<Filework::FBX>(filename);
        tmp -> open();
        tmp -> conf();
        return tmp;
    }

    if (file_type == Mesh::File::_PLY)
    {
        auto tmp = std::make_unique<Filework::PLY>(filename);
        tmp -> open();
        tmp -> conf();
        return tmp;
    }
    // etc...
    return nullptr;
}

bool add_in_this_mesh(Mesh::File file_type,
    Mesh::_meshPtr_t& model, Mesh::_filename_t filename) noexcept
{
    bool result = false;

    if (file_type == Mesh::File::_STL)
    {
        Filework::STL tmp = *model;

        tmp.__filename = filename;
        tmp.open();

        *model = tmp;
    }

    if (file_type == Mesh::File::_OBJ)
    {
        Filework::OBJ tmp = *model;

        tmp.__filename = filename;
        tmp.open();

        *model = tmp;
    }

    if (file_type == Mesh::File::_AMF)
    {
        Filework::AMF tmp = *model;

        tmp.__filename = filename;
        tmp.open();

        *model = tmp;
    }

    if (file_type == Mesh::File::_3MF)
    {
        Filework::_3MF tmp = *model;

        tmp.__filename = filename;
        tmp.open();

        *model = tmp;
    }

    if (file_type == Mesh::File::_FBX)
    {
        Filework::FBX tmp = *model;

        tmp.__filename = filename;
        tmp.open();

        *model = tmp;
    }

    if (file_type == Mesh::File::_PLY)
    {
        Filework::PLY tmp = *model;

        tmp.__filename = filename;
        tmp.open();

        *model = tmp;
    }

    result = true;
    return result;
}

bool reinit_mesh(Mesh::File file_type,
    Mesh::_meshPtr_t& model, Mesh::_filename_t filename) noexcept
{
    bool result = false;

    if (file_type == Mesh::File::_STL)
    {
        Filework::STL tmp(filename);
        tmp.open();
        *model = tmp;
    }

    if (file_type == Mesh::File::_OBJ)
    {
        Filework::OBJ tmp(filename);
        tmp.open();
        *model = tmp;
    }

        if (file_type == Mesh::File::_AMF)
    {
        Filework::AMF tmp(filename);
        tmp.open();
        *model = tmp;
    }

        if (file_type == Mesh::File::_3MF)
    {
        Filework::_3MF tmp(filename);
        tmp.open();
        *model = tmp;
    }

        if (file_type == Mesh::File::_FBX)
    {
        Filework::FBX tmp(filename);
        tmp.open();
        *model = tmp;
    }

        if (file_type == Mesh::File::_PLY)
    {
        Filework::PLY tmp(filename);
        tmp.open();
        *model = tmp;
    }

    result = true;
    return result;
}

void save_mesh_as(Mesh::File file_type, const Mesh::_meshPtr_t& model,
    Mesh::_filename_t filename) noexcept
{
    if (file_type == Mesh::File::_STL)
    {
        const Filework::STL tmp = *model;
        tmp.saveAs(filename);
    }
    if (file_type == Mesh::File::_OBJ)
    {
        const Filework::OBJ tmp = *model;
        tmp.saveAs(filename);
    }
    if (file_type == Mesh::File::_FBX)
    {
        const Filework::FBX tmp = *model;
        tmp.saveAs(filename);
    }
    if (file_type == Mesh::File::_AMF)
    {
        const Filework::AMF tmp = *model;
        tmp.saveAs(filename);
    }
    if (file_type == Mesh::File::_3MF)
    {
        const Filework::_3MF tmp = *model;
        tmp.saveAs(filename);
    }
    if (file_type == Mesh::File::_PLY)
    {
        const Filework::PLY tmp = *model;
        tmp.saveAs(filename);
    }
    // etc...
}

const Mesh::_stat_t Mesh::getVertices( ) const noexcept
{
    return _vertices;
}

const Mesh::_stat_t Mesh::getTriangles( ) const noexcept
{
    return _triangles;
}

void Mesh::stat() noexcept
{
    _vertices = __vertexData.size();
    _triangles = __triangleData.size();
}
