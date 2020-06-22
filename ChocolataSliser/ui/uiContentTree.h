#ifndef __UI_CONTENT_TREE_
#define __UI_CONTENT_TREE_


#include "cinder/gl/gl.h"
#include "ui/uiComponents.h"
#include "ChocolataSlicerMesh.h"
#include <vector>
#include "ui/ui.h"

#include "cinder/ObjLoader.h"

/** FIXME: add mesh definitions
 * @brief Is a simplest component of Slicers's objects system which user
 * can manipulate and change. Is used in uiContentTree as simple component
 * 
*/
class ui::uiContentItem {
    public :
        /** FIXME: add mesh to create function
         * @brief Function to create new items
         * 
         * @param name It's name of current model. It will be key for it
         * @param texture Is pointer to texture which should be stored in current model
         * 
         * @return Returnt pointer to new created object
         * 
        */
        static uiContentItemRef     create(const char* name, ci::gl::Texture2dRef texture = nullptr) {
            return uiContentItemRef(new uiContentItem{name, texture} );
        }


        /**
         * @brief Siplest constructor for it
         * 
         * @param name It's name of current model. It will be key for it
         * @param texture Is pointer to texture which should be stored in current model
         * 
        */
        uiContentItem(const char* name, ci::gl::Texture2dRef texture = nullptr ) : _nameRef(name), _texturePtr(texture) {
        }

    public : // Lines of class
        const char*                         _nameRef; // Name of current object. It will be as a key for processing

        ci::gl::Texture2dRef                _texturePtr; // Texture of this model

        ci::gl::BatchRef                    _bathMesh; // Graphic Model
};


/**
 * @brief Main storage of objects for ChocolataSlicer. It contains uiContentItems and info for
 * visualizing items 
*/
class ui::uiContentTree {
    private : // Singleton definitions
        /**
         * @brief Updates item location in vector of items. It is needed for correct visualizing to
         * users screen
        */
        void update();

        /**
         * @brief Default constructor
        */
        uiContentTree() { }

    public :
        static uiContentTree& getInstance() { static uiContentTree tree; return tree; }


        /**
         * @brief Adds new item to vector of items.
         * 
         * @param item Pointer to item which should be pushed to vector
        */
        void pushItem(uiContentItemRef item) { _items.push_back(item ); }


        /**
         * @brief Shows tooltip with any text to users screen.
         * 
         * @param tx Is a text for visualizing
        */
        static void __tooltip(const char* tx);


        /**
         * @brief Draws vector of items. User can do anything with them
        */
        void draw();

    public :
        std::vector<uiContentItemRef>                   _items; // Main items storage of slicer

        int32_t                                         _selected = -1; // Selected item in list of items. It is index of element in vector

};




void ui::uiContentTree::__tooltip(const char* tx) {
    if (ImGui::IsItemHovered() ) {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(tx);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}


void ui::uiContentTree::update() {
    std::vector<uiContentItemRef> new_items;
    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->_texturePtr == nullptr && _items.at(i)->_bathMesh == nullptr ) new_items.push_back(_items.at(i));

    for (int i = 0; i < _items.size(); i++ )
        if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_bathMesh != nullptr ) new_items.push_back(_items.at(i));

    _items = new_items;
}


void ui::uiContentTree::draw() {
    update();       // update items location

    static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

    for (int i = (_items.size() -1); i >= 0; i-- ) {
        ImGuiTreeNodeFlags node_flags = base_flags;
        if (i == _selected ) node_flags |= ImGuiTreeNodeFlags_Selected;
        if (_items.at(i)->_texturePtr == nullptr && _items.at(i)->_bathMesh == nullptr ) node_flags |= ImGuiTreeNodeFlags_Leaf;

        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", _items.at(i)->_nameRef, (i+1) );
        if (ImGui::IsItemClicked()) _selected = i;

        // Draw elements content
        if (node_open) {
            if (_items.at(i)->_texturePtr != nullptr) {
                ImGui::BulletText("%p", _items.at(i)->_texturePtr ); __tooltip("Texture object");
            }

            if (_items.at(i)->_bathMesh != nullptr) {
                ImGui::BulletText("%p", _items.at(i)->_bathMesh ); __tooltip("Mesh object");
            }

            ImGui::TreePop();
            if (_items.at(i)->_texturePtr != nullptr || _items.at(i)->_bathMesh != nullptr ) { ImGui::Spacing(); ImGui::Spacing(); }
        }
    }
}



#endif // __UI_CONTENT_TREE_
