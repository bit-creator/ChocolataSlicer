#include "ContentTree.h"

#include "ui/uiComponents.h"
#include "ShaderTree.h"

#include "cinder/app/App.h"
#include "core.h"

void ContentTree::__tooltip(const char* tx) {
    if (ImGui::IsItemHovered() ) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(tx);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


void ContentTree::destroy() {
    CHOCOLATA_SLIER_PROFILE_FUNCTION();

    {
        CHOCOLATA_SLIER_PROFILE_SCOPE("_FboPtr.reset()");
        _FboPtr.reset();
    }

    {
        CHOCOLATA_SLIER_PROFILE_SCOPE("_items.at(i)->destroy()");
        for (int i = 0; i < getInstance()._items.size(); i++ ) {
            _items.at(i)->destroy();
        }
    }
}

void ContentTree::update() {
    CHOCOLATA_SLIER_PROFILE_FUNCTION();

    std::vector<ContentItemRef> new_items;

    if (_items.size() <= 0) return;

    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->isEmpty() ) new_items.push_back(_items.at(i));

    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_batchPtr != nullptr ) new_items.push_back(_items.at(i));

    _items = new_items;
}


void ContentTree::drawObjectsToUiList() {
    CHOCOLATA_SLIER_PROFILE_FUNCTION();

    update();       // update items location

    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

    {
        CHOCOLATA_SLIER_PROFILE_SCOPE("drawItems");
        for (int i = (_items.size() - 1); i >= 0; i-- ) {
            ImGuiTreeNodeFlags node_flags = base_flags;
            if (i == _selected ) node_flags |= ImGuiTreeNodeFlags_Selected;
            if (_items.at(i)->_texturePtr == nullptr && _items.at(i)->_batchPtr == nullptr ) node_flags |= ImGuiTreeNodeFlags_Leaf;
    
            float _x = ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth() - 50;
            bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", _items.at(i)->_nameRef.c_str(), (i+1) );
            if (ImGui::IsItemClicked()) _selected = i;

    
            if (node_open) {
                bool _drBatch = (_items.at(i)->_batchPtr != nullptr);
                bool _drTextr = (_items.at(i)->_texturePtr != nullptr);

                if (_drBatch ) {
                    ImVec2 nodePos = ImGui::GetCursorScreenPos();
                    ui::customBullet("", ImVec2(17,17), glm::vec3(0.23137,0.23137,0.21961), true);
                    ImGui::SameLine();
                    ImGui::Text("%p", _items.at(i)->_batchPtr ); __tooltip("Mesh object");
    
                    if (ui::__ui_invisible_button(ImVec2(nodePos.x + ImGui::GetWindowSize().x - 50, nodePos.y), " ", true ) ) {
                        _items.at(i)->_batchPtr.reset();
    
                        if (_items.at(i)->isEmpty() ) {
                            if (_items.size() > 0 )
                                _items.erase(_items.end() - i - 1 );
                            else 
                                _items.clear();
                        }
    
                    } __tooltip("Remove item");
    
                }
    
                if (_drTextr ) {
                ImVec2 nodePos = ImGui::GetCursorScreenPos();
                ui::customBullet("", ImVec2(17,17), glm::vec3(0.23137,0.23137,0.21961), true);
                ImGui::SameLine();
                ImGui::Text("%p", _items.at(i)->_texturePtr ); __tooltip("Texture object");

                if (ImGui::IsItemHovered() ) {
                    ImGui::BeginTooltip();

                    // FIXME: Proportional scaling of image
                    ImGui::Image(_items.at(i)->_texturePtr, _items.at(i)->_texturePtr->getSize()/2, {0,1}, {1,0} );
                    ImGui::EndTooltip();
                }

                if (ui::__ui_invisible_button(ImVec2(nodePos.x + ImGui::GetWindowSize().x - 50, nodePos.y), "  ", true ) ) {
                    _items.at(i)->_texturePtr.reset();

                    if (_items.at(i)->isEmpty() ) {
                        if (_items.size() > 0 )
                            _items.erase(_items.end() - i - 1 );
                        else 
                            _items.clear();
                    }

                } __tooltip("Remove item");

            }
    
                ImGui::TreePop();
            }
        }
    }
}



void ContentTree::drawObjectsToScene(ci::CameraPersp* _camera ) {
    CHOCOLATA_SLIER_PROFILE_FUNCTION();
    for (int i = 0; i < _items.size(); i++ ) {
        if (!_items.at(i)->_batchPtr ) continue;

        ci::gl::GlslProgRef sl = _items.at(i)->_batchPtr->getGlslProg();

        ci::gl::setModelMatrix(glm::mat4(1.0) );
        ci::gl::color(0.7,0.7,0.7);
        ci::gl::translate(_items.at(i)->_position );
        ci::gl::rotate(_items.at(i)->_rotate );
        ci::gl::scale(_items.at(i)->_scale );

        if (i == _selected ) {
            ci::gl::color(0.988235294118, 0.729411764706, 0.164705882353);
            _items.at(i)->_batchPtr->replaceGlslProg(ShaderTree::getInstance().colorShader());
        }

        _items.at(i)->_batchPtr->getGlslProg()->uniform("ciEyePos", _camera->getEyePoint() );
        _items.at(i)->_batchPtr->getGlslProg()->uniform("ciCameraUp", glm::cross(glm::normalize(_camera->getViewDirection() ), glm::vec3(1,0,0)) );
        _items.at(i)->_batchPtr->draw();

        if (i == _selected )
            ContentTree::getInstance()._items.at(i)->_batchPtr->replaceGlslProg(sl);
    }

}


void ContentTree::swapShaders(ci::gl::GlslProgRef _shader ) {
    for (auto it : _items ) {
        if (it->_batchPtr == nullptr ) continue;

        it->_batchPtr->replaceGlslProg(_shader );
    }
}