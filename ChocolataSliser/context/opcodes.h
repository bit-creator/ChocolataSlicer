#ifndef __CHOCOLATA_SLICER_OPCODES_
#define __CHOCOLATA_SLICER_OPCODES_

#define _OP_IS_EXECUTABLE(x)    ( ((x < OP_STACK_EXECUTE) && (x >= OP_DISABLE_LED)) ? true : false )

#define _OP_ARGS_AS_BYTES       true            // float args will transfer as (sizeof(float)). iy means float value transfers as 4 bytes

/*  General/Executable/Geters/Exceptions  */

/** General(systems) opcodes */
#define OP_INTERUPTION                  (uint8_t)7
#define OP_DISCONNECT                   (uint8_t)0xfc
#define OP_TERMINATOR                   (uint8_t)0x01
#define OP_SEPARATOR                    (uint8_t)0x02


#define OP_CONNECT_REQUEST              (uint8_t)0xff
#define OP_CONNECT_ACCEPT               (uint8_t)0xfe
#define OP_CONNECT_REFUSED              (uint8_t)0xfd



/** Geters opcodes */
#define OP_GET_RESPOND                  (uint8_t)0xfb
#define OP_GET_VERSION                  (uint8_t)0xfa
#define OP_GET_STACK_SIZE               (uint8_t)0xf9


/** Executable opcodes */
#define OP_STACK_BEGIN_FILLING          (uint8_t)0xf8
#define OP_STACK_END_FILLING            (uint8_t)0xf7
#define OP_STACK_CLEAR                  (uint8_t)0xf6


#define OP_STACK_EXECUTE                (uint8_t)0xf5

#define OP_ENABLE_LED                   (uint8_t)0xf4
#define OP_DISABLE_LED                  (uint8_t)0xf3


/** Exception opcodes */




#endif // __CHOCOLATA_SLICER_OPCODES_

