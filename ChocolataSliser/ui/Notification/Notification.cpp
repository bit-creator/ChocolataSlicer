#include "Notification.h"

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"

#include "definitions.h"

bool Notif::draw() {
    static bool _canClose = false;
    static float _lineThickness = 5;

    ImVec2 _pos = ImGui::GetWindowPos();



    ImGui::SetNextWindowPos(_pos );
    ImGui::SetNextWindowSize(Notifications::GetInstance()._notifSize );
    bool _opened = true;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0,0} );
    ImGui::Begin(_title.c_str(), &_opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
        ImDrawList* _dr = ImGui::GetWindowDrawList();



        _dr->AddText(ImGui::GetFont(), ImGui::GetFontSize() - 1, ImVec2(ImGui::GetCursorScreenPos().x + 10, ImGui::GetCursorScreenPos().y + 2), ImGui::GetColorU32(ImGuiCol_Text, 0.6 ), _description.c_str() );


        ImVec4 _cl = ImGui::GetStyleColorVec4(ImGuiCol_NavHighlight );
        switch (_level ) {
            case (ci::log::LEVEL_INFO) : { _cl = ImVec4(0.525, 0.913, 0.360, 1.0);
                break;
            }
            case (ci::log::LEVEL_WARNING) : { _cl = ImVec4(0.913, 0.659, 0.360, 1.0);
                break;
            }
            // case (ci::log::LEVEL_VERBOSE) : { _cl = Notifications::GetInstance()._verboseCl;
                // break;
            // }
            case (ci::log::LEVEL_ERROR) : { _cl = ImVec4(0.913, 0.360, 0.360, 1.0);
                break;
            }
        }


        _dr->AddLine({ _pos.x + Notifications::GetInstance()._notifSize.x - _lineThickness - 1, _pos.y }, { _pos.x + Notifications::GetInstance()._notifSize.x - _lineThickness - 1, _pos.y + Notifications::GetInstance()._notifSize.y }, ImGui::GetColorU32(_cl), _lineThickness );

        if (!_dateilsLink.empty() ) {
            ImVec2 _textPos = ImVec2(ImGui::GetCursorScreenPos().x + 10, _pos.y + Notifications::GetInstance()._notifSize.y - ImGui::GetFontSize() - 4);
            ImVec2 _textSize = ImGui::CalcTextSize("details", NULL, false);
            _dr->AddText(ImGui::GetFont(), ImGui::GetFontSize() - 2, _textPos, ImGui::GetColorU32(ImVec4(0.259,0.282,0.659,1.0) ), "details" );
            _dr->AddLine({_textPos.x, _textPos.y+_textSize.y-2}, {_textPos.x+_textSize.x-8, _textPos.y+_textSize.y-2}, ImGui::GetColorU32(ImVec4(0.259,0.282,0.659,1.0) ), 1 );

            ImGui::SetCursorScreenPos(_textPos);
            if (ImGui::InvisibleButton(_title.c_str(), _textSize) ) {
                std::thread _sys( 
                    [](std::string _link) { 
                        std::string _cmd = "xdg-open "; _cmd += _link;
                        system(_cmd.c_str() );
                    },
                    _dateilsLink
                );

                _sys.detach();
            }
        }
        

        ImGui::PopStyleVar();
    ImGui::End();


    return !_opened;

}



void Notifications::draw() {
    static ImVec2 _notifOffset = { 0, 15 };

    static ImVec2 _winOffset = { 15, 0 };

    ImVec2 pos = ImVec2(_winOffset.x, ci::app::getWindowSize().y - ((_notifSize.y + _notifOffset.y) * (_notifications.size() > _maxNotifs ? _maxNotifs : _notifications.size() )) - _winOffset.y );

    for (int i = (_notifications.size() - 1); i >=0  ; i-- ) {
        ImGui::SetWindowPos(pos );
        bool _closed = _notifications.at(i).draw();

        if ( _closed ) {
            _notifications.erase(_notifications.begin() + i);
        }

        pos = ImVec2(_winOffset.x, pos.y + _notifSize.y + _notifOffset.y );
    }


}