#ifndef AIV_SET_LL_H
#define AIV_SET_LL_H

#define START_HASHMAP_SIZE 4
#include "llist.h"

typedef struct set_item set_item;
typedef struct aiv_set aiv_set;

struct set_item
{
    string_item item;
};

struct aiv_set
{
    int dimension;
    struct set_item* hashmap[];
};

set_item* aiv_make_string_set_item(const char* string);
set_item* aiv_set_find(aiv_set *set, const char *key);
aiv_set* set_init(const int set_size);
set_item* aiv_set_insert_string(aiv_set *head,const char *key);
void aiv_set_insert_item(aiv_set *head, set_item *item);
void print_set(aiv_set *set);
set_item * aiv_set_remove(aiv_set *set, const char *key);
void aiv_free_set(aiv_set* set);
#endif