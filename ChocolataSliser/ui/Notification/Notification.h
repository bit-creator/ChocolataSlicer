#ifndef __CHOCOLATA_SLICER_NOTIFICATIONS_
#define __CHOCOLATA_SLICER_NOTIFICATIONS_


#include <string>
#include <vector>

#include <cinder/Log.h>
#include <cinder/CinderImGui.h>

#include "Notif.h"


class Notifications {
    private :
        std::vector<Notif>       _notifications;

    public :
        ImVec2                  _notifSize = { 273, 68 };

        uint                    _maxNotifs = 3;

    public :
        static Notifications& GetInstance() { static Notifications nt; return nt; }


        void addNotif(Notif ntf) { _notifications.push_back(ntf); }

        void draw();

};


#endif // __CHOCOLATA_SLICER_NOTIFICATIONS_

