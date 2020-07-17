#ifndef __UI_WINDOW_
#define __UI_WINDOW_

#include <iostream>
#include "ui.h"


class ui::uiWindow {
    public :
        static uiWindowRef create(ImVec2 size, ImVec2 pos = ImVec2(60,60), const char* title = "wnd", uiLocation_ lc = uiLocation_None, int flags = ImGuiWindowFlags_None);

        uiWindow(ImVec2 size, ImVec2 pos = ImVec2(60,60), const char* title = "wnd", uiLocation_ lc = uiLocation_None, int flags = ImGuiWindowFlags_None );

        void Begin();
        void End();

        void addFlag(int flag ) { _flags |= flag; }
        void removeFlag(int flag ) { _flags &= ~flag; }

        void setTite(const char* title);
        const char* getTitle() { return _title; }

    private:
        const char*         _title;
        int                 _flags;

        uiWindowHandlerRef  _space;

    public :
        ImVec2              _pos;
        ImVec2              _size;
        bool                _opened;

        uiLocation_         _location;

};


#endif // __UI_WINDOW_