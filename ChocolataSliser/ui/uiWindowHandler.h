#ifndef __UI_WINDOW_HANDLER_
#define __UI_WINDOW_HANDLER_

#include "cinder/app/Window.h"
#include "uiWindow.h"
#include "ui.h"

class ui::uiWindowHandler {
    public : 
        static uiWindowHandlerRef   create(ci::app::WindowRef wnd, uiLocation_ location, ImVec2 size = {250,250}, ImVec2 offset = {0,0} );

        uiWindowHandler(ci::app::WindowRef wnd, uiLocation_ location, ImVec2 size = {250,250}, ImVec2 offset = {0,0} ) : _size(size), _location(location), _main_wnd(wnd), _offset(offset) {};

        // Show rectengular scope for this handler
        void show();

        // Modifies conteiner stufs
        void update(bool vertical = true);

        // Adding window to conteiner for processing
        void pushWnd(uiWindowRef wnd ) { _wnds.push_back(wnd); }


    private :
        std::vector<uiWindowRef>    _wnds;
        ci::app::WindowRef          _main_wnd;
    
    public :
        // Size of other side. One side will be equal windows side size
        ImVec2                      _size;

        // Rectengular scope of handler seting by two points (pos, end_pos).
        ImVec2                      _pos;
        ImVec2                      _end_pos;

        // ofset from sides of window. Beginning is (0, 0) point in top left corner of a window  
        ImVec2                      _offset;

        // Location in only viewport spacec
        uiLocation_                 _location;
};



#endif // __UI_WINDOW_HANDLER_