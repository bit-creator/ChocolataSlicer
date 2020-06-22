#ifndef __UI_WINDOW_
#define __UI_WINDOW_

#include <iostream>
#include "ui.h"


class ui::uiWindow {
    public :
        static uiWindowRef         create(ImVec2 size, ImVec2 pos = ImVec2(60,60), const char* title = "wnd", uiLoaction_ lc = uiLoaction_None, int flags = ImGuiWindowFlags_None) { 
            return uiWindowRef(new uiWindow{size, pos, title, lc, flags} );
        }

        uiWindow(ImVec2 size, ImVec2 pos = ImVec2(60,60), const char* title = "wnd", uiLoaction_ lc = uiLoaction_None, int flags = ImGuiWindowFlags_None ) {
            _size = size;
            _pos = pos;

            _title = title;
            _opened = true;

            _flags = flags;
            _space = nullptr;
            _location = lc;
        }

        void Begin() {
            ImGui::SetNextWindowPos(_pos );
            ImGui::SetNextWindowSize(_size );
            ImGui::Begin(_title, nullptr, _flags );
        }
        void End() {
            _size = ImGui::GetWindowSize();
            ImGui::End();
        }

    private:
        const char*         _title;

        int                 _flags;

        uiWindowHandlerRef  _space;

    public : 
        ImVec2              _pos;
        ImVec2              _size;
        bool                _opened;

        uiLoaction_         _location;
};


#endif // __UI_WINDOW_