#include "FileSelector.h"
#include "fileConfig.h"
#include "thread"

void FileSelector::destroy() {
    _texturePtr.reset();
    _shaderPtr.reset();
    _FboPtr.reset();

}

void FileSelector::initFileSelector() {
    CI_LOG_D("initialize");
    _lastPath = (char*)malloc(sizeof(char) * 1024);

    // UI preparing 
    _windowPtr = ui::uiWindow::create( ImVec2(), ImVec2(60,60), "FileSelector", ui::uiLocation_None,
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoCollapse
    );

    _windowBlurPtr = ui::uiWindow::create( ImVec2(), ImVec2(), "FileSelectorBlur", ui::uiLocation_None, 
                                        ImGuiWindowFlags_NoDecoration |
                                        ImGuiWindowFlags_NoNavInputs |
                                        ImGuiWindowFlags_NoFocusOnAppearing
    );


    // Frame buffer preparing
    ci::gl::Fbo::Format fboFormat;
    fboFormat.samples(8 );
    glm::ivec2 fboResolution = glm::ivec2(640, 480);
	_FboPtr = ci::gl::Fbo::create(fboResolution.x, fboResolution.y, fboFormat );


    // Camera preparing
    _cameraPersp.setPerspective(50, float(fboResolution.x/fboResolution.y), 1, 700 );
    _cameraPersp.setEyePoint({12,8,16});
    _cameraPersp.lookAt({0,0,0});
}





// FIXME:
void FileSelector::draw() {
    ImVec2 offsets = ImVec2(35,35);             // Dynamic values for changing

    ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.23137,0.20784,0.21961,0.5 } );
    _windowBlurPtr->_size = ImVec2(_perentWindowPtr->getSize().x, _perentWindowPtr->getSize().y );
    _windowBlurPtr->Begin();
    ImGui::PopStyleColor();

    // Set FileSelector window focus
    ImGui::SetNextWindowFocus();

    _windowPtr->_size = ImVec2(_perentWindowPtr->getSize().x-(2*offsets.x), _perentWindowPtr->getSize().y-(2*offsets.y));
    _windowPtr->_pos = offsets;
    _windowPtr->Begin();
        ImGui::Columns(2, "FileSelectorItems" );        // FileSelectorItems items to be selected for object loading
            ImGui::SetColumnWidth(0, 250 );
            ImGui::TextColored(ImVec4(0,0,0,0.8), "Content tree");
            ImGui::SameLine();
            ImGui::Text("(?)");
            ui::uiContentTree::__tooltip("Select item to which tou  want load an object");
            ImGui::Spacing(); ImGui::Spacing();
            ui::uiContentTree::getInstance().draw();
        ImGui::NextColumn();                                           // Main Previewing area for loaded objects to program
            ImGui::TextColored(ImVec4(0,0,0,0.8), "Previewing area");
            ImGui::SameLine();
            ImGui::Text("(?)");
            ui::uiContentTree::__tooltip("Area for previewing model or texture befor loading");
            ImGui::Separator();
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0,0,0,0.5), "%s", _lastPath );
            ImVec2 winSize = ImGui::GetWindowSize();


            /**
             * Priviewing loaded objects in scale of priviewing area.
             * Texture draws as 2d plate on screen without additional objects.
             * 
             * Meshes draws to separate FBO with other nonmove camera.
             * 
            */
            if (_lastPathExtention == _File_Extention::_File_Extention_Texture ) {
                ImVec2 st_pos = ImGui::GetCursorScreenPos();
                ImVec2 en_pos = {_windowPtr->_pos.x+_windowPtr->_size.x-10, _windowPtr->_pos.y+_windowPtr->_size.y-50};
                float screenHight = en_pos.y - st_pos.y;
                ImVec2 imSize = ImVec2(_texturePtr->getHeight()*(screenHight/_texturePtr->getHeight())*_texturePtr->getAspectRatio(), _texturePtr->getHeight()*(screenHight/_texturePtr->getHeight()));
                ImGui::SetCursorScreenPos({ st_pos.x + ((en_pos.x-st_pos.x)/2 - imSize.x/2 ) , st_pos.y });
                ImGui::Image(_texturePtr, imSize, {0,1}, {1,0} );
            }
            else if (_lastPathExtention == _File_Extention::_File_Extention_Mesh ) {
                ImVec2 st_pos = ImGui::GetCursorScreenPos();
                ImVec2 en_pos = {_windowPtr->_pos.x+_windowPtr->_size.x-10, _windowPtr->_pos.y+_windowPtr->_size.y-50};
                float screenHight = en_pos.y - st_pos.y;
                ImVec2 imSize = ImVec2(480*(screenHight/480)*_FboPtr->getAspectRatio(), 480*(screenHight/480));
                ImGui::SetCursorScreenPos({ st_pos.x + ((en_pos.x-st_pos.x)/2 - imSize.x/2 ) , st_pos.y });
                ImGui::Image(_FboPtr->getColorTexture(), imSize, {0,1}, {1,0} );
            }


            /**
             * Buttons for applying actions. Before loading object you should choice it in Object tree.
             * After selecting object you will be given some info about loading.
             * 
             * It contains two buttons: Cancel, Load
             * 
            */  {
                ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200, winSize.y+offsets.y-40) );
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_WindowBg) );
                if (ImGui::Button("Cancel", ImVec2(90,30))) {
                    m_opened = false; ui::uiContentTree::getInstance()._selected = -1;
                }
                
                if (ui::uiContentTree::getInstance()._selected >= 0)
                    ImGui::PopStyleColor();

                ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-100, winSize.y+offsets.y-40) );
                if (ImGui::Button("Load", ImVec2(90,30))) {
                    if (ui::uiContentTree::getInstance()._selected != -1 && _lastPathExtention == _File_Extention::_File_Extention_Texture ) {
                        ui::uiContentTree::getInstance().ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_texturePtr.swap(_texturePtr);

                        m_opened = false;
                    }
                    if (ui::uiContentTree::getInstance()._selected != -1 && _lastPathExtention == _File_Extention::_File_Extention_Mesh ) {
                        m_opened = false;
                    }
                }
                
                if (ui::uiContentTree::getInstance()._selected == -1)
                    ImGui::PopStyleColor();
            }


            /**
             * Users information about loading mode of current object. You can replace or
             * create new object in model
             * 
            */
            if (_lastPathExtention == _File_Extention::_File_Extention_Texture && ui::uiContentTree::getInstance()._selected >= 0 ) {
                if (ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_texturePtr == nullptr ) {
                    ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200-ImGui::CalcTextSize("Insert object texture to object ").x, winSize.y+offsets.y-20-(ImGui::CalcTextSize("Insert object texture to object").y/2)) );
                    ImGui::TextColored(ImVec4(0,0,0,0.5), "Insert texture item to object" );
                }
                else {
                    ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200-ImGui::CalcTextSize("Replace texture item of object ").x, winSize.y+offsets.y-20-(ImGui::CalcTextSize("Replace texture item of object").y/2)) );
                    ImGui::TextColored(ImVec4(0,0,0,0.5), "Replace texture item of object" );
                }
            }
            else if (_lastPathExtention == _File_Extention::_File_Extention_Mesh && ui::uiContentTree::getInstance()._selected >= 0 ) {
                /* ... */
            }


            /**
             * Update frame buffer if it is a mesh object. Clear and drow it to Fbo with multtsampling,
             * depth buffer and mipmaping
            */
            if (_lastPathExtention == _File_Extention::_File_Extention_Mesh ) {
	            ci::gl::ScopedViewport viewport(glm::vec2( 0.0f ), _FboPtr->getSize() );
                _FboPtr->bindFramebuffer();
                ImVec4 cl = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg );
                ci::gl::clear(ci::Color(cl.x, cl.y, cl.z) );
                ci::gl::setMatrices(_cameraPersp );
                /* Draw model */
                ci::gl::Batch::create(ci::geom::Teapot().subdivisions(16), ci::gl::getStockShader(ci::gl::ShaderDef().color() ) )-> draw();
                _FboPtr->unbindFramebuffer();
            }

        ImGui::Columns(1);


    _windowPtr->End();
    _windowBlurPtr->End();
}




