#ifndef __CHOCOLATA_SLICER_RECEIVER_
#define __CHOCOLATA_SLICER_RECEIVER_


#include "unordered_map"

#include "command.h"

class Receiver {
    private :
        Receiver();

    public :
        static Receiver& getInstance() { static Receiver tr; return tr; }


        Command readCommand(Command* _cmd = nullptr );




        std::unordered_map<int, Command>        _commandsLog; // Internal commands log

};



#endif // __CHOCOLATA_SLICER_RECEIVER_

