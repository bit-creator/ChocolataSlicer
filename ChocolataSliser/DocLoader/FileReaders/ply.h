#ifndef PLY_H
#define PLY_H

#include "../mesh.h"

class PLY : public Mesh
{
    PLY(_Filename_t filename) noexcept;
};

#endif // PLY_H