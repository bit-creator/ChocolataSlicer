#include "ChocolataSlicer.h"
#include "cinder/CinderImGui.h"

#include "ui/uiWindow.h"
#include "ui/uiViewport.h"
#include "ui/uiWindowHandler.h"
#include "ContentTree.h"

#include "ui/uiBarWindows.h"

void ChocolataSlicer::resize() {
    m_camera.setPerspective(25, getWindowAspectRatio(), 1, 600 );
	ci::gl::setMatrices(m_camera );

    m_cameraui.setWindowSize(getWindowSize() );
}

void ChocolataSlicer::update() {
    drawUI();

}

void ChocolataSlicer::drawUI() {
    // TODO: Update handlers!!!
    m_handler_main->update();

    // TODO: Update viewport
    m_ui_viewport->Begin();
        // Menu bar
        if (ImGui::BeginMenuBar()) {

            if (ImGui::BeginMenu("File")) {
                // TODO: Clear all loaded files and buffers
                if (ImGui::MenuItem("New", "Ctrl+N")) {  }


                if (ImGui::MenuItem("Open...", "Ctrl+O")) { FileSelector::getInstance().open(FileSelector::_FileSelector_Type_Load ); }


                // showing list of recent files
                if (ImGui::BeginMenu("Open Recent..", (!FileSelector::getInstance()._recentFiles["recentFiles"].size() ? false : true) )) {  
                    for (int i = FileSelector::getInstance()._recentFiles["recentFiles"].size()-1; i >= 0 ; i-- ) {
                        if (ImGui::MenuItem(FileSelector::getInstance()._recentFiles["recentFiles"][i].asCString()) ) {
                            FileSelector::getInstance().open(FileSelector::getInstance()._recentFiles["recentFiles"][i].asCString() );
                        }
                    }

                    ImGui::EndMenu();
                }


                // TODO: Saving off
                ImGui::Separator();
                if (ImGui::BeginMenu("Save", false )) { ImGui::EndMenu(); }


                // TODO: only binary suggestions file formats
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", nullptr, false )) {  }


                // TODO: Utf-8 formats of files
                ImGui::Separator();
                if (ImGui::MenuItem("Export", "", nullptr, false )) {  }


                if (ImGui::BeginMenu("Export As...", false )) {
                    ImGui::Text("Utf-8 formats from Export item");
                    ImGui::EndMenu();
                }


                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Esc/Ctrl+Q")) { quit(); }


                ImGui::EndMenu();
            }


            // TODO:
            if (ImGui::BeginMenu("Edit"))  { ImGui::EndMenu(); }


            // TODO:
            if (ImGui::BeginMenu("Tools"))  {
                if (ImGui::MenuItem("Slice", "Ctrl+Shift+L" )) {  }

                if (ImGui::MenuItem("Print", "Ctrl+Shift+P" )) {  }


                // TODO:
                ImGui::Separator();


                if (ImGui::BeginMenu("View mode")) {
                    ImGui::EndMenu();
                }


                if (ImGui::BeginMenu("Addons", false)) {
                    ImGui::EndMenu();
                }


                if (ImGui::MenuItem("Setings", "Ctrl+,")) {  }

                ImGui::EndMenu();
            }


            // TODO:
            if (ImGui::BeginMenu("Help"))  {
                if (ImGui::MenuItem("Welcome", "")) { ui::UiWindows.welcome = true; }
                if (ImGui::MenuItem("Documentation", "")) {  }
                if (ImGui::MenuItem("Shortcuts", "Ctrl+Shift+O")) { ui::UiWindows.shortCuts = true; }

                ImGui::Separator();
                if (ImGui::MenuItem("Change log", "")) {  }

                if (ImGui::MenuItem("Report issue", "")) {  }

                ImGui::Separator();
                if (ImGui::MenuItem("About", "Alt+A")) { ui::UiWindows.about = true; }
                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }

    m_ui_viewport->End();

    // update all other
    if (m_window_editor->_opened ) {
        m_window_editor->Begin();
        m_window_editor->End();
    }
    if (m_window_content->_opened ) {
        m_window_content->Begin();
        ContentTree::getInstance().draw();
        m_window_content->End();
    }

    if (FileSelector::getInstance().isOpen() ) {
        FileSelector::getInstance().draw();
    }



    if (ui::UiWindows.about == true ) {
        ui::showAboutWindow();
    }

    // General Info
    // ImGui::TextColored(ImVec4(1,1,1,0.4), "Vertices: %d   Fragments: %d", 0, 0);

    // Slice/Print button
    // ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4);
    // ImGui::SetCursorScreenPos(ImVec2(10, getWindow()->getSize().y - 30 -10  ));
    // if (!m_sliced ) { if (ImGui::Button("Slice", ImVec2(120, 30) ))             { m_sliced = true; } }      // Slice
    // else if (ImGui::Button("Print", ImVec2(120, 30) ))                          { }                         // Print
    // ImGui::PopStyleVar();

}



void ChocolataSlicer::draw() {
    ci::gl::clear(ci::Color::gray(0.2) );
    ci::gl::setMatrices(m_camera );


    // Draw Grid + Axises
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


    ci::gl::color(0.7,0.7,0.7);
    _bt->getGlslProg()->uniform("ciEyePos", m_camera.getEyePoint() );
    _bt->getGlslProg()->uniform("ciCameraUp", glm::cross(glm::normalize(m_camera.getViewDirection() ), glm::vec3(1,0,0)) );
    _bt->draw();

}


void ChocolataSlicer::mouseDrag(ci::app::MouseEvent event ) {
	m_cameraui.mouseDrag( event );
}


void ChocolataSlicer::mouseDown(ci::app::MouseEvent event ) {
    m_cameraui.mouseDown( event );
}

void ChocolataSlicer::mouseWheel(ci::app::MouseEvent event ) {
    m_cameraui.mouseWheel( event );
}


void ChocolataSlicer::keyDown(ci::app::KeyEvent event ) {
    if(event.getCode() == ci::app::KeyEvent::KEY_ESCAPE ) quit();
}