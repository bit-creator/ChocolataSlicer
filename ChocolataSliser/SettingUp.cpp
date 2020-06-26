#include "cinder/app/App.h"
#include "cinder/Display.h"
#include "cinder/Log.h"

#include "cinder/CinderImGui.h"



#include "ChocolataSlicer.h"

#include "ui/uiWindow.h"
#include "ui/uiWindowHandler.h"
#include "ui/uiViewport.h"
#include "ui/uiContentTree.h"

void ChocolataSlicer::setup() {
    CI_LOG_I("ChocolataApp ~> ChocolataSlicer version : " << __ChocolataSlicer_Version_ );
    CI_LOG_I("ChocolataApp ~> DisplaySize : " << getDisplay()->getSize().x << "px | " << getDisplay()->getSize().y << "px" );
    CI_LOG_I("ChocolataApp ~> WindowSize : " << getWindowSize().x << "px | " << getWindowSize().y << "px\n" );



    // Window preparing
    enablePowerManagement();
    setWindowPos( glm::ivec2(  (getDisplay()->getSize().x/2) - (getWindowSize().x/2),
                               (getDisplay()->getSize().y/2) - (getWindowSize().y/2) )
    );



    // Main opengl Initializing
    m_camera.setPerspective(45, getWindow()->getAspectRatio(), 1, 1000 );
    m_camera.lookAt(glm::vec3(3, 2, 4));
    m_cameraui = ci::CameraUi(&m_camera );

	ci::gl::enableDepthWrite();
	ci::gl::enableDepthRead();



    // ImGui Initializing
    ImGui::Initialize();
    ImGui::StyleColorsLight();
    ImGui::GetIO().IniFilename = "assets/config/imGuiReserveConfig.ini";
    ImGui::GetStyle().WindowRounding = 0;



    // Main Ui Initializing
    m_ui_viewport = ui::uiViewport::create(getWindow() );


    m_content_tree.pushItem(
        ui::uiContentItem::create("ModelObject:01", 
            ci::gl::Texture2d::create(1024, 1024 ) 
        )
    );

// ui::uiContentItem::create("ModelObject:01", ci::gl::Batch::create(ci::geom::Sphere().subdivisions(32), ci::gl::getStockShader(ci::gl::ShaderDef().color())) );

    m_window_editor = ui::uiWindow::create({240, 240}, {60, 60}, "Editor", ui::uiLocation_Top, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
    m_window_content = ui::uiWindow::create({240, 240}, {360, 60}, "Content bar", ui::uiLocation_Down, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    m_handler_main = ui::uiWindowHandler::create(getWindow(), ui::uiLocation_Right, {250,250}, {0,19} );
    m_handler_main->pushWnd(m_window_editor );
    m_handler_main->pushWnd(m_window_content );



    // Initializing of ChocolataSlicerFileSelector
    // ChocolataSlicerFileSelector::getInstance().setPerentWindow(getWindow() );

}
