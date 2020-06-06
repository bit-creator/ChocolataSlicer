#ifndef __UI_
#define __UI_

#include <memory>
#include "cinder/CinderImGui.h"

/**
 * Scope of all abstract ui components for full control of everything on 2d ui frame buffer
*/
namespace ui {
    class uiViewport;                                           // Viewport contains all window scope. It makes available window docking and direct drawing UI widgets on it. uiViewport contains uiWindowHandlers for more docking
    typedef std::shared_ptr<class ui::uiViewport>                   uiViewportRef;


    class uiWindow;                                             // uiWindow is smallest ui component for structuring users possibilities to one box. Windows should be able to dock on viewport
    typedef std::shared_ptr<class ui::uiWindow>                     uiWindowRef;


    class uiWindowHandler;                                      // uiWindowHandler is storage scope of windows which gives possibility for window docking. uiWindowHandler constains windows for docking
    typedef std::shared_ptr<class ui::uiWindowHandler>              uiWindowHandlerRef;



    class uiContentItem;
    typedef std::shared_ptr<uiContentItem>                           uiContentItemRef;

    class uiContentTree;
    typedef std::shared_ptr<class ui::uiContentTree>                uiContentTreeRef;



    // uiLoaction_ enum for controlling general position of any viewable objects in some local space
    enum uiLoaction_ {
        uiLoaction_None,
        uiLoaction_Left,
        uiLoaction_Right,

        uiLoaction_Top,
        uiLoaction_Down
    };

};


#endif // __UI_