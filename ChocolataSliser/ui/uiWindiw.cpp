#include "uiWindow.h"

ui::uiWindowRef ui::uiWindow::create(ImVec2 size, ImVec2 pos, const char *title, uiLocation_ lc, int flags )
{
    return uiWindowRef(new uiWindow{size, pos, title, lc, flags});
}

ui::uiWindow::uiWindow(ImVec2 size, ImVec2 pos, const char *title, ui::uiLocation_ lc, int flags )
{
    _size = size;
    _pos = pos;

    // _title = title;
    setTite(title );
    _opened = true;

    _flags = flags;
    _space = nullptr;
    _location = lc;
}

void ui::uiWindow::setTite(const char* title) {
    if (_title == nullptr ) {
        free((void*)_title );
    }
    _title = title;
}

void ui::uiWindow::Begin()
{
    ImGui::SetNextWindowPos(_pos);
    ImGui::SetNextWindowSize(_size);
    ImGui::Begin(_title, nullptr, _flags);
}

void ui::uiWindow::End()
{
    _size = ImGui::GetWindowSize();
    ImGui::End();
}
