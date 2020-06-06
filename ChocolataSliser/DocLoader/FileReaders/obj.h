#ifndef OBJ_H
#define OBJ_H

#include "../ChocolataSlicerMesh.h"

class OBJ : public Mesh
{
    OBJ(_Filename_t filename) noexcept;
};

#endif // OBJ_H