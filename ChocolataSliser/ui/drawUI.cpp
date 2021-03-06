#include "ChocolataSlicer.h"

#include "printingContext.h"
#include "ui/Notification/Notification.h"

#include "cinder/CinderImGui.h"

#include "ui/uiWindow.h"
#include "ui/uiViewport.h"
#include "ui/uiWindowHandler.h"
#include "ContentTree.h"

#include "ui/BarWindows/uiBarWindows.h"



void ChocolataSlicer::drawUI() {
    // TODO: Update handlers!!!
    m_handler_main->update();

    // TODO: Update viewport
    m_ui_viewport->Begin();
        // Menu bar
        if (ImGui::BeginMenuBar()) {

            if (ImGui::BeginMenu("File")) {
                // TODO: Clear all loaded files and buffers
                // if (ImGui::MenuItem("New", "Ctrl+N")) {  }


                if (ImGui::MenuItem("Open...", "Altl+O")) { FileSelector::getInstance().open(FileSelector::_FileSelector_Type_Load ); }


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
                // ImGui::Separator();
                // if (ImGui::BeginMenu("Save", false )) { ImGui::EndMenu(); }


                // TODO: only binary suggestions file formats
                // if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", nullptr, false )) {  }


                // TODO: Utf-8 formats of files
                // ImGui::Separator();
                // if (ImGui::MenuItem("Export", "", nullptr, false )) {  }


                // if (ImGui::BeginMenu("Export As...", false )) {
                    // ImGui::Text("Utf-8 formats from Export item");
                    // ImGui::EndMenu();
                // }


                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Esc/Ctrl+Q")) { quit(); }


                ImGui::EndMenu();
            }


            // TODO:
            if (ImGui::BeginMenu("Edit"))  {

                if (ImGui::MenuItem("Undo", "Ctrl+Z" )) {  }

                if (ImGui::MenuItem("Redo", "Ctrl+Y" )) {  }

                ImGui::EndMenu();
            }


            // TODO:
            if (ImGui::BeginMenu("Tools"))  {
                if (ImGui::MenuItem("Slice", "Ctrl+Shift+L" )) {  }

                if (ImGui::MenuItem("Print", "Ctrl+Shift+P" )) { PrintingContext::getInstance().open(); }


                // TODO:
                ImGui::Separator();
                // if (ImGui::BeginMenu("Addons", false)) { ImGui::EndMenu(); }


                if (ImGui::MenuItem("Setings", "Ctrl+,")) {  }

                ImGui::EndMenu();
            }


            // TODO:
            if (ImGui::BeginMenu("Help"))  {
                if (ImGui::MenuItem("Welcome", "")) { ui::UiWindows.welcome = true; }

                if (ImGui::MenuItem("Documentation", "")) { 
                    std::thread _sys( 
                        [](std::string _link) { 
                            std::string _cmd = "xdg-open "; _cmd += _link;
                            system(_cmd.c_str() );
                        },
                        __ChocolataSlicer_Documentation_Link_
                    );
                    _sys.detach();
                }

                // if (ImGui::MenuItem("Shortcuts", "Ctrl+Shift+O")) { ui::UiWindows.shortCuts = true; }

                // ImGui::Separator();
                // if (ImGui::MenuItem("Change log", "")) {  }

                // if (ImGui::MenuItem("Report issue", "")) {  }

                // ImGui::Separator();
                // if (ImGui::MenuItem("About", "Alt+A")) { ui::UiWindows.about = true; }
                ImGui::EndMenu();
            }


            // ViewMode
            static const Json::Value::Members _list = Json::Value::Members({"Shaded", "Wireframe", "Solid" } ); 
            if (ImGui::Combo("ViewMode", &_viewMode, _list ) ) {
                switch (_viewMode) {
                    case (0) : {
                        ci::gl::disableWireframe();
                        ContentTree::getInstance().swapShaders(ShaderTree::getInstance().velvetyShader() );
                        break;
                    }
                    case (1) : {
                        ci::gl::enableWireframe();
                        ContentTree::getInstance().swapShaders(ShaderTree::getInstance().colorShader() );
                        break;
                    }
                    case (2) : {
                        ci::gl::disableWireframe();
                        ContentTree::getInstance().swapShaders(ShaderTree::getInstance().solidShader() );
                        break;
                    }
                }
            }

            ImGui::EndMenuBar();
        }

    m_ui_viewport->End();

    // update all other
    if (m_window_editor->_opened ) {
        m_window_editor->Begin();
            if (ContentTree::getInstance()._selected != -1 ) {
                // Transforms
                if (ImGui::TreeNode("Transforms" )) {
                    if (ContentTree::getInstance()._selected != -1 ) {
                        ImGui::TextColored(ImVec4(0,0,0,0.7), "  Transforms ( X, Y, Z )");
                        ImGui::DragFloat3("Pos", &ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_position );
                        ImGui::DragFloat3("Scale", &ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_scale );
                        ImGui::DragFloat3("Rotate", &ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_rotate );

                        ImGui::Separator();
                        ImGui::Spacing();
                    }

                    ImGui::TreePop();
                }


                // Texture
                if (ImGui::TreeNode("Texture") ) {
                    if (ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_texturePtr != nullptr ) {
                        ImGui::Spacing();
                        ImGui::TextColored(ImVec4(0,0,0,0.7), "  Texture");

                        ImGui::Text("ID : %d", ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_texturePtr->getId() );
                        ImGui::Text("Label : %s", ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_texturePtr->getLabel().c_str() );

                        ImGui::Spacing();
                        glm::ivec2 size = ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_texturePtr->getSize();
                        ImGui::Text("Size  : %d | %d", size.x, size.y );

                        ImGui::Spacing();
                        // ImGui::Button("Edit", ImVec2(ImGui::GetWindowSize().x-(ImGui::GetStyle().WindowPadding.x*2), 20) );
                    }
                    else {
                        if (ImGui::Button("Add", ImVec2(ImGui::GetWindowSize().x-(ImGui::GetStyle().WindowPadding.x*2), 20)) ) {
                            FileSelector::getInstance().open(FileSelector::_FileSelector_Type_Load );
                        }
                    }

                    ImGui::Separator();
                    ImGui::Spacing();

                    ImGui::TreePop();
                }


                // Mesh
                if (ImGui::TreeNode("Mesh") ) {
                    if (ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_batchPtr != nullptr ) {
                        ImGui::Spacing();
                        ImGui::TextColored(ImVec4(0,0,0,0.7), "  Mesh");


                        // ImGui::Text("Vertices : %d", ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_meshPtr->getVertices() );
                        // ImGui::Text("Triangles : %d", ContentTree::getInstance()._items.at(ContentTree::getInstance()._selected)->_meshPtr->getTriangles() );

                        ImGui::Spacing();
                    }
                    else {
                        if (ImGui::Button("Add", ImVec2(ImGui::GetWindowSize().x-(ImGui::GetStyle().WindowPadding.x*2), 20)) ) {
                            FileSelector::getInstance().open(FileSelector::_FileSelector_Type_Load );
                        }
                    }

                    ImGui::Separator();
                    ImGui::Spacing();

                    ImGui::TreePop();
                }

            }
            else {
                ImGui::TextColored(ImVec4(0,0,0,0.4), "  No selected object");
            }

        m_window_editor->End();
    }

    if (m_window_content->_opened ) {
        m_window_content->Begin();
        ContentTree::getInstance().drawObjectsToUiList();
        if (ContentTree::getInstance()._items.size() < 1 ) { ImGui::TextColored(ImVec4(0,0,0, 0.4), "No objects"); }
        m_window_content->End();
    }


    if (FileSelector::getInstance().isOpen() ) {
        FileSelector::getInstance().draw();
    }


    if (PrintingContext::getInstance().isOpen() ) {
        PrintingContext::getInstance().draw();
    }


    Notifications::GetInstance().draw();

    if (ui::UiWindows.about == true ) {
        ui::showAboutWindow();
    }

}
