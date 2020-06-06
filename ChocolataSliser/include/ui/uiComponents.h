#ifndef __UI_COMPONENTS_
#define __UI_COMPONENTS_

#include "cinder/CinderImGui.h"

namespace ui {



bool __ui_invisible_button(ImVec2 pos, const char* text, ImVec2 plus_size = {0,0}) {
    ImVec2 size = ImGui::CalcTextSize(text, NULL, true);
    ImGui::SetCursorScreenPos(pos );
    ImGui::InvisibleButton(text, size);
}



};


#endif // __UI_COMPONENTS_

