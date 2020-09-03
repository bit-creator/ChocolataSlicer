#ifndef __UI_VIEWPORT_
#define __UI_VIEWPORT_

#include "cinder/CinderImGui.h"
#include "cinder/app/Window.h"
#include "ui.h"

class ui::uiViewport {
    public :
        static uiViewportRef create(ci::app::WindowRef wnd, const char* id = "viewport:0" );

        ci::app::WindowRef getWindow() { return _wnd; }

        uiViewport(ci::app::WindowRef wnd, const char* id = "viewport:0" );

        void Begin();
        void End();

    private :
        const char*             _id;
        int                     _flags;         // Static variable for any viewports

        ci::app::WindowRef      _wnd;

};


#endif // __UI_VIEWPORT_