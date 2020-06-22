#ifndef __CHOCOLATA_SLICER_FILE_SELECTOR_
#define __CHOCOLATA_SLICER_FILE_SELECTOR_


#include <stdio.h>
#include "cinder/Log.h"
#include "cinder/app/Window.h"

#include <string>
#include "__string.h"

#include "ui/uiWindow.h"
#include "ui/uiContentTree.h"
#include "ChocolataSlicerMesh.h"

#include "cinder/gl/Fbo.h"
#include "cinder/ImageIo.h"

/**
 * @brief Singleton class with window for viewing and loading objects to programs objects buffer.
 * You can call it by one line "ChocolataSlicerFileSelector::getInstance.open()"
*/
class ChocolataSlicerFileSelector {
    private : // Singleton definitions
        /**
         * @brief Functions makes deployment for this singleton class's components
        */
        void setup();

        /**
         * @brief Default constructor of singleton class
        */
        ChocolataSlicerFileSelector() : m_opened(false) { setup(); }

    public : // Main users functions
        static ChocolataSlicerFileSelector& getInstance() { static ChocolataSlicerFileSelector dialog; return dialog;  }


        /**
         * @brief Setting ChocolataSlicerFileSelector's parant window. Main window of FileSelector refers to scale of main
         * viewport.
         * 
         * @param perent_wnd It's reference to main window of program
        */
        void setPerentWindow(ci::app::WindowRef perent_wnd) { _perentWindowPtr = perent_wnd; }


        /**
         * @brief Opens system FileSelector to loading files by extentions
         * 
         * @param title Title of file selector wich loads your file
         * @param extentions Extentions of files wich can be loaded. Write it by line ex: "*.png | *.jpg"
         * 
         * @return Returns path of file to be load with one of seated extensions
        */
        char* openLoadingFileSelector(const char* title, const char* extentions );

        /**
         * @brief Function for opening ChocolataSlicerFileSelector and systems FileSelector. You selecting
         * a file and choising wich object will refers on it
         * 
         * @return Returns 1 if loaded something, or 0
        */
        bool open();


        /**
         * @brief Function for previewing ChocolataSlicerFileSelector's window. It contains object tree and
         * previewing area
        */
        void draw();

    private : // Main variables of ChocolataSlicerFileSelector. It must be hide of touching
        ui::uiWindowRef                     _windowPtr; // General purpose uiWindow of ChocolateSliceFileSelector

        ci::app::WindowRef                  _perentWindowPtr; // Parant window. Main programs wnd

        char*                               _lastPathRef; // Path to last loaded object

    private : // Parts of previewing area and actual objects for drawing 
        ci::gl::Texture2dRef                _texturePtr; // Texture ref for storing loaded texture object

        Mesh::_meshPtr_t                    _meshPtr; // Mesh ref for storing loaded mesh object

        ci::gl::GlslProgRef                 _shaderPtr; // Shader of loading model

        ci::gl::FboRef                      _FboPtr; // Frame buffer for drawing model loading by parts and fully defined model topology

        ci::CameraPersp                     _cameraPersp; // Camera for controling eye point

    private : // File extension verificator
        enum _FileExtention {
            _fileExtention_None             = 0,

            _fileExtention_Texture,

            _fileExtention_Mesh
        };
        _FileExtention                      _lastPathExtention; // Extention identificator of last loaded object


    public : // Variables for users access
        bool m_opened;

};



char* ChocolataSlicerFileSelector::openLoadingFileSelector(const char* title, const char* extentions ) {
    std::string cmd = "zenity --file-selection --title=\""; cmd += title;
    cmd += "\" --file-filter=\".png, .jpg, .jpeg, .stl, .obj, .amf, .3mf |";
    cmd += extentions; cmd += "|\"";

    FILE* p = popen(cmd.c_str(), "r");
    fgets(_lastPathRef, 1024, p);
    pclose(p);


    // Cutting _lastPathRef from endline symbol. _lastPathRef will contains clear path to file
    strcpy(_lastPathRef, (std::string(_lastPathRef).erase(std::string(_lastPathRef).find("\n"))).c_str());


    // Set extention of loaded file. Extantion can be texture of mesh format wich mantains ChocolataSlicer
    const std::string path = std::string(_lastPathRef );
    if ( (path.find(".png") != std::string::npos )  || (path.find(".jpg") != std::string::npos ) ||
         (path.find(".jpeg") != std::string::npos )
    ) {
        _lastPathExtention = _FileExtention::_fileExtention_Texture;
    } 
    else if ( (path.find(".stl") != std::string::npos )  || (path.find(".obj") != std::string::npos )) {
        _lastPathExtention = _FileExtention::_fileExtention_Mesh;
    }
    else {
        _lastPathExtention = _FileExtention::_fileExtention_None;
    }


    return _lastPathRef;
}


