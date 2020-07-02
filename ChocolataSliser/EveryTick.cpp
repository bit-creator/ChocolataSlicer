#include "ChocolataSlicer.h"
#include "cinder/CinderImGui.h"

#include "ui/uiWindow.h"
#include "ui/uiViewport.h"
#include "ui/uiWindowHandler.h"
#include "ui/uiContentTree.h"

// #include "ui/uiComponents.h"

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

            if (ImGui::BeginMenu("File"))  {
                // TODO: Clear all loaded files and buffers
                if (ImGui::MenuItem("New", "Ctrl+N")) {  }

                // TODO: Loading model ar textures to programs     echo "Debug"buffer. If it is model then create new object for it
                if (ImGui::MenuItem("Open...", "Ctrl+O")) { FileSelector::getInstance().open(FileSelector::_FileSelector_Type_Load ); }

                // TODO: showing list of recent files
                if (ImGui::BeginMenu("Open Recent..", "")) {  ImGui::Text("No Recent Files"); ImGui::EndMenu(); }
                ImGui::Separator();

                // TODO: Saving of 
                if (ImGui::BeginMenu("Save")) {
                    // if (ui::uiContentTree::getInstance()._selected >= 0) { if (ImGui::MenuItem("Current Object", "")) { } }
                    // else { ImGui::MenuItem("Current Object", "", nullptr, false); } 

                    if (ImGui::MenuItem("Scene Objects", "Ctrl+S")) { }
                    ImGui::EndMenu();
                }

                // TODO: only binary suggestions file formats
                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) {  }
                ImGui::Separator();

                // TODO: Utf-8 formats of files
                if (ImGui::MenuItem("Export", "")) {  }

                if (ImGui::BeginMenu("Export As...", "")) {
                    ImGui::Text("Utf-8 formats from Export item");
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))  {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Tools"))  {
                if (ImGui::MenuItem("Setings", "Ctrl+,")) {  }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))  {
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
        ui::uiContentTree::getInstance().draw();
        m_window_content->End();
    }

    if (FileSelector::getInstance().isOpen() ) {
        FileSelector::getInstance().draw();
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
