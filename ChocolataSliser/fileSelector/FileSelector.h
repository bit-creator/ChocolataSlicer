#ifndef __CHOCOLATA_SLICER_FILE_SELECTOR_
#define __CHOCOLATA_SLICER_FILE_SELECTOR_


#include <stdio.h>
#include "cinder/Log.h"
#include "cinder/app/Window.h"

#include "cstringFunctions.h"
#include "fileConfig.h"

#include "ui/uiWindow.h"
#include "ui/uiContentTree.h"
// #include "ChocolataSlicerMesh.h"

// #include "cinder/gl/Fbo.h"
// #include "cinder/ImageIo.h"

/**
 * @brief Singleton class with window for viewing and loading objects to programs objects buffer.
 * You can call it by one line "FileSelector::getInstance.open()"
*/
class FileSelector {
    private : // Singleton definitions
        /**
         * @brief Default constructor of singleton FileSelector class
        */
        FileSelector()  : m_opened(false) {  initFileSelector(); }


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
         * @brief Opens system FileSelector to loading files by extentions
         * 
         * @param title Title of file selector which loads your file
         * @param extentions Extentions of files which can be loaded. Write it by line ex: "*.png | *.jpg"
         * 
         * @return Returns path of file to be load with one of seated extensions
        */
        // char* openLoadingFileSelector(const char* title, const char* extentions );


        /**
         * @brief Function for opening FileSelector and systems FileSelector. You selecting
         * a file and choosing which object will refers on it
         * 
         * @return Returns 1 if loaded something, or 0
        */
        bool open();


        /**
         * @brief Function for previewing FileSelector's window. It contains object tree and
         * previewing area
        */
        void draw();


        bool isOpen() { return m_opened; }

        bool isEmpty() { return (_texturePtr == nullptr ? true : false); }      // && _batchPtr == nullptr

        void destroy() {
            // if (!m_opened ) return;

            _texturePtr.~__shared_ptr();
            _shaderPtr.~__shared_ptr();
            _FboPtr.~__shared_ptr();

            _texturePtr = nullptr;
            _shaderPtr = nullptr;
            _FboPtr = nullptr;
        }

    private : // Main variables of FileSelector. It must be hide of touching
        ui::uiWindowRef                     _windowPtr; // General purpose uiWindow of ChocolateSliceFileSelector

        ci::app::WindowRef                  _perentWindowPtr; // Parant window. Main programs wnd

    private : // Parts of previewing area and actual objects for drawing 
        ci::gl::Texture2dRef                _texturePtr;

        // Mesh::_meshPtr_t                    _meshPtr;

        ci::gl::GlslProgRef                 _shaderPtr;

        ci::gl::FboRef                      _FboPtr;

        ci::CameraPersp                     _cameraPersp;

    private : // File extension vinificator
        _FileExtention                      _lastPathExtention; // Extention indemnificator of last loaded object

    private : // Variables for users access
        bool m_opened;

};



#endif // __CHOCOLATA_SLICER_FILE_SELECTOR_


