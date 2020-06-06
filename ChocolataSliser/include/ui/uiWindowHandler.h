#ifndef __UI_WINDOW_HANDLER_
#define __UI_WINDOW_HANDLER_

#include "cinder/app/Window.h"
#include "ui.h"

class ui::uiWindowHandler {
    public : 
        static uiWindowHandlerRef   create(ci::app::WindowRef wnd, uiLoaction_ location, ImVec2 size = {250,250}, ImVec2 offset = {0,0} ) { return uiWindowHandlerRef(new uiWindowHandler{wnd, location, size, offset} ); }

        uiWindowHandler(ci::app::WindowRef wnd, uiLoaction_ location, ImVec2 size = {250,250}, ImVec2 offset = {0,0} ) : _size(size), _location(location), _main_wnd(wnd), _offset(offset) {
        }

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
        uiLoaction_                 _location;
};


void ui::uiWindowHandler::show( ) {
    ImDrawList* dlist = ImGui::GetWindowDrawList();

    if ((_location == uiLoaction_Right) || (_location == uiLoaction_Down)) {
        dlist->AddRect(_pos, (_end_pos = {_main_wnd->getSize().x, _main_wnd->getSize().y}), ImGui::GetColorU32({0.90196,0.29804,0.67451,1.0}) );
    }
    else if (_location == uiLoaction_Left) {
        dlist->AddRect(_pos, (_end_pos = {_size.x, _main_wnd->getSize().y}), ImGui::GetColorU32({0.90196,0.29804,0.67451,1.0}) );
    }
    else if (_location == uiLoaction_Top) {
        dlist->AddRect(_pos, (_end_pos = {_main_wnd->getSize().x, _size.y }), ImGui::GetColorU32({0.90196,0.29804,0.67451,1.0}) );
    }

    dlist->AddText(ImVec2(_pos.x+2,_pos.y+2), ImGui::GetColorU32({0.90196,0.29804,0.67451,1.0}), "uiWindowHandler" );

}


void ui::uiWindowHandler::update(bool vertical ) {
    // Update handlers location
    if (_location == uiLoaction_Right) _pos = ImVec2(_main_wnd->getSize().x - _size.x + _offset.x, 0 + _offset.y );
    else if ((_location == uiLoaction_Left) || (_location == uiLoaction_Top)) _pos = ImVec2(0 + _offset.x, 0 + _offset.y );
    else if (_location == uiLoaction_Down) _pos = ImVec2(0 + _offset.x, _main_wnd->getSize().y - _size.y + _offset.y );


    // update included windows
    if (_wnds.size() == 1 ) {
        _wnds.at(0)->_pos = _pos;
        _wnds.at(0)->_size = ImVec2(_end_pos.x-_pos.x, _end_pos.y-_pos.y);
    }
    else if (_wnds.size() == 2) {
        if (vertical ) {
            _wnds.at(1)->_pos = _pos;
            _wnds.at(1)->_size.x = _end_pos.x - _pos.x;


            _wnds.at(0)->_pos = ImVec2(_pos.x, _pos.y + _wnds.at(1)->_size.y );
            _wnds.at(0)->_size = ImVec2(_end_pos.x - _pos.x, _end_pos.y - _pos.y - _wnds.at(1)->_size.y );  
        }
        // else if (!vertical ) {
            // _wnds.at(1)->_pos = _pos;
            // _wnds.at(1)->_size.x = _end_pos.x - _pos.x;


            // _wnds.at(0)->_pos = ImVec2(_pos.x, _pos.y + _wnds.at(1)->_size.y );
            // _wnds.at(0)->_size = ImVec2(_end_pos.x - _pos.x, _end_pos.y - _pos.y - _wnds.at(1)->_size.y );  
        // }
    }

}


#endif // __UI_WINDOW_HANDLER_