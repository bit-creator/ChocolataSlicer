#include "uiViewport.h"

ui::uiViewportRef ui::uiViewport::create(ci::app::WindowRef wnd, const char *id ) {
    return uiViewportRef(new uiViewport{wnd, id});
}

ui::uiViewport::uiViewport(ci::app::WindowRef wnd, const char *id ) : _wnd(wnd), _id(id) {
    _flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus;
    _flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar;
}

void ui::uiViewport::Begin() {
    uint32_t pop = 1;
    if (ImGui::GetStyle().WindowRounding > 0)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        pop++;
    }
    if (ImGui::GetStyle().WindowBorderSize > 0)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
        pop++;
    }
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});

    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({_wnd->getSize().x, 0});
    ImGui::Begin(_id, nullptr, _flags);
    ImGui::PopStyleVar(pop);
}

void ui::uiViewport::End() {
    ImGui::End();
}