bool ChocolataSlicerFileSelector::open() {
    // Prepare variables before next file loading
    _lastPathExtention = _FileExtention::_fileExtention_None;
    ui::uiContentTree::getInstance()._selected = -1;
    strcpy(_lastPathRef, "");
    m_opened = true;


    openLoadingFileSelector("Select a file for loading", "*.png | *.jpg | *.jpeg | *.stl | *.obj | *.amf | *.3mf");


    CI_LOG_D("Opening file : \"" << _lastPathRef << "\"");

    // Checking file extention and load an object
    if (_lastPathExtention == _FileExtention::_fileExtention_Texture ) {    // Loading a texture
        CI_LOG_D("Loading file has IMAGE extension");
        try {
            _texturePtr = ci::gl::Texture2d::create( ci::loadImage(_lastPathRef), ci::gl::Texture2d::Format().mipmap() );
            if (_texturePtr->getAspectRatio() != 1 ) { CI_LOG_W("Loaded image isnt a texture" ); } 
            CI_LOG_D("Image loaded ~>" << " | wdt: " << _texturePtr->getWidth() << " | hgt: " << _texturePtr->getHeight() );
        } catch (ci::Exception& e) { CI_LOG_W("Image didnt load : " << e.what() );  }

    }
    else if (_lastPathExtention == _FileExtention::_fileExtention_Mesh ) {  // Loading a model
        CI_LOG_D("Loading file has MODEL extension");_meshPtr = make_mesh(Mesh::File::_STL, _lastPathRef );

        if (_str_find(_lastPathRef, ".stl") == 0 ) {
            printf("STL model loads. . .\n");
            _meshPtr = make_mesh(Mesh::File::_STL, _lastPathRef );
        }
        else if (_str_find(_lastPathRef, ".obj") == 0 ) {
            printf("OBJ model loads. . .\n");
            _meshPtr = make_mesh(Mesh::File::_OBJ, _lastPathRef );
        }
        // if (_str_find(_lastPathRef, ".stl") == 0 ) {
            // printf("STL model loads. . .\n");
        // }

        _meshPtr->stat();
        CI_LOG_D("Model loaded ~> trgs: " << _meshPtr->getTriangles() << " | vrcs: " << _meshPtr->getVertices() );
    }
    else {
        CI_LOG_W("ERR of loading : " << "Download model extension not supported" );
    }

}


