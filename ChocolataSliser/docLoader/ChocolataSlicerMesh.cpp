#include "ChocolataSlicerMesh.h"
#include "filework.hpp"

Mesh::Mesh(_filename_t filename) noexcept
    : __filename ( filename )
{ }

Mesh::Mesh(const Mesh& mesh) noexcept
    : __filename    (mesh.__filename    )
    , __vertexData  (mesh.__vertexData  )
    , __triangleData(mesh.__triangleData)
{ fixAllTriangle(); calculateGabarit(); }

Mesh::Mesh(const Mesh&& mesh) noexcept
    : __filename    (std::move(mesh.__filename)    )
    , __vertexData  (std::move(mesh.__vertexData)  )
    , __triangleData(std::move(mesh.__triangleData))
{ fixAllTriangle(); calculateGabarit(); }

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
        [this](_trianglePtr triangle) mutable -> void
        {
            mIndices.insert
            (
                mIndices.end(),
                {
                    __vertexData [ triangle -> getVertex_A() ],
                    __vertexData [ triangle -> getVertex_B() ],
                    __vertexData [ triangle -> getVertex_C() ],
                }
            );
        }
    );

    std::for_each
    (
        __vertexData.cbegin(),
        __vertexData.cend(),
        [this](auto vert) mutable -> void
        {
            mPositions.insert
            (
                mPositions.begin(),
                {
                    vert.first -> getX(),
                    vert.first -> getY(),
                    vert.first -> getZ(),
                }
            );
        }
    );

    recalculateNormals();
    recalculateTangents();
    recalculateBitangents();
}

bool Mesh::isEmpty() noexcept
{ return __triangleData.empty() && __vertexData.empty(); }

const Mesh::_triangleData&
Mesh::getTriangleArray() const noexcept
{ return __triangleData; }

const float
Mesh::getModelHeights() const noexcept
{ return _g_z; }

void Mesh::calculateGabarit() noexcept
{
    if (__vertexData.empty()) std::cout << "YOU ARE DYRAK";

    auto [minX, maxX] = std::minmax_element
    (
        __vertexData.cbegin(),
        __vertexData.cend(),
        [] (auto v_1, auto v_2) -> bool
        { return  v_1.first -> getX() < v_2.first -> getX(); }
    );

    auto [minY, maxY] = std::minmax_element
    (
        __vertexData.cbegin(),
        __vertexData.cend(),
        [] (auto v_1, auto v_2) -> bool
        { return  v_1.first -> getY() < v_2.first -> getY();}
    );

    auto [minZ, maxZ] = std::minmax_element
    (
        __vertexData.cbegin(),
        __vertexData.cend(),
        [] (auto v_1, auto v_2) -> bool
        { return  v_1.first -> getZ() < v_2.first -> getZ();}
    );

    _g_x = maxX -> first -> getX() - minX -> first -> getX();
    _g_y = maxY -> first -> getY() - minY -> first -> getY();
    _g_z = maxZ -> first -> getZ() - minZ -> first -> getZ();
}

void Mesh::fixAllTriangle() noexcept
{
    std::for_each
    (
        __triangleData.begin(),
        __triangleData.end(),
        [] (auto triangle) -> void
        { triangle -> fixTriangle(); }
    );
}

std::optional < float >
Mesh::nextLayerHeight(const float prev) const noexcept
{
    std::optional < float > minCos = std::nullopt;   // max angle

    const float min          = *cfg::get<f>(CfgNames::MIN_LAYER);
    const float max          = *cfg::get<f>(CfgNames::MAX_LAYER);
    const float intersection = *cfg::get<f>(CfgNames::INTERSECTION);

    std::for_each
    (
        __triangleData.cbegin(),
        __triangleData.cend(),
        [&minCos, prev, min, max] (auto triangle) mutable -> void
        {
            if (triangle -> onRange(prev + min) || triangle -> onRange(prev + max))
            {
                if(!minCos) minCos = 1.f;
                if (auto angle = triangle -> getNormal().normalAngle();
                    std::abs(angle) < *minCos ) minCos = std::abs(angle);
            }
        }
    );

    if (minCos)
    {
        auto res = std::sqrt ( ( 1 - *minCos ) * ( 1 + *minCos ) ) * intersection;

        if(*minCos != 0) res /= *minCos;
        else return prev + max;

        if (res <= min) return prev + min;
        if (res >= max) return prev + max;
        if (res >=   0) return prev + res;
    }
    return std::nullopt;
}

Mesh::_meshPtr_t make_mesh(Mesh::File file_type,
    Mesh::_filename_t filename) noexcept
{
    Mesh::_meshPtr_t result = nullptr;
    if (file_type == Mesh::File::_STL) result = std::make_shared<Filework:: STL>(filename);
    if (file_type == Mesh::File::_OBJ) result = std::make_shared<Filework:: OBJ>(filename);
    if (file_type == Mesh::File::_AMF) result = std::make_shared<Filework:: AMF>(filename);
    if (file_type == Mesh::File::_3MF) result = std::make_shared<Filework::_3MF>(filename);
    if (file_type == Mesh::File::_FBX) result = std::make_shared<Filework:: FBX>(filename);
    if (file_type == Mesh::File::_PLY) result = std::make_shared<Filework:: PLY>(filename);

    // auto fut = std::async
    // (
        // std::launch::async,
        // [result] () -> void
        // {
            if(result == nullptr) return result;
            result -> open();
            result -> fixAllTriangle();
            result -> conf();
        // }
    // );

    return result;
}

bool add_in_this_mesh(Mesh::File file_type,
    Mesh::_meshPtr_t& model, Mesh::_filename_t filename) noexcept
{
    bool result = false;

    model -> __filename = filename;
    model -> open();

    result = true;
    return result;
}

bool reinit_mesh(Mesh::File file_type,
    Mesh::_meshPtr_t& model, Mesh::_filename_t filename) noexcept
{
    bool result = false;

    model -> destroy();
    model -> __filename = filename;
    model -> open();

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
    return __vertexData.size();
}

const Mesh::_stat_t Mesh::getTriangles( ) const noexcept
{
    return __triangleData.size();
}
