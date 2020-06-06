#ifndef FBX_H
#define FBX_H

#include "../mesh.h"

class FBX : public Mesh
{
    FBX(_Filename_t filename) noexcept;
};

#endif // FBX_H