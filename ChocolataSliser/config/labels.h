#ifndef _PLANET_MOV_LABLES_H
#define _PLANET_MOV_LABLES_H


#include <vector>


enum Label_ {
    Label_winSize = 0,
    Label_winPos,
    Label_winFrameRate

};

static std::vector<std::pair<const char*, const char*> > Labels = std::initializer_list<std::pair<const char*, const char*> > {
    { "windowSize", "winSize" },                                // Label_winSize

    { "windowPosition", "winPos" },                             // Label_winPos

    { "windowFrameRate", "winFrameRate" },                         // Label_winFrameRate

};



#endif // _PLANET_MOV_LABLES_H


