#include "FileSelector.h"


void FileSelector::initFileSelector() {
    CI_LOG_D("initialize");

    // UI preparing 
    _windowPtr = ui::uiWindow::create(ImVec2(), ImVec2(60,60), "FileSelector", ui::uiLocation_None, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );

    // Prepare shader
    // try {
        // _shaderPtr = ci::gl::GlslProg::create(ci::loadFile("assets/shaders/default.vs.glsl"), 
                                            //  ci::loadFile("assets/shaders/default.fs.glsl")
        // );
    // }
    // catch (ci::Exception& ex) {
        // CI_LOG_W("ERR : " << ex.what() );
    // }

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

    // Set FileSelector window focus
    ImGui::SetNextWindowFocus();

    // _windowPtr->_size = ImVec2(_perentWindowPtr->getSize().x-(2*offsets.x), _perentWindowPtr->getSize().y-(2*offsets.y));
    // _windowPtr->_pos = offsets;
    // _windowPtr->Begin();
        // ImGui::Columns(2, "FileSelectorItems" );        // FileSelectorItems items to be selected for object loading
            // ImGui::SetColumnWidth(0, 250 );
            // ImGui::Text("Content tree");
            // ImGui::SameLine();
            // ImGui::Text("(?)");
            // ui::uiContentTree::__tooltip("Select item to wich tou  want load an object");
            // ui::uiContentTree::getInstance().draw();
        // ImGui::NextColumn();                                           // Main Previewing area for loaded objects to program
            // ImGui::Text("Previewing area" );
            // ImGui::SameLine();
            // ImGui::Text("(?)");
            // ui::uiContentTree::__tooltip("Area for previewing model or texture befor loading");
            // ImGui::TextColored(ImVec4(0,0,0,0.5), "File path : %s", _lastPathRef );
            // ImVec2 winSize = ImGui::GetWindowSize();


            /**
             * Priviewing loaded objects in scale of priviewing area.
             * Texture draws as 2d plate on screen without additional objects.
             * 
             * Meshes draws to separate FBO with other nonmove camera.
             * 
            */
            // if (_lastPathExtention == _FileExtention::_fileExtention_Texture ) {             // Preview texture
                // ImVec2 st_pos = ImGui::GetCursorScreenPos();
                // ImVec2 en_pos = {_windowPtr->_pos.x+_windowPtr->_size.x-10, _windowPtr->_pos.y+_windowPtr->_size.y-50};
                // float screnHight = en_pos.y - st_pos.y;
                // ImVec2 imSize = ImVec2(_texturePtr->getHeight()*(screnHight/_texturePtr->getHeight())*_texturePtr->getAspectRatio(), _texturePtr->getHeight()*(screnHight/_texturePtr->getHeight()));
                // ImGui::SetCursorScreenPos({ st_pos.x + ((en_pos.x-st_pos.x)/2 - imSize.x/2 ) , st_pos.y });
                // ImGui::Image(_texturePtr, imSize, {0,1}, {1,0} );
                // ImGui::GetWindowDrawList()->AddRect(st_pos, en_pos, ImGui::GetColorU32({0.90196,0.29804,0.67451,1.0}) );
            // }
            // else if (_lastPathExtention == _FileExtention::_fileExtention_Mesh ) {          // Preview mesh
                // ImVec2 st_pos = ImGui::GetCursorScreenPos();
                // ImVec2 en_pos = {_windowPtr->_pos.x+_windowPtr->_size.x-10, _windowPtr->_pos.y+_windowPtr->_size.y-50};
                // float screnHight = en_pos.y - st_pos.y;
                // ImVec2 imSize = ImVec2(_FboPtr->getWidth(), _FboPtr->getHeight() );
                // ImVec2 imSize = ImVec2(480*(screnHight/480)*_FboPtr->getAspectRatio(), 480*(screnHight/480));
                // ImGui::SetCursorScreenPos({ st_pos.x + ((en_pos.x-st_pos.x)/2 - imSize.x/2 ) , st_pos.y });
                // _FboTexturePtr
                // ImGui::Image(_FboPtr->getColorTexture(), imSize, {0,1}, {1,0} );
            // }


            /**
             * Buttons for applying actions. Before loading object you should shoice it in Object tree.
             * After selecting object you will be given some info aboud loading.
             * 
             * It contains two buttons: Cencel, Load
             * 
            */ // {
                // ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200, winSize.y+offsets.y-40) );
                // ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_WindowBg) );
                // if (ImGui::Button("Cencel", ImVec2(90,30))) {
                    // m_opened = false; ui::uiContentTree::getInstance()._selected = -1;
                // }
                // ImGui::PopStyleColor();

                // ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-100, winSize.y+offsets.y-40) );
                // if (ImGui::Button("Load", ImVec2(90,30))) {                     // Load an object 
                    // if (ui::uiContentTree::getInstance()._selected != -1 && _lastPathExtention == _FileExtention::_fileExtention_Texture ) {          // If it is a texture
                        // ui::uiContentTree::getInstance().ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_texturePtr = std::shared_ptr<ci::gl::Texture2d>(_texturePtr.get() );
                        // _texturePtr.~__shared_ptr();
                        // m_opened = false;
                    // }
                    // if (ui::uiContentTree::getInstance()._selected != -1 && _lastPathExtention == _FileExtention::_fileExtention_Mesh ) {               // If it is a mesh
                        // ui::uiContentTree::getInstance().ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_meshPtr = _meshPtr;
                        // m_opened = false;
                    // }
                // }
            // }


            /**
             * Users onformation about loading mode of current object. You can replace or
             * create new object in model
             * 
            */
            // if (_lastPathExtention == _FileExtention::_fileExtention_Texture && ui::uiContentTree::getInstance()._selected >= 0 ) {         // Texture has been loaded
                // if (ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_texturePtr == nullptr ) {
                    // ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200-ImGui::CalcTextSize("Insert object texture to object ").x, winSize.y+offsets.y-20-(ImGui::CalcTextSize("Insert object texture to object").y/2)) );
                    // ImGui::TextColored(ImVec4(0,0,0,0.5), "Insert texture item to object" );
                // }
                // else {
                    // ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200-ImGui::CalcTextSize("Replace texture item of object ").x, winSize.y+offsets.y-20-(ImGui::CalcTextSize("Replace texture item of object").y/2)) );
                    // ImGui::TextColored(ImVec4(0,0,0,0.5), "Replace texture item of object" );
                // }
            // } 
            // else if (_lastPathExtention == _FileExtention::_fileExtention_Mesh && ui::uiContentTree::getInstance()._selected >= 0 ) {  // Model has been loaded
                // /* ... */
            // }


            /**
             * Update frame buffer if it is a mesh object. Clear and drow it to Fbo with multtsampling,
             * depth buffer and mipmaping
            */
            // if (_lastPathExtention == _FileExtention::_fileExtention_Mesh ) {
	            // ci::gl::ScopedViewport viewport(glm::vec2( 0.0f ), _FboPtr->getSize() );
                // _FboPtr->bindFramebuffer();
                // ImVec4 cl = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg );
                // ci::gl::clear(ci::Color(cl.x, cl.y, cl.z) );
                // ci::gl::setMatrices(_cameraPersp );
                // ci::gl::Batch::create(ci::geom::Teapot().subdivisions(16), ci::gl::getStockShader(ci::gl::ShaderDef().color() ) )-> draw();
                // _FboPtr->unbindFramebuffer();
            // }

        // ImGui::Columns(1);


    // _windowPtr->End();
}




bool FileSelector::open() {
    CI_LOG_I("File selector opened"); 
    
    m_opened = true;
}