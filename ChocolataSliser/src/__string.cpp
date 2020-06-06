#include "__string.h"

#include <memory>

// #include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int            _str_find(const char* __a, const char* __b ) {
    int j = 0;
    for (int i = 0; i < strlen(__a) && j < strlen(__b); i++ ) {
        if (__a[i] == __b[j] ) j++;
        else if (j > 0 ) j = 0;
    }

    if (j < (strlen(__b) - 1) ) return 1;
    return 0;
}


int            _str_find_first(const char* __a, const char* __b ) {
    const char* ptr;
    if ( (ptr = strstr(__a, __b)) == NULL ) return -1;

    return (int)(ptr - __a);
}


int            _str_find_first_after(const char* __a, const char* __b, size_t __of ) {
    if (__of > strlen(__a) ) return -1;
    int pos = -1;
    int j = 0;
    for (int i = __of; i < strlen(__a) && j < strlen(__b); i++ ) {
        if (__a[i] == __b[j] ) { j++; if (pos == -1) { pos = i; } }
        else if (j > 0 ) return 1;
    }

    if (j < (strlen(__b) - 1) ) return -1;
    return pos;
}


int _str_split(const char *txt, char delim, char ***tokens) {
    int *tklen, *t, count = 1;
    char **arr, *p = (char *) txt;

    while (*p != '\0') if (*p++ == delim) count += 1;
    t = tklen = (int*)calloc (count, sizeof (int));
    for (p = (char *) txt; *p != '\0'; p++) *p == delim ? *t++ : (*t)++;
    *tokens = arr = (char**)malloc (count * sizeof (char *));
    t = tklen;
    p = *arr++ = (char*)calloc (*(t++) + 1, sizeof (char *));
    while (*txt != '\0')
    {
        if (*txt == delim)
        {
            p = *arr++ = (char*)calloc (*(t++) + 1, sizeof (char *));
            txt++;
        }
        else *p++ = *txt++;
    }

    free (tklen);
    return count;
}


int            _str_find_mask(const char* _f, char _mask[] ) {
    char** tkns;
    int nm = _str_split(_mask, '#', &tkns );
    int poss[nm];


    for (size_t i = 0; i < nm; i++) {
        // printf("Mask prompt : '%s'\n", tkns[i] );
        if (i == 0 ) { 
            poss[i] = _str_find_first(_f, tkns[i] );
            if ((poss[i] == -1) && (strcmp(tkns[i], "") != 0) ) return 1;
        }
        else {
            poss[i] = _str_find_first_after(_f, tkns[i], poss[i-1] );
            if ((poss[i] == -1) && (strcmp(tkns[i-1], "") != 0) ) return 1;
        }
    }


    return 0;
}


int            _str_cut(char *str, int begin, int len) {
    int l = strlen(str);

    if (len < 0) len = l - begin;
    if (begin + len > l) len = l - begin;
    memmove(str + begin, str + begin + len, l - len + 1);

    return len;
}


// find firest
// int pos = -1;
// for (int i = 0, j = 0; i < strlen(__a) && j < strlen(__b); i++ ) {
//     if (__a[i] == __b[j] ) { j++; if (pos == -1) { pos = i; } }
//     else if (j > 0 ) return 1;
// }

// return pos;