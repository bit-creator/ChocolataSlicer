#ifndef __CHOCOLATA_SLICER_
#define __CHOCOLATA_SLICER_

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"


#include "ui/ui.h"
#include "ChocolataSlicerFileSelector.h"

#define __ChocolataSlicer_Version_ "0.1.1"

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
         * Executes every tick and contains camera rersizing and fbos
        */
        void resize() override;

        /**
         * Executes every tick and draws scene
        */
        void draw() override;

        /**
         * // Function for drawing all programs ui
        */
        void drawUI();

    public :  // Ui components of Slicer
        ui::uiViewportRef       m_ui_viewport;

        ui::uiWindowHandlerRef  m_handler_main;


        ui::uiWindowRef         m_window_editor;

        ui::uiWindowRef         m_window_content;

    public : // Hard logic components
        ci::CameraPersp         m_camera;

        bool                    m_sliced = false;

};



#endif // __CHOCOLATA_SLICER_

