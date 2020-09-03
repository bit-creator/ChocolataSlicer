#include "ObjectPicker.h"
#include "ContentTree.h"

#include "ShaderTree.h"

#include <stdint.h>

void ObjectPicker::makeFbo() {
    _fboPtr.reset();

    ci::gl::Fbo::Format fboFormat;
	_fboPtr = ci::gl::Fbo::create(ci::app::getWindowWidth(), ci::app::getWindowHeight(), fboFormat );
}


void ObjectPicker::initObjectPicker() { makeFbo(); }

void ObjectPicker::resize() { makeFbo(); }


void ObjectPicker::drawToPickerFbo(ci::CameraPersp* cm ) {
    ci::gl::ScopedViewport viewport(glm::vec2( 0.0f ), ObjectPicker::getInstance()._fboPtr->getSize() );
    ObjectPicker::getInstance()._fboPtr->bindFramebuffer();
        ci::gl::clear({0,0,0,0});
        ci::gl::setMatrices(*cm );


        for (int i = 0; i < ContentTree::getInstance()._items.size(); i++ ) {
            if (!ContentTree::getInstance()._items.at(i)->_batchPtr ) continue;

            ci::gl::GlslProgRef sl = ContentTree::getInstance()._items.at(i)->_batchPtr->getGlslProg();
            ContentTree::getInstance()._items.at(i)->_batchPtr->replaceGlslProg(ShaderTree::getInstance().colorShader());

            ci::gl::setModelMatrix(glm::mat4(1.0) );
            ci::gl::color(0, ((float)(i+1))/((float)ContentTree::getInstance()._items.size()) ,0,1);
            ci::gl::translate(ContentTree::getInstance()._items.at(i)->_position );
            ci::gl::rotate(ContentTree::getInstance()._items.at(i)->_rotate );
            ci::gl::scale(ContentTree::getInstance()._items.at(i)->_scale );
            ContentTree::getInstance()._items.at(i)->_batchPtr->draw();

            ContentTree::getInstance()._items.at(i)->_batchPtr->replaceGlslProg(sl);
        }

    ObjectPicker::getInstance()._fboPtr->unbindFramebuffer();

}


int ObjectPicker::calculateSelection(ci::CameraPersp* cm, ci::app::MouseEvent &event ) {
    static const float _accuracy = 0.01f;
    drawToPickerFbo(cm);

    ci::Surface32f pixel = _fboPtr->readPixels32f(ci::Area(0,0, _fboPtr->getSize().x, _fboPtr->getSize().y ), GL_COLOR_ATTACHMENT0 );

    if (pixel.getPixel(event.getPos() ).a != 0 ) {
        float _greenPx = pixel.getPixel(event.getPos() ).g;

        for (int i = 0; i < ContentTree::getInstance()._items.size(); i++ ) {
            float _objCl = ((float)(i+1))/((float)ContentTree::getInstance()._items.size());

            if (fabs(_objCl - _greenPx) <= _accuracy )
                ContentTree::getInstance()._selected = i;

        }
    }
    else ContentTree::getInstance()._selected = -1;
}

