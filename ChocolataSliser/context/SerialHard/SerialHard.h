#ifndef __CHOCOLATA_SLICER_SERIAL_HARD_
#define __CHOCOLATA_SLICER_SERIAL_HARD_



#include <stdio.h>
#include <termios.h>


struct __SerialHard {

    int                 __port_descriptor;
    struct termios      __tio;


    char *              __port;
	unsigned char       __c;

};



void __serialHardOpen(struct __SerialHard* _serial );

void __serialHardClose(struct __SerialHard* _serial );


bool __serialHardIsOpen(struct __SerialHard* _serial );


// extern "C" int hexatoi(const char * ln ) { return (int)strtol(ln, NULL, 0); }




#endif // __CHOCOLATA_SLICER_SERIAL_HARD_