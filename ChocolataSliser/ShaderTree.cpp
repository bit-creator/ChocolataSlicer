#include "ShaderTree.h"
#include "cinder/Log.h"

void ShaderTree::initShaders() {
    // Color shader
    try {
        _colorShader = ci::gl::getStockShader(ci::gl::ShaderDef().color() );
    }
    catch (ci::Exception& e) {
        CI_LOG_EXCEPTION("Shade loading", e );
    }


    // Velvet shader
    try {
        _velvetyShader = ci::gl::GlslProg::create(
            ci::loadFile("assets/shaders/Velvety.vs.glsl"),
            ci::loadFile("assets/shaders/Velvety.fs.glsl")
        );
    }
    catch (ci::Exception& e) {
        CI_LOG_EXCEPTION("Shade loading", e );
    }


    // Solid shader
    try {
        _solidShader = ci::gl::getStockShader(ci::gl::ShaderDef().color() );
    }
    catch (ci::Exception& e) {
        CI_LOG_EXCEPTION("Shade loading", e );
    }

}

void ShaderTree::destroy() {
    _colorShader.reset();
    _velvetyShader.reset();

    _solidShader.reset();
}