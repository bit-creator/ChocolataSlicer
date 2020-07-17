#include "uiBarWindows.h"
#include "uiWindow.h"

#include "cinder/app/App.h"

void ui::showAboutWindow() {
    static ui::uiWindowRef _wnd = ui::uiWindow::create( ImVec2(), ImVec2(), "About", ui::uiLocation_None,
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoCollapse
    );

    static ui::uiWindowRef _wndBlur = ui::uiWindow::create( ImVec2(), ImVec2(), "AboutBlur", ui::uiLocation_None, 
                                        ImGuiWindowFlags_NoDecoration |
                                        ImGuiWindowFlags_NoFocusOnAppearing
    );


    // Variables set
    static const ImVec2 _offset = ImVec2(70, 40);
    static const ImVec2 _size   = ImVec2(360, 515);

    ImVec2 _perendWndSize = ImVec2(ci::app::getWindow()->getSize().x, ci::app::getWindow()->getSize().y );


    // Blur window
    ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.23137,0.20784,0.21961,0.5 } );
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
    _wndBlur->_size = _perendWndSize;
    _wndBlur->Begin();
    _wndBlur->End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();



    _wnd->_size = _size;
    if (_perendWndSize.x < (_size.x + _offset.x) ) {
        _wnd->_size.x = _perendWndSize.x - _offset.x;
    }
    if (_perendWndSize.y < (_size.y + _offset.y) ) {
        _wnd->_size.y = _perendWndSize.y - _offset.y;
    }



    _wnd->_pos = ImVec2(_perendWndSize.x/2 - (_wnd->_size.x/2), _perendWndSize.y/2 - (_wnd->_size.y/2)  );

    _wnd->Begin();
        if (!ImGui::IsWindowFocused() ) {
            ui::UiWindows.about = false;

        }
    _wnd->End();

}