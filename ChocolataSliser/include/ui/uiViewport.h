#ifndef __UI_VIEWPORT_
#define __UI_VIEWPORT_

#include "cinder/CinderImGui.h"
#include "cinder/app/Window.h"
#include "ui.h"

class ui::uiViewport {
    public :
        static uiViewportRef create(ci::app::WindowRef wnd, const char* id = "viewport:0" ) { return uiViewportRef(new uiViewport{wnd, id } ); }

        uiViewport(ci::app::WindowRef wnd, const char* id = "viewport:0" ) : _wnd(wnd), _id(id) {
            _flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus;
            _flags |= ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar;
            // _flags |= ImGuiWindowFlags_NoInputs;
        }

        void Begin() {
            uint32_t pop = 1;
            if (ImGui::GetStyle().WindowRounding > 0 ) { ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0 ); pop ++; }
            if (ImGui::GetStyle().WindowBorderSize > 0 ) { ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0 ); pop ++; }
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );

            ImGui::SetNextWindowPos({0,0});
            ImGui::SetNextWindowSize({_wnd->getSize().x,_wnd->getSize().y});
            ImGui::Begin(_id, nullptr, _flags );
            ImGui::PopStyleVar(pop);
        }
        void End() {
            ImGui::End();

        }

    private :
        // Ref to owner window
        ci::app::WindowRef      _wnd;

        // uiViewportRef flags for drawing
        int                     _flags;

        // Viewport name
        const char*             _id;

};


#endif // __UI_VIEWPORT_