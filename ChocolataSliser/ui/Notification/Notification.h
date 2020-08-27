#ifndef __CHOCOLATA_SLICER_NOTIFICATIONS_
#define __CHOCOLATA_SLICER_NOTIFICATIONS_


#include <string>
#include <vector>

#include <cinder/Log.h>
#include <cinder/CinderImGui.h>

#include "ui/uiWindow.h"
#include "Notif.h"



class Notifications {
    private :
        std::vector<Notif>       _notifications;

    public :
        static Notifications& GetInstance() { static Notifications nt; return nt; }


        void addNotif(Notif ntf) { _notifications.push_back(ntf); }

        void draw();

};


#endif // __CHOCOLATA_SLICER_NOTIFICATIONS_

