#ifndef __DOT_STRING_
#define __DOT_STRING_

#include <string.h>

// Find __b in __a and return 0 if trua or 1
int            _str_find(const char* __a, const char* __b );


// Find first __d in __c and return pos or -1
int            _str_find_first(const char* __a, const char* __b );


// Find first __d in __c aafter __of and return pos or -1. __of index of char in array
int            _str_find_first_after(const char* __c, const char* __d, size_t __of );


// Splits string txt by delim and writes it to tokens
int            _str_split(const char *txt, char delim, char ***tokens);


// Find mask(pattern) in the line and return 0 if it exist or 1 if no
int            _str_find_mask(const char* _f, char* _mask = "#");


// Cut str from begin to end and write to it
int            _str_cut(char *str, int begin, int len);


#endif // __DOT_STRING_


