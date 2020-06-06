#include "cinder/app/App.h"
#include "cinder/Log.h"

#include "cinder/CinderImGui.h"
#include "jsoncpp/json.h"



#include "ChocolataSlicer.h"

#include "ui/uiWindow.h"
#include "ui/uiWindowHandler.h"
#include "ui/uiViewport.h"
#include "ui/uiContentTree.h"

void ChocolataSlicer::setup() {
    CI_LOG_I("ChocolataApp ~> ChocolataSlicer version : " << __ChocolataSlicer_Version_ );

    // Window prepering
    std::ifstream configFile("assets/config/windowSettings.json" );
    if (configFile.is_open() ) {
        Json::Value windowCfg;
        configFile >> windowCfg;

        setWindowSize(glm::ivec2(windowCfg["windowSize"][0].asInt(), windowCfg["windowSize"][1].asInt()) );
        setWindowPos(glm::vec2(windowCfg["windowPos"][0].asInt(), windowCfg["windowPos"][1].asInt() ) );
        setFrameRate(windowCfg["windowFrameRate"].asInt() );

        CI_LOG_D("Window config loaded : " << "assets/config/windowSettings.json" << getElapsedSeconds() );
    } else CI_LOG_W("Window config didnt load : " << "assets/config/windowSettings.json" << getElapsedSeconds() );
    configFile.close();

    enablePowerManagement();


    // Main opengl Initializing
    m_camera.setPerspective(45, getWindow()->getAspectRatio(), 1, 1000 );
    m_camera.lookAt(glm::vec3(3, 2, 4));

	ci::gl::enableDepthWrite();
	ci::gl::enableDepthRead();



    // ImGui Initializing
    ImGui::Initialize();
    ImGui::StyleColorsLight();
    ImGui::GetIO().IniFilename = "assets/config/img.ini";
    ImGui::GetStyle().WindowRounding = 0;





    // Main Ui Initializing
    m_ui_viewport = ui::uiViewport::create(getWindow() );

    ui::uiContentTree::getInstance().pushItem(ui::uiContentItem::create("ModelObject:01"));
    ui::uiContentTree::getInstance().pushItem(ui::uiContentItem::create("ModelObject:02"));

    m_window_editor = ui::uiWindow::create({240, 240}, {60, 60}, "Editor", ui::uiLoaction_Top, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    m_window_content = ui::uiWindow::create({240, 240}, {360, 60}, "Content bar", ui::uiLoaction_Down, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    

    m_handler_main = ui::uiWindowHandler::create(getWindow(), ui::uiLoaction_Right, {250,250}, {0,19} );
    m_handler_main->pushWnd(m_window_editor );
    m_handler_main->pushWnd(m_window_content );

    
    // Initializing of ChocolataSlicerFileSelector
    ChocolataSlicerFileSelector::getInstance().setPerentWindow(getWindow() );

}
