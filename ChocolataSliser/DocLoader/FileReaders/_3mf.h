#ifndef _3MF_H
#define _3MF_H

#include "../mesh.h"

class _3MF : public Mesh
{
    public:
        _3MF(_Filename_t filename) noexcept;
        
};

#endif // _3MF_H