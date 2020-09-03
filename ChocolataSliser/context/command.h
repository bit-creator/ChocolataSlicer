#ifndef __CHOCOLATA_SLICER_COMMAND_
#define __CHOCOLATA_SLICER_COMMAND_


#include <vector>
#include <string>

struct Command {
    uint8_t                     __cmd; // Opcode

    std::vector<float>          __args; // Arguments

    // std::string                 __native; // String command

};


#endif // __CHOCOLATA_SLICER_COMMAND_

