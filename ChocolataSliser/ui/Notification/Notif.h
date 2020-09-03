#ifndef __CHOCOLATA_SLICER_NOTIF_
#define __CHOCOLATA_SLICER_NOTIF_


#include <string>
#include <cinder/Log.h>

struct Notif {
    std::string             _title;

    std::string             _description;

    std::string             _dateilsLink;

    ci::log::Level          _level;



    bool draw();        // Returns true if notif is closed
};



#endif // __CHOCOLATA_SLICER_NOTIF_
