#include "cinder/app/App.h"
#include "cinder/Display.h"
#include "cinder/Log.h"

#include "cinder/CinderImGui.h"


#include "ChocolataSlicer.h"

#include "ui/uiWindow.h"
#include "ui/uiWindowHandler.h"
#include "ui/uiViewport.h"
#include "ContentTree.h"

#include "ShaderTree.h"
#include "cinder/Serial.h"

void ChocolataSlicer::setup() {
    CHOCOLATA_SLIER_PROFILE_BEGIN_SESSION("startProfiling", "assets/config/appStartProfiling.json");

    {
        CI_LOG_I("ChocolataApp ~> ChocolataSlicer version : " << __ChocolataSlicer_Version_ );
        CI_LOG_I("ChocolataApp ~> DisplaySize : " << getDisplay()->getSize().x << "px | " << getDisplay()->getSize().y << "px" );
        CI_LOG_I("ChocolataApp ~> WindowSize : " << getWindowSize().x << "px | " << getWindowSize().y << "px\n" );


        CHOCOLATA_SLIER_PROFILE_FUNCTION();

        // Window preparing
        {
            CHOCOLATA_SLIER_PROFILE_SCOPE("Window settings");
            enablePowerManagement();
            setWindowPos( glm::ivec2(  (getDisplay()->getSize().x/2) - (getWindowSize().x/2),
                                       (getDisplay()->getSize().y/2) - (getWindowSize().y/2) )
            );
        }



        // Main opengl Initializing
        {
            CHOCOLATA_SLIER_PROFILE_SCOPE("Init OpenGl");
            {
                CHOCOLATA_SLIER_PROFILE_SCOPE("Setting main camera proporties");
                m_camera.setPerspective(45, getWindow()->getAspectRatio(), 1, 1000 );
                m_camera.lookAt(glm::vec3(3, 2, 4));
                m_cameraui = ci::CameraUi(&m_camera );
            }

            {
                CHOCOLATA_SLIER_PROFILE_SCOPE("Setting openGl components");
	            ci::gl::enableDepthWrite();
	            ci::gl::enableDepthRead();
            }
        }



        // ImGui Initializing
        {
            CHOCOLATA_SLIER_PROFILE_SCOPE("Init ImGui");

            {
                CHOCOLATA_SLIER_PROFILE_SCOPE("Main proporties");
                ImGui::Initialize();
                ImGui::StyleColorsLight();
                ImGui::GetIO().IniFilename = "assets/config/imGuiReserveConfig.ini";
                ImGui::GetStyle().WindowRounding = 0;
            }

            {
                CHOCOLATA_SLIER_PROFILE_SCOPE("Load fonts");
                ImGui::GetIO().Fonts->AddFontDefault();
                static ImWchar ranges[] = { 0xf000, 0xf3ff, 0 };
                ImFontConfig config;
                config.MergeMode = true;
                ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/fa-solid-900.ttf", 12.0f, &config, ranges);
                ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/fa-brands-400.ttf", 12.0f, &config, ranges);
            }
        }


        // Main Ui Initializing
        {
            CHOCOLATA_SLIER_PROFILE_SCOPE("Init MainUI");
            m_ui_viewport = ui::uiViewport::create(getWindow() );

            m_window_editor = ui::uiWindow::create({240, 240}, {60, 60}, "Proporties", ui::uiLocation_Top, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
            m_window_content = ui::uiWindow::create({240, 240}, {360, 60}, "Content bar", ui::uiLocation_Down, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

            m_handler_main = ui::uiWindowHandler::create(getWindow(), ui::uiLocation_Right, {250,250}, {0,19} );
            m_handler_main->pushWnd(m_window_editor );
            m_handler_main->pushWnd(m_window_content );
    
            // Notifications
            std::string _vs = "Current version is : "; _vs += __ChocolataSlicer_Version_;
            Notifications::GetInstance().addNotif( Notif { "Slicer version", _vs.c_str(), __ChocolataSlicer_Link_, ci::log::LEVEL_INFO  } );

            // Printing Context
            PrintingContext::getInstance().initPrinterBoard();
        }

        // Mesh::_meshPtr_t ms = make_mesh(Mesh::File::_STL, "test/printersHouseLogo.stl" );
        // ContentItemRef it0 = ContentTree::getInstance().pushItem(
            // ContentItem::create(
                // "HouseLogo",
                // ci::gl::Batch::create(*ms, ShaderTree::getInstance().velvetyShader() )
                // ci::gl::Texture2d::create(ci::loadImage("test/Ico.png") )
            // ) 
        // );
        // ContentTree::getInstance()._items.back()->_rotate = {-1.6,0,0};

    }

    CHOCOLATA_SLIER_PROFILE_END_SESSION();
    CHOCOLATA_SLIER_PROFILE_BEGIN_SESSION("processProfiling", "assets/config/appProcessProfiling.json");
}
