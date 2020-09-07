#include "ChocolataSlicer.h"

#include "ui/BarWindows/uiBarWindows.h"
#include "cinder/linux/input_redef.h"

#include "printingContext.h"


void ChocolataSlicer::resize() {
    m_camera.setPerspective(25, getWindowAspectRatio(), 1, 600 );
	ci::gl::setMatrices(m_camera );

    m_cameraui.setWindowSize(getWindowSize() );

    ObjectPicker::getInstance().resize();

}

void ChocolataSlicer::update() {
}


void ChocolataSlicer::draw() {
    ci::gl::clear(ci::Color::gray(0.2) );
    drawUI();

    ci::gl::setMatrices(m_camera );


    // FIXME: Draw Grid + Axises
    uint32_t lines = 6, offset = 2;
    ci::gl::color(1,1,1, 0.4);
    for (int i = 1; i <= lines; i ++ ) {
        ci::gl::drawLine(glm::vec3((offset*i),0,0), glm::vec3((offset*i),0,(offset*lines)) );    
        ci::gl::drawLine(glm::vec3(0,0,(offset*i)), glm::vec3((offset*lines),0,(offset*i)) );
    }

    ci::gl::color(1,0,0);
    ci::gl::drawLine(glm::vec3(0), glm::vec3((offset*lines),0,0) );

    ci::gl::color(0,1,0);
    ci::gl::drawLine(glm::vec3(0), glm::vec3(0,(offset*lines),0) );

    ci::gl::color(0,0,1);
    ci::gl::drawLine(glm::vec3(0), glm::vec3(0,0,(offset*lines)) );

    ContentTree::getInstance().drawObjectsToScene(&m_camera );

}


void ChocolataSlicer::mouseDrag(ci::app::MouseEvent event ) {
	m_cameraui.mouseDrag( event );
}


void ChocolataSlicer::mouseDown(ci::app::MouseEvent event ) {
    m_cameraui.mouseDown( event );

    ObjectPicker::getInstance().calculateSelection(&m_camera, event );

}

void ChocolataSlicer::mouseWheel(ci::app::MouseEvent event ) {
    m_cameraui.mouseWheel( event );
}


void ChocolataSlicer::keyDown(ci::app::KeyEvent event ) {
    if (event.getModifiers() & (ci::app::KeyEvent::CTRL_DOWN | ci::app::KeyEvent::SHIFT_DOWN) ) {
        if (event.getCode() == ci::app::KeyEvent::KEY_q ) quit();
    }

}