bool FileSelector::open(_FileSelector_Type type ) {
    _texturePtr.reset();

    CI_LOG_I("File selector opened in mode : " << (type == _FileSelector_Type_Load ? "FileSelector_Type_Load" : "FileSelector_Type_Save") ); 
    m_opened = true;

    openLoadingFileSelector(_File_Extention::_File_Extention_None );

}


bool FileSelector::openLoadingFileSelector(_File_Extention extention ) {
    std::string title = (extention == _File_Extention::_File_Extention_None ? "Select an object" : 
        (extention == _File_Extention::_File_Extention_Texture ? "Select a Texture" : "Select a Mesh" ) 
    );

    std::string extentions = (extention == _File_Extention::_File_Extention_None ? "*3mf, *amf, *stl, *obj, *png, *jpg, *jpeg | *3mf | *amf | *stl | *obj | *png | *jpg | *jpeg" : 
        (extention == _File_Extention::_File_Extention_Texture ? "*png, *jpg, *jpeg | *png | *jpg | *jpeg" : 
        "*3mf, *amf, *stl, *obj | *3mf | *amf | *stl | *obj" ) 
    );

    _lastPathExtention = extention;
    strcpy(_lastPath, "");

    // System call
    std::string command = "zenity --file-selection ";
    command += "--title=\"" + title + "\" ";
    command += "--file-filter=\"" + extentions + "\" ";

    // Execute command
    FILE* p = popen(command.c_str(), "r");
    fgets(_lastPath, 1024, p);
    pclose(p);

    // Exception situation
    if (strlen(_lastPath) <= 6 ) {
        m_opened = false;
        return false;
    }

    // Cutting _lastPathRef from endline symbol. _lastPathRef will contains clear path to file
    strcpy(_lastPath, (std::string(_lastPath).erase(std::string(_lastPath).find("\n"))).c_str());
    CI_LOG_I("Selected object : " << _lastPath << "\n" );

    // Load an object
    loadObject();


    return true;
}


void FileSelector::loadObject( ) {
    if (strlen(_lastPath) <= 4 ) {
        m_opened = false;
        return;
    }

    if (_lastPathExtention == _File_Extention::_File_Extention_None ) {
        if ( (_str_find(_lastPath, ".png") == 0 ) ||
             (_str_find(_lastPath, ".jpg") == 0 ) ||
             (_str_find(_lastPath, ".jpeg") == 0 )
        ) {
            _lastPathExtention = _File_Extention::_File_Extention_Texture;
        }

        else if ( (_str_find(_lastPath, ".3mf") == 0 ) ||
                  (_str_find(_lastPath, ".amf") == 0 ) ||
                  (_str_find(_lastPath, ".stl") == 0 ) ||
                  (_str_find(_lastPath, ".obj") == 0 )
        ) {
            _lastPathExtention = _File_Extention::_File_Extention_Mesh;
        }

    }

    if (_lastPathExtention == _File_Extention::_File_Extention_Texture ) {
        _texturePtr = ci::gl::Texture2d::create(ci::loadImage(_lastPath), ci::gl::Texture2d::Format().mipmap() );
    }

    else if (_lastPathExtention == _File_Extention::_File_Extention_Mesh ) {
        /* ... */
    }

}