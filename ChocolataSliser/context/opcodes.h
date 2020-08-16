#ifndef __CHOCOLATA_SLICER_OPCODES_
#define __CHOCOLATA_SLICER_OPCODES_



// tokens
#define OP_TERMINATOR                   (uint8_t)0x01
#define OP_SEPARATOR                    (uint8_t)0x02



// Connection
#define OP_CONNECT_REQUEST              (uint8_t)0xff
#define OP_CONNECT_ACCEPT               (uint8_t)0xfe
#define OP_CONNECT_REFUSED              (uint8_t)0xfd
#define OP_DISCONNECT                   (uint8_t)0xfc


// System
#define OP_INTERUPTION                  (int32_t)5
#define OP_GET_VERSION                  (uint8_t)0xfb


#endif // __CHOCOLATA_SLICER_OPCODES_

