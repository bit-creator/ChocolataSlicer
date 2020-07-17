#ifndef __CHOCOLATA_SLICER_FILE_SELECTOR_
#define __CHOCOLATA_SLICER_FILE_SELECTOR_


#include <stdio.h>
#include "cinder/Log.h"
#include "cinder/app/Window.h"

#include "cstringFunctions.h"
#include "fileConfig.h"

#include "ui/uiWindow.h"
#include "ui/uiContentTree.h"

#include "jsonConfig.h"

/**
 * @brief Singleton class with window for viewing and loading objects to programs objects buffer.
 * You can call it by one line "FileSelector::getInstance.open()"
*/
class FileSelector {
    public :
        enum _FileSelector_Type {
            _FileSelector_Type_Load = 0,
            _FileSelector_Type_Save
        };

    private : // Singleton definitions
        /**
         * @brief Default constructor of singleton FileSelector class
        */
        FileSelector()  : m_opened(false) {  initFileSelector(); }


        /**
         * @brief Function to set default values of singleton class 
        */
        void initFileSelector();


    public : // Main users functions
        static FileSelector& getInstance() { static FileSelector dialog; return dialog;  }


        /**
         * @brief Setting FileSelector's parant window. Main window of FileSelector refers to scale of main
         * viewport.
         * 
         * @param perent_wnd It's reference to main window of program
        */
        void setPerentWindow(ci::app::WindowRef perent_wnd) { _perentWindowPtr = perent_wnd; }


        /**
         * @brief Opens system FileSelector to load files by extentions
         * 
         * @param extentions Extentions of files which can be loaded. Write it by line ex: "*.png | *.jpg"
         * 
         * @return Returns true if some path selected
        */
        bool openLoadingFileSelector(_File_Extention extention );


        /**
         * @brief Function for opening FileSelector and systems FileSelector. You selecting
         * a file and choosing which object will refers on it
         * 
         * @return Returns 1 if loaded something, or 0
        */
        bool open(_FileSelector_Type type );

        /**
         * @brief Function for opening FileSelector without systems FileSelector
         * 
         * @return Returns 1 if loaded something, or 0
        */
        bool open(const char* path );

        // TODO:
        void loadObject();

        /**
         * @brief Function for previewing FileSelector's window. It contains object tree and
         * previewing area
        */
        void draw();


        /**
         * @brief Function to clean dinamically reserved memory
        */
        void destroy();


        /**
         * @brief Function check if FileSelector is open
         * 
         * @return Returns m_opened vale
        */
        bool isOpen() { return m_opened; }


        /**
         * @brief Function check if FileSelector is empty from objects
         * 
         * @return Returns true if every object of FileSelector is nullptr
        */
        bool isEmpty() { return (_texturePtr == nullptr ? true : false); }      // && _batchPtr == nullptr

    private : // Main variables of FileSelector. It must be hide of touching
        ui::uiWindowRef                     _windowPtr; // General purpose uiWindow of ChocolateSliceFileSelector

        ui::uiWindowRef                     _windowBlurPtr; // Window to hide beckground windows

        ci::app::WindowRef                  _perentWindowPtr; // Parant window. Main programs wnd

    private : // Parts of previewing area and actual objects for drawing 
        ci::gl::Texture2dRef                _texturePtr;

        // Mesh::_meshPtr_t                    _meshPtr;
        ci::gl::BatchRef                    _batch;
        ci::gl::GlslProgRef                 _shaderPtr;

        ci::gl::FboRef                      _FboPtr;

        ci::CameraPersp                     _cameraPersp;

    private : // File extension vinificator
        _File_Extention                      _lastPathExtention; // Extention indemnificator of last loaded object

        char*                               _lastPath;

    private : // Variables for users access
        bool m_opened;

    public: // 
        Json::Value                         _recentFiles;

};



#endif // __CHOCOLATA_SLICER_FILE_SELECTOR_


