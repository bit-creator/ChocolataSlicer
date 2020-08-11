#ifndef __UI_COMPONENTS_
#define __UI_COMPONENTS_

#include "cinder/CinderImGui.h"

namespace ui {



bool __ui_invisible_button(ImVec2 pos, const char* text, bool drawText = false ) {
    ImVec2 size = ImGui::CalcTextSize(text, NULL, true);
    ImDrawList* dw = ImGui::GetWindowDrawList();
    float fontSize = 8;

    ImGui::SetCursorScreenPos(pos );
    ImGui::InvisibleButton(text, size);

    if (ImGui::IsItemHovered() ) fontSize = 10;

    if (drawText ) {
        dw->AddText(ImGui::GetFont(), fontSize, pos, ImGui::GetColorU32(ImVec4(0,0,0,1)), text );
    }

    if (ImGui::IsItemDeactivated() ) return true;
    return false;
}


bool customButton(const char* label, ImVec2 size, glm::vec3 textColor = {1,1,1}, bool centring = false ) {
    ImDrawList* list = ImGui::GetWindowDrawList();    
    ImVec2 minPos = ImGui::GetCursorScreenPos();
    bool pressed = false;

    if (ImGui::InvisibleButton(label, size )) pressed = true;

    if (ImGui::IsItemHovered() ) {
        list->AddRectFilled(minPos, ImVec2(minPos.x+size.x, minPos.y+size.y), ImGui::GetColorU32(ImGuiCol_ButtonHovered), 3 );

        if (!centring ) {
            list->AddText({minPos.x+3, minPos.y+3}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,1)), label );
        } 
        else {
            ImVec2 txtSize = ImGui::CalcTextSize(label, nullptr, true );
            list->AddText({minPos.x + ((size.x-txtSize.x)/2), minPos.y + ((size.y-txtSize.y)/2)}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,1)), label );
        }

    } 
    else {
        list->AddRectFilled(minPos, ImVec2(minPos.x+size.x, minPos.y+size.y), ImGui::GetColorU32(ImGuiCol_ButtonHovered, 0.05), 3 );
        if (!centring ) {
            list->AddText({minPos.x+3, minPos.y+3}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,0.75)), label );
        }
        else {
            ImVec2 txtSize = ImGui::CalcTextSize(label, nullptr, true );
            list->AddText({minPos.x + ((size.x-txtSize.x)/2), minPos.y + ((size.y-txtSize.y)/2)}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,0.75)), label );
        }
    }

    return pressed;
}


void customBullet(const char* label, ImVec2 size, glm::vec3 textColor = {1,1,1}, bool centring = false ) {
    ImDrawList* list = ImGui::GetWindowDrawList();    
    ImVec2 minPos = ImGui::GetCursorScreenPos();

    ImGui::InvisibleButton(label, size );

    if (!centring ) {
        list->AddText({minPos.x+3, minPos.y+3}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,0.75)), label );
    }
    else {
        ImVec2 txtSize = ImGui::CalcTextSize(label, nullptr, true );
        list->AddText({minPos.x + ((size.x-txtSize.x)/2), minPos.y + ((size.y-txtSize.y)/2)}, ImGui::GetColorU32(ImVec4(textColor.x,textColor.y,textColor.z,0.75)), label );
    }
}

};


#endif // __UI_COMPONENTS_

