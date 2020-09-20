#ifndef __CHOCOLATA_SLICER_OBJECT_PICKER_
#define __CHOCOLATA_SLICER_OBJECT_PICKER_


#include "cinder/gl/gl.h"
#include "cinder/app/App.h"

#include "core.h"

/**
 * ObjectPicker is class to detect selected object in viewport. You should press on object to select it.
 * 
 * TODO: Make highlight for selected object
*/
class ObjectPicker {
    private : // Singleton
        ObjectPicker()  { initObjectPicker(); }

        // Function to init singleton class
        void initObjectPicker();


        // Create FBO with Window size
        void makeFbo();


        void drawToPickerFbo(ci::CameraPersp* cm );

    public :
        static ObjectPicker& getInstance() { static ObjectPicker _picker; return _picker; }


        /**
         * @brief Main public function to calculate selection
         * 
         * @param cm Pointer to global camera
         * 
         * @return Retrns selected object or -1
        */
        int calculateSelection(ci::CameraPersp* cm, ci::app::MouseEvent &event );


        /**
         * @brief Function to resize FBO object of ObjectPicker. It should be called as event when
         * window is resizing
        */
        void resize();


        void destroy() { CHOCOLATA_SLIER_PROFILE_FUNCTION(); _fboPtr.reset(); }


        ci::gl::FboRef                      _fboPtr;

};




#endif // __CHOCOLATA_SLICER_OBJECT_PICKER_