void ChocolataSlicerFileSelector::setup() { 
    CI_LOG_D("ChocolataSlicerFileSelector inited");
    _lastPathRef = (char*)malloc(sizeof(char) * 1024);

    // UI preparing 
    _windowPtr = ui::uiWindow::create(ImVec2(), ImVec2(60,60), "ChocolataSlicerFileSelector", ui::uiLoaction_None, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );

    // Prepare shader
    try {
        _shaderPtr = ci::gl::GlslProg::create("/home/deins_one/Code/ChocolataSlicer/assets/shaders/default.vs.glsl", 
                                             "/home/deins_one/Code/ChocolataSlicer/assets/shaders/default.fs.glsl"
        );
    }
    catch (ci::Exception& ex) {
        CI_LOG_W("ERR : " << ex.what() );
    }

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
void ChocolataSlicerFileSelector::draw() {
    ImVec2 offsets = ImVec2(35,35);             // Dynamic values for changing

    // Set ChocolataSlicerFileSelector window focus
    ImGui::SetNextWindowFocus();

    _windowPtr->_size = ImVec2(_perentWindowPtr->getSize().x-(2*offsets.x), _perentWindowPtr->getSize().y-(2*offsets.y));
    _windowPtr->_pos = offsets;
    _windowPtr->Begin();
        ImGui::Columns(2, "ChocolataSlicerFileSelectorItems" );        // ChocolataSlicerFileSelectorItems items to be selected for object loading
            ImGui::SetColumnWidth(0, 250 );
            ImGui::Text("Content tree");
            ImGui::SameLine();
            ImGui::Text("(?)");
            ui::uiContentTree::__tooltip("Select item to wich tou  want load an object");
            ui::uiContentTree::getInstance().draw();
        ImGui::NextColumn();                                           // Main Previewing area for loaded objects to program
            ImGui::Text("Previewing area" );
            ImGui::SameLine();
            ImGui::Text("(?)");
            ui::uiContentTree::__tooltip("Area for previewing model or texture befor loading");
            ImGui::TextColored(ImVec4(0,0,0,0.5), "File path : %s", _lastPathRef );
            ImVec2 winSize = ImGui::GetWindowSize();


            /**
             * Priviewing loaded objects in scale of priviewing area.
             * Texture draws as 2d plate on screen without additional objects.
             * 
             * Meshes draws to separate FBO with other nonmove camera.
             * 
            */
            if (_lastPathExtention == _FileExtention::_fileExtention_Texture ) {             // Preview texture
                ImVec2 st_pos = ImGui::GetCursorScreenPos();
                ImVec2 en_pos = {_windowPtr->_pos.x+_windowPtr->_size.x-10, _windowPtr->_pos.y+_windowPtr->_size.y-50};
                float screnHight = en_pos.y - st_pos.y;
                ImVec2 imSize = ImVec2(_texturePtr->getHeight()*(screnHight/_texturePtr->getHeight())*_texturePtr->getAspectRatio(), _texturePtr->getHeight()*(screnHight/_texturePtr->getHeight()));
                ImGui::SetCursorScreenPos({ st_pos.x + ((en_pos.x-st_pos.x)/2 - imSize.x/2 ) , st_pos.y });
                ImGui::Image(_texturePtr, imSize, {0,1}, {1,0} );
                // ImGui::GetWindowDrawList()->AddRect(st_pos, en_pos, ImGui::GetColorU32({0.90196,0.29804,0.67451,1.0}) );
            }
            else if (_lastPathExtention == _FileExtention::_fileExtention_Mesh ) {          // Preview mesh
                ImVec2 st_pos = ImGui::GetCursorScreenPos();
                ImVec2 en_pos = {_windowPtr->_pos.x+_windowPtr->_size.x-10, _windowPtr->_pos.y+_windowPtr->_size.y-50};
                float screnHight = en_pos.y - st_pos.y;
                // ImVec2 imSize = ImVec2(_FboPtr->getWidth(), _FboPtr->getHeight() );
                ImVec2 imSize = ImVec2(480*(screnHight/480)*_FboPtr->getAspectRatio(), 480*(screnHight/480));
                ImGui::SetCursorScreenPos({ st_pos.x + ((en_pos.x-st_pos.x)/2 - imSize.x/2 ) , st_pos.y });
                // _FboTexturePtr
                ImGui::Image(_FboPtr->getColorTexture(), imSize, {0,1}, {1,0} );
            }


            /**
             * Buttons for applying actions. Before loading object you should shoice it in Object tree.
             * After selecting object you will be given some info aboud loading.
             * 
             * It contains two buttons: Cencel, Load
             * 
            */ {
                ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200, winSize.y+offsets.y-40) );
                ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetColorU32(ImGuiCol_WindowBg) );
                if (ImGui::Button("Cencel", ImVec2(90,30))) {
                    m_opened = false; ui::uiContentTree::getInstance()._selected = -1;
                }
                ImGui::PopStyleColor();

                ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-100, winSize.y+offsets.y-40) );
                if (ImGui::Button("Load", ImVec2(90,30))) {                     // Load an object 
                    if (ui::uiContentTree::getInstance()._selected != -1 && _lastPathExtention == _FileExtention::_fileExtention_Texture ) {          // If it is a texture
                        ui::uiContentTree::getInstance().ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_texturePtr = std::shared_ptr<ci::gl::Texture2d>(_texturePtr.get() );
                        _texturePtr.~__shared_ptr();
                        m_opened = false;
                    }
                    if (ui::uiContentTree::getInstance()._selected != -1 && _lastPathExtention == _FileExtention::_fileExtention_Mesh ) {               // If it is a mesh
                        // ui::uiContentTree::getInstance().ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_meshPtr = _meshPtr;
                        m_opened = false;
                    }
                }
            }


            /**
             * Users onformation about loading mode of current object. You can replace or
             * create new object in model
             * 
            */
            if (_lastPathExtention == _FileExtention::_fileExtention_Texture && ui::uiContentTree::getInstance()._selected >= 0 ) {         // Texture has been loaded
                if (ui::uiContentTree::getInstance()._items.at(ui::uiContentTree::getInstance()._selected)->_texturePtr == nullptr ) {
                    ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200-ImGui::CalcTextSize("Insert object texture to object ").x, winSize.y+offsets.y-20-(ImGui::CalcTextSize("Insert object texture to object").y/2)) );
                    ImGui::TextColored(ImVec4(0,0,0,0.5), "Insert texture item to object" );
                }
                else {
                    ImGui::SetCursorScreenPos(ImVec2(winSize.x+offsets.x-200-ImGui::CalcTextSize("Replace texture item of object ").x, winSize.y+offsets.y-20-(ImGui::CalcTextSize("Replace texture item of object").y/2)) );
                    ImGui::TextColored(ImVec4(0,0,0,0.5), "Replace texture item of object" );
                }
            } 
            else if (_lastPathExtention == _FileExtention::_fileExtention_Mesh && ui::uiContentTree::getInstance()._selected >= 0 ) {  // Model has been loaded
                /* ... */
            }


            /**
             * Update frame buffer if it is a mesh object. Clear and drow it to Fbo with multtsampling,
             * depth buffer and mipmaping
            */
            if (_lastPathExtention == _FileExtention::_fileExtention_Mesh ) {
	            ci::gl::ScopedViewport viewport(glm::vec2( 0.0f ), _FboPtr->getSize() );
                _FboPtr->bindFramebuffer();
                ImVec4 cl = ImGui::GetStyleColorVec4(ImGuiCol_WindowBg );
                ci::gl::clear(ci::Color(cl.x, cl.y, cl.z) );
                ci::gl::setMatrices(_cameraPersp );
                ci::gl::Batch::create(ci::geom::Teapot().subdivisions(16), ci::gl::getStockShader(ci::gl::ShaderDef().color() ) )-> draw();
                _FboPtr->unbindFramebuffer();
            }

        ImGui::Columns(1);


    _windowPtr->End();
}


#endif // __CHOCOLATA_SLICER_FILE_SELECTOR_


