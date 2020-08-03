#ifndef __CHOCOLATA_SLICER_SHADER_TREE_
#define __CHOCOLATA_SLICER_SHADER_TREE_


#include "cinder/gl/gl.h"
#include "cinder/gl/GlslProg.h"

// TODO: more shaders def
class ShaderTree {
    private : // Singleton definitions
        ShaderTree() : _colorShader(nullptr), _velvetyShader(nullptr), _solidShader(nullptr)
            { initShaders(); }

        void initShaders();


        // Shaders
        ci::gl::GlslProgRef         _colorShader;
        ci::gl::GlslProgRef         _velvetyShader;
        ci::gl::GlslProgRef         _solidShader;

    public : // Accesable
        static ShaderTree& getInstance() { static ShaderTree tree; return tree; }


        void destroy();


        ci::gl::GlslProgRef colorShader() { return _colorShader; } 
        ci::gl::GlslProgRef solidShader() { return _solidShader; }
        ci::gl::GlslProgRef velvetyShader() { return _velvetyShader; }

};



#endif // __CHOCOLATA_SLICER_SHADER_TREE_