#ifndef __CHOCOLATA_SLICER_
#define __CHOCOLATA_SLICER_

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"


#include "ui/ui.h"
#include "FileSelector.h"
#include "ContentTree.h"
#include "ObjectPicker.h"
#include "docLoader/ChocolataSlicerMesh.h"

#include "ShaderTree.h"
#include "Notification/Notification.h"

#include "definitions.h" 

/**
 * @brief ChocolataSlicer is a main program's class for defining ChocolataApps behavior
 * and manipulating all functionality
 *
*/
class ChocolataSlicer : public ci::app::App {
    public :
        /**
         * Function for prepering anly slicers definitions
        */
        void setup() override;

        /**
         * Executes every tick
        */
        void update() override;

        /**
         * Executes every tick and contains camera resizing and FBOs
        */
        void resize() override;

        /**
         * Executes every tick and draws scene
        */
        void draw() override;

        /**
         * Cleans dynamicall reserved memory before programs end
        */
        void cleanup() override;

        /**
         * Function for drawing all programs ui
        */
        void drawUI();


	    void mouseDown(ci::app::MouseEvent event ) override;
	    void mouseDrag(ci::app::MouseEvent event ) override;
        void mouseWheel(ci::app::MouseEvent event ) override;

	    void keyDown(ci::app::KeyEvent event ) override;
	    // void keyUp(ci::app::KeyEvent event ) override;

    public :  // Ui components of Slicer
        ui::uiViewportRef       m_ui_viewport;

        ui::uiWindowHandlerRef  m_handler_main;


        ui::uiWindowRef         m_window_editor;

        ui::uiWindowRef         m_window_content;

    public : // Hard logic components
        ci::CameraPersp         m_camera;
        ci::CameraUi			m_cameraui;


        int                     _viewMode = 0;

    public :
        ci::log::LoggerFile _logger = ci::log::LoggerFile(__ChocolataSlicer_LogFile_, false);

};



#endif // __CHOCOLATA_SLICER_
