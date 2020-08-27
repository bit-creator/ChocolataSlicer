#include "Notification.h"

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"


bool Notif::draw() {
    static ImVec2 _notifSize = { 273, 68 };
    static bool _canClose = false;
    static float _lineThickness = 4;

    ImVec2 _pos = ImGui::GetWindowPos();



    ImGui::SetNextWindowPos(_pos );
    ImGui::SetNextWindowSize(_notifSize );
    bool _opened = true;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
    ImGui::Begin(_title.c_str(), &_opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
        ImDrawList* _dr = ImGui::GetWindowDrawList();



        _dr->AddText(ImGui::GetFont(), ImGui::GetFontSize() - 1, ImVec2(ImGui::GetCursorScreenPos().x + 10, ImGui::GetCursorScreenPos().y + 2), ImGui::GetColorU32(ImGuiCol_Text, 0.6 ), _description.c_str() );


        ImVec4 _cl = ImGui::GetStyleColorVec4(ImGuiCol_NavHighlight );
        switch (_level ) {
            case (ci::log::LEVEL_INFO) : { _cl = ImVec4(0.45882,0.71373,0.36471,0.8);
                break;
            }
            case (ci::log::LEVEL_WARNING) : { _cl = ImVec4();
                break;
            }
            case (ci::log::LEVEL_VERBOSE) : { _cl = ImVec4();
                break;
            }
            case (ci::log::LEVEL_ERROR) : { _cl = ImVec4();
                break;
            }
            case (ci::log::LEVEL_FATAL) : { _cl = ImVec4();
                break;
            }
            case (ci::log::LEVEL_DEBUG) : { _cl = ImVec4();
                break;
            }
        }


        _dr->AddLine({ _pos.x + _notifSize.x - _lineThickness - 1, _pos.y }, { _pos.x + _notifSize.x - _lineThickness - 1, _pos.y + _notifSize.y }, ImGui::GetColorU32(_cl), _lineThickness );

        // _dr->AddText(ImGui::GetFont(), ImGui::GetFontSize() - 1, ImVec2(ImGui::GetCursorScreenPos().x + 10, ImGui::GetCursorScreenPos().y), ImGui::GetColorU32(ImGuiCol_Text, 0.6 ), _description.c_str() );

        ImGui::PopStyleVar();
    ImGui::End();


    return !_opened;

}



void Notifications::draw() {
    static ImVec2 _notifSize = { 273, 68 };
    static ImVec2 _notifOffset = { 0, 15 };
    static uint _maxNotifs = 3;

    static ImVec2 _winOffset = { 15, 0 };

    ImVec2 pos = ImVec2(_winOffset.x, ci::app::getWindowSize().y - ((_notifSize.y + _notifOffset.y) * (_notifications.size() > _maxNotifs ? _maxNotifs : _notifications.size() )) - _winOffset.y );

    int i = 0;
    for (auto it : _notifications ) {
        ImGui::SetNextWindowPos(pos );
        bool _closed = it.draw();
        
        if ( _closed ) {
            _notifications.emplace(_notifications.begin() + i);
        }

        pos = ImVec2(_winOffset.x, pos.y + _notifSize.y + _notifOffset.y );
        i++;
    }


}