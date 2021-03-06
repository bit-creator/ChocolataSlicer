#ifndef __CHOCOLATA_SLICER_CONTENT_TREE_
#define __CHOCOLATA_SLICER_CONTENT_TREE_

#include <memory>

#include "cinder/gl/gl.h"

#include "docLoader/ChocolataSlicerMesh.h"

class ContentItem;
typedef std::shared_ptr<class ContentItem>      ContentItemRef;

class ContentTree;
typedef std::shared_ptr<class uiContentTree>    ContentTreeRef;




class ContentItem {
    public :
        /**
         * @brief Function to create new item
         *
         * @param name It's name of current model. It will be key for it
         * @param texture Is pointer to texture which should be stored in current model
         *
         * @return Returns pointer to new created object
        */
        static ContentItemRef create(std::string name, ci::gl::Texture2dRef texture = nullptr) {
            return ContentItemRef(new ContentItem{name, texture} );
        }

        static ContentItemRef create(std::string name, ci::gl::BatchRef mesh = nullptr) {
            return ContentItemRef(new ContentItem{name, mesh} );
        }


        /**
         * @brief Siplest constructor for it
         *
         * @param name It's name of current model. It will be key for it
         * @param texture Is pointer to texture which should be stored in current model
        */
        ContentItem(std::string name, ci::gl::Texture2dRef texture = nullptr ) : _nameRef(name), _texturePtr(texture), _batchPtr(nullptr) {
        }

        ContentItem(std::string name, ci::gl::BatchRef mesh = nullptr ) : _nameRef(name), _batchPtr(mesh), _texturePtr(nullptr) {
        }


        /**
         * @brief Function to check if object is empty

         * @return Returns true case every pointer equals nullptr, or false
        */
        bool isEmpty() { return (_texturePtr == nullptr && _batchPtr == nullptr ? true : false); }

        /**
         * @brief Function to cleanup objects which dynamically reserved memory
        */
        void destroy() { _texturePtr.~__shared_ptr(); _batchPtr.~__shared_ptr(); _texturePtr = nullptr; _batchPtr = nullptr; }

    public : // Lines of class
        std::string                         _nameRef; // Name of current object. It will be as a key for processing

        ci::gl::Texture2dRef                _texturePtr = nullptr; // Texture of this model

        Mesh::_meshPtr_t                    _meshPtr = nullptr; // ...

        ci::gl::BatchRef                    _batchPtr = nullptr; // Graphic Model


    public : // Transforms
        glm::vec3               _position = glm::vec3(0, 0, 0);
        glm::vec3               _scale = glm::vec3(1, 1, 1);
        glm::vec3               _rotate = glm::vec3(0, 0, 0);

};


/**
 * @brief Main storage of objects for ChocolataSlicer. It contains uiContentItems and info for
 * visualizing items
*/
class ContentTree {
    private : // Singleton definitions
        /**
         * @brief Updates item location in vector of items. It is needed for correct visualizing to
         * users screen
        */
        void update();

        /**
         * @brief Default constructor
        */
        ContentTree() {
            ci::gl::Fbo::Format fboFormat;
            fboFormat.samples(8 );
            glm::ivec2 fboResolution = glm::ivec2(1280, 960);
	        _FboPtr = ci::gl::Fbo::create(fboResolution.x, fboResolution.y, fboFormat );    
        }

    public :
        static ContentTree& getInstance() { static ContentTree tree; return tree; }


        /**
         * @brief Adds new item to vector of items.
         *
         * @param item Pointer to item which should be pushed to vector
        */
        ContentItemRef pushItem(ContentItemRef item) { _items.push_back(item ); return _items.at(_items.size()-1); }


        /**
         * @brief Shows tooltip with any text to users screen.
         *
         * @param tx Is a text for visualizing
        */
        static void __tooltip(const char* tx);


        /**
         * @brief Draws vector of items. User can do anything with them
        */
        void drawObjectsToUiList();


        /**
         * @brief Draw objects to scene 
        */
        void drawObjectsToScene(ci::CameraPersp* _camera );

        void destroy();


        void swapShaders(ci::gl::GlslProgRef _shader );

    public :
        std::vector<ContentItemRef>                     _items; // Main items storage of slicer

        int32_t                                         _selected = -1; // Selected item in list of items. It is index of element in vector

    private : // Objects to preview mesh objects in toolrip
        ci::gl::FboRef                      _FboPtr;

};


#endif // __CHOCOLATA_SLICER_CONTENT_TREE_
