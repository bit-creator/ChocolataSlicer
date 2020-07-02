#ifndef __UI_CONTENT_TREE_
#define __UI_CONTENT_TREE_


#include "cinder/gl/gl.h"
// #include "ChocolataSlicerMesh.h"
#include <vector>
#include "ui/ui.h"

// #include "cinder/ObjLoader.h"

/** FIXME: add mesh definitions
 * @brief Is a simplest component of Slicers's objects system which user
 * can manipulate and change. Is used in uiContentTree as simple component
 * 
*/
class ui::uiContentItem {
    public :
        /**
         * @brief Function to create new item
         * 
         * @param name It's name of current model. It will be key for it
         * @param texture Is pointer to texture which should be stored in current model
         * 
         * @return Returns pointer to new created object
        */
        static uiContentItemRef     create(const char* name, ci::gl::Texture2dRef texture = nullptr) {
            return uiContentItemRef(new uiContentItem{name, texture} );
        }

        static uiContentItemRef     create(const char* name, ci::gl::BatchRef mesh = nullptr) {
            return uiContentItemRef(new uiContentItem{name, mesh} );
        }


        /**
         * @brief Siplest constructor for it
         * 
         * @param name It's name of current model. It will be key for it
         * @param texture Is pointer to texture which should be stored in current model
        */
        uiContentItem(const char* name, ci::gl::Texture2dRef texture = nullptr ) : _nameRef(name), _texturePtr(texture), _batchPtr(nullptr) {
        }

        uiContentItem(const char* name, ci::gl::BatchRef mesh = nullptr ) : _nameRef(name), _batchPtr(mesh), _texturePtr(nullptr) {
        }


        /**
         * @brief Function to check if object is empty

         * @return Returns true case every pointer equals nullptr, or falsChocolataSlicere
        */
        bool isEmpty() { return (_texturePtr == nullptr && _batchPtr == nullptr ? true : false); }

        /**
         * @brief Function to cleanup objects which dynamically reserved memory 
        */
        void destroy() { _texturePtr.~__shared_ptr(); _batchPtr.~__shared_ptr(); _texturePtr = nullptr; _batchPtr = nullptr; }

    public : // Lines of class
        const char*                         _nameRef; // Name of current object. It will be as a key for processing

        ci::gl::Texture2dRef                _texturePtr = nullptr; // Texture of this model

        ci::gl::BatchRef                    _batchPtr = nullptr; // Graphic Model

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

    public :
        static uiContentTree& getInstance() { static uiContentTree tree; return tree; }

        /**
         * @brief Default constructor
        */
        uiContentTree() { }


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

        void destroy();

    public :
        std::vector<uiContentItemRef>                   _items; // Main items storage of slicer

        int32_t                                         _selected = -1; // Selected item in list of items. It is index of element in vector

};




#endif // __UI_CONTENT_TREE_
