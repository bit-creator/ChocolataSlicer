#include "uiContentTree.h"
#include "ui/uiComponents.h"



void ui::uiContentTree::__tooltip(const char* tx) {
    if (ImGui::IsItemHovered() ) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(tx);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


void ui::uiContentTree::destroy() {
    for (int i = 0; i < getInstance()._items.size(); i++ ) {
        _items.at(i)->destroy();
    }
}

void ui::uiContentTree::update() {
    std::vector<uiContentItemRef> new_items;
    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->isEmpty() ) new_items.push_back(_items.at(i));

    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_batchPtr != nullptr ) new_items.push_back(_items.at(i));

    _items = new_items;
}


void ui::uiContentTree::draw() {
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
            }

            if (_items.at(i)->_texturePtr != nullptr) {
                ui::customBullet("", ImVec2(17,17), glm::vec3(0.23137,0.23137,0.21961), true);
                ImGui::SameLine();
                ImGui::Text("%p", _items.at(i)->_texturePtr ); __tooltip("Texture object");
            }

            ImGui::TreePop();
            if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_batchPtr != nullptr ) { ImGui::Spacing(); ImGui::Spacing(); }
        }
    }
}
