#include "uiWindowHandler.h"

ui::uiWindowHandlerRef ui::uiWindowHandler::create(ci::app::WindowRef wnd, uiLocation_ location, ImVec2 size, ImVec2 offset ) {
    return uiWindowHandlerRef(new uiWindowHandler{wnd, location, size, offset}); 
}


void ui::uiWindowHandler::show() {
    ImDrawList *dlist = ImGui::GetWindowDrawList();

    if ((_location == uiLocation_Right) || (_location == uiLocation_Down)) {
        dlist->AddRect(_pos, (_end_pos = {_main_wnd->getSize().x, _main_wnd->getSize().y}), ImGui::GetColorU32({0.90196, 0.29804, 0.67451, 1.0}));
    }
    else if (_location == uiLocation_Left) {
        dlist->AddRect(_pos, (_end_pos = {_size.x, _main_wnd->getSize().y}), ImGui::GetColorU32({0.90196, 0.29804, 0.67451, 1.0}));
    }
    else if (_location == uiLocation_Top) {
        dlist->AddRect(_pos, (_end_pos = {_main_wnd->getSize().x, _size.y}), ImGui::GetColorU32({0.90196, 0.29804, 0.67451, 1.0}));
    }

    dlist->AddText(ImVec2(_pos.x + 2, _pos.y + 2), ImGui::GetColorU32({0.90196, 0.29804, 0.67451, 1.0}), "uiWindowHandler");
}


void ui::uiWindowHandler::update(bool vertical )
{
    // Update handlers location
    if (_location == uiLocation_Right)
        _pos = ImVec2(_main_wnd->getSize().x - _size.x + _offset.x, 0 + _offset.y);
    else if ((_location == uiLocation_Left) || (_location == uiLocation_Top))
        _pos = ImVec2(0 + _offset.x, 0 + _offset.y);
    else if (_location == uiLocation_Down)
        _pos = ImVec2(0 + _offset.x, _main_wnd->getSize().y - _size.y + _offset.y);

    // update included windows
    if (_wnds.size() == 1)
    {
        _wnds.at(0)->_pos = _pos;
        _wnds.at(0)->_size = ImVec2(_end_pos.x - _pos.x, _end_pos.y - _pos.y);
    }
    else if (_wnds.size() == 2)
    {
        if (vertical)
        {
            _wnds.at(1)->_pos = _pos;
            _wnds.at(1)->_size.x = _end_pos.x - _pos.x;

            _wnds.at(0)->_pos = ImVec2(_pos.x, _pos.y + _wnds.at(1)->_size.y);
            _wnds.at(0)->_size = ImVec2(_end_pos.x - _pos.x, _end_pos.y - _pos.y - _wnds.at(1)->_size.y);
        }
        // else if (!vertical ) {
        // _wnds.at(1)->_pos = _pos;
        // _wnds.at(1)->_size.x = _end_pos.x - _pos.x;

        // _wnds.at(0)->_pos = ImVec2(_pos.x, _pos.y + _wnds.at(1)->_size.y );
        // _wnds.at(0)->_size = ImVec2(_end_pos.x - _pos.x, _end_pos.y - _pos.y - _wnds.at(1)->_size.y );
        // }
    }



    if ((_location == uiLocation_Right) || (_location == uiLocation_Down)) {
        _end_pos = {_main_wnd->getSize().x, _main_wnd->getSize().y};
    }
    else if (_location == uiLocation_Left) {
        _end_pos = {_size.x, _main_wnd->getSize().y};
    }
    else if (_location == uiLocation_Top) {
        _end_pos = {_main_wnd->getSize().x, _size.y};
    }

}