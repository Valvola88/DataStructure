#ifndef AIV_DICTIONARY_H
#define AIV_DICTIONARY_H
#include "set_ll.h"

typedef struct dictionary_item dictionary_item;

struct dictionary_item
{
    set_item key;
    int value;
};

dictionary_item* dictionary_make_item(const char* key, const int value);
dictionary_item* aiv_dictionary_insert(aiv_set *head, const char *key, int val);
int aiv_print_dictionary(aiv_set *head);
dictionary_item* aiv_dictionary_get_item_key(aiv_set* head,const char* key);

#endif