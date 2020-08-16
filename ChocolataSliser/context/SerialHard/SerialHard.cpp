#include "SerialHard.h"
#include "cinder/Exception.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


#include <unistd.h>
#include <iostream>

#include <sys/types.h>

void __serialHardSetupTio(int fd) {
	struct termios newtio;

	newtio.c_cflag = B19200 | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = 0;
	newtio.c_oflag = 0;
	newtio.c_lflag = 0;
	newtio.c_cc[VMIN] = 1;
	newtio.c_cc[VTIME] = 0;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);
}


void __serialHardOpen(struct __SerialHard* _serial) {
	if ((_serial->__port_descriptor = open(_serial->__port, O_RDWR | O_NOCTTY)) < 0 )
		throw cinder::Exception("ERR : SerialHard object didn't open");

	tcgetattr(_serial->__port_descriptor, &_serial->__tio);
	__serialHardSetupTio(_serial->__port_descriptor);

}


void __serialHardClose(struct __SerialHard* _serial ) {
	tcsetattr(_serial->__port_descriptor, TCSANOW, &_serial->__tio);
	close(_serial->__port_descriptor);
}


void serial_clear(__SerialHard* _serial ) {
	tcflush(_serial->__port_descriptor, TCIOFLUSH);
}


bool __serialHardIsOpen(struct __SerialHard * _serial ) {
	if (lseek(_serial->__port_descriptor, 0, SEEK_CUR) <= 0 ) { return false; }

	return true;
}

