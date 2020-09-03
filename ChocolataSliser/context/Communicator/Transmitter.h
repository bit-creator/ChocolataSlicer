#ifndef __CHOCOLATA_SLICER_TRANSMITTER_
#define __CHOCOLATA_SLICER_TRANSMITTER_


#include "command.h"

#include "unordered_map"


class Transmitter {
    private :
        Transmitter();

    public :
        static Transmitter& getInstance() { static Transmitter tr; return tr; }


        /* FIXME: Maybe you will be needed add separators between arguments */
        void sendCommand(Command _cmd );





        std::unordered_map<int, Command>                _commandsLog; // Internal commands log

};


#endif // __CHOCOLATA_SLICER_TRANSMITTER_

