#include "ContentTree.h"

#include "ui/uiComponents.h"



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

        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", _items.at(i)->_nameRef, (i+1) );
        if (ImGui::IsItemClicked()) _selected = i;

        // Draw elements content
        if (node_open) {
            if (_items.at(i)->_batchPtr != nullptr) {
                ui::customBullet("", ImVec2(17,17), glm::vec3(0.23137,0.23137,0.21961), true);
                ImGui::SameLine();
                ImGui::Text("%p", _items.at(i)->_batchPtr ); __tooltip("Mesh object");

                // TODO: Object highlight
            }

            if (_items.at(i)->_texturePtr != nullptr) {
                ui::customBullet("", ImVec2(17,17), glm::vec3(0.23137,0.23137,0.21961), true);
                ImGui::SameLine();
                ImGui::Text("%p", _items.at(i)->_texturePtr ); __tooltip("Texture object");

                if (ImGui::IsItemHovered() ) {
                    ImGui::BeginTooltip();

                    // FIXME: Proportional scaling of image
                    ImGui::Image(_items.at(i)->_texturePtr, _items.at(i)->_texturePtr->getSize()/2, {0,1}, {1,0} );
                    ImGui::EndTooltip();
                }
            }

            ImGui::TreePop();
            if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_batchPtr != nullptr ) { ImGui::Spacing(); ImGui::Spacing(); }
        }
    }
}



void ContentTree::drawObjectsToScene(ci::CameraPersp* _camera ) {
    for (auto _itemIt : _items ) {
        if (_itemIt->_batchPtr == nullptr ) continue;

        ci::gl::color(0.7,0.7,0.7);
        ci::gl::translate(_itemIt->_position );
        ci::gl::rotate(_itemIt->_rotate );
        ci::gl::scale(_itemIt->_scale );

        _itemIt->_batchPtr->getGlslProg()->uniform("ciEyePos", _camera->getEyePoint() );
        _itemIt->_batchPtr->getGlslProg()->uniform("ciCameraUp", glm::cross(glm::normalize(_camera->getViewDirection() ), glm::vec3(1,0,0)) );
        _itemIt->_batchPtr->draw();
    }

}
