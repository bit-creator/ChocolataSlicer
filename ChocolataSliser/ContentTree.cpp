#include "ContentTree.h"

#include "ui/uiComponents.h"
#include "ShaderTree.h"

#include "cinder/app/App.h"

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
    _FboPtr.reset();

    for (int i = 0; i < getInstance()._items.size(); i++ ) {
        _items.at(i)->destroy();
    }
}

void ContentTree::update() {
    std::vector<ContentItemRef> new_items;
    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->isEmpty() ) new_items.push_back(_items.at(i));

    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_batchPtr != nullptr ) new_items.push_back(_items.at(i));

    _items = new_items;
}


void ContentTree::drawObjectsToUiList() {
    update();       // update items location

    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

    for (int i = (_items.size() -1); i >= 0; i-- ) {
        ImGuiTreeNodeFlags node_flags = base_flags;
        if (i == _selected ) node_flags |= ImGuiTreeNodeFlags_Selected;
        if (_items.at(i)->_texturePtr == nullptr && _items.at(i)->_batchPtr == nullptr ) node_flags |= ImGuiTreeNodeFlags_Leaf;

        float _x = ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth() - 50;
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", _items.at(i)->_nameRef, (i+1) );
        if (ImGui::IsItemClicked()) _selected = i;


        if (node_open) {
            if (_items.at(i)->_batchPtr != nullptr) {
                ImVec2 nodePos = ImGui::GetCursorScreenPos();
                ui::customBullet("", ImVec2(17,17), glm::vec3(0.23137,0.23137,0.21961), true);
                ImGui::SameLine();
                ImGui::Text("%p", _items.at(i)->_batchPtr ); __tooltip("Mesh object");

                if (ui::__ui_invisible_button(ImVec2(nodePos.x + ImGui::GetWindowSize().x - 50, nodePos.y), " ", true ) ) {
                    _items.at(i)->_batchPtr.reset();

                    if (_items.at(i)->isEmpty() ) { _items.erase(_items.end() - i );
                        goto endContentTree;
                    }

                } __tooltip("Remove item");

            }

            if (_items.at(i)->_texturePtr != nullptr) {
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

                    if (_items.at(i)->isEmpty() ) { _items.erase(_items.end() - i );
                        goto endContentTree;
                    }

                } __tooltip("Remove item");

            }

            ImGui::TreePop();
            if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_batchPtr != nullptr ) { ImGui::Spacing(); ImGui::Spacing(); }

            endContentTree: continue;
        }
    }
}



void ContentTree::drawObjectsToScene(ci::CameraPersp* _camera ) {
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