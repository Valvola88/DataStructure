#ifndef AIV_DICTIONARY_H
#define AIV_DICTIONARY_H
#include "set_ll.h"

typedef struct dictionary_item dictionary_item;

struct dictionary_item
{
    set_item key;
    int value;
};

#endif