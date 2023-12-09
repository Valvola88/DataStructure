#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "mycollections.h"

#define START_HASHMAP_SIZE 4
#define HASHMAP_SIZE_LIST 1

typedef struct set_item set_item;
typedef struct aiv_set aiv_set;

//extern void aiv_print_list(list_item* head, const char list_type);

struct set_item
{
    string_item item;
};

struct aiv_set
{
    int dimension;
    struct set_item* hashmap[START_HASHMAP_SIZE];
};

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

set_item* aiv_set_find(aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % START_HASHMAP_SIZE;

    set_item* r_item = aiv_get_by_string(&(set->hashmap[index]->item),key);
    if (r_item)
    {
        printf("Found %s at index %i\n", key, index);
        return r_item;
    }

    printf("%s NOT FOUND\n", key);
    return r_item;
}

void set_init(aiv_set * set)
{
    set->dimension = START_HASHMAP_SIZE;
    for(int i = 0; i< set->dimension;i++)
    {
        set->hashmap[i] = NULL;
    }
}


string_item aiv_set_insert(aiv_set *set, const char *key)
{

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % START_HASHMAP_SIZE;
    printf("Key %s | Index %llu\n",key,index);
    string_item value;
    value.value = (char*)key;
    aiv_list_append(&(set->hashmap[index]), &value);
    // printf("Idx: %llu\n", set->hashmap[0]);
    //aiv_print_list(set->hashmap[index], 's');
    // printf("Nx: %llu\n", value.list_item.next);

    return value;
}

void print_set(aiv_set *set)
{  
    for(int i = 0; i< START_HASHMAP_SIZE;i++)
    {
        if (set->hashmap[i] == NULL)
        {
            printf("NULL\n");
            continue;
        }
        // //printf("%llu\n", (unsigned long long)set->hashmap[i]);
        list_item* si = (set->hashmap[i]);
        aiv_print_list(si, 's');
    }
}

int aiv_set_remove(aiv_set *set, const char *key)
{
    list_item* item_to_remove = aiv_set_find(set, key);

    if (item_to_remove == NULL)
        return -1;

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % START_HASHMAP_SIZE;

    list_item* head = &(set->hashmap[index]->item);
    aiv_remove_item_list(&head, item_to_remove);

    return 0;
}

int main(int argc, char **argv)
{
    aiv_set myset;

    for(int i = 0; i< 4;i++)
    {
        myset.hashmap[i] = NULL;
    }
    //memset(items, 0, sizeof(set_item*) * 4 );
    // print_set(&myset);
    
    //print_set(&myset);
    //set_init(&myset);
    //printf("Idx: %llu\n", myset.hashmap[0]);
    // aiv_print_list(myset.hashmap[0], 's');
    // aiv_set_insert(&myset, "Fortnite");
    // print_set(&myset);
    // aiv_set_insert(&myset, "Fortnite2");
    // print_set(&myset);
    //printf("Idx: %llu\n", myset.hashmap[0]);
    //printf("Nx: %llu\n", si1.list_item.next);
    //aiv_print_list((&myset)->hashmap[0], 's');
    //aiv_set_insert(&myset, "Fortnite2");
    //printf("XD");

    
    // string_item* si = &(*(myset.hashmap[0])).item;
    // printf("List %llu\n",  (unsigned long long)si);
    // printf("Element %s\n", si->value);
    // si = &(*(myset.hashmap[2])).item;
    // printf("List %llu\n",  (unsigned long long)si);
    // printf("Element %s\n", si->value);
    aiv_set_insert(&myset, "Death Knight");
    aiv_set_insert(&myset, "Demon Hunter");
    aiv_set_insert(&myset, "Druid");
    aiv_set_insert(&myset, "Hunter");
    aiv_set_insert(&myset, "Mage");
    aiv_set_insert(&myset, "Shaman");
    aiv_set_insert(&myset, "Priest");
    aiv_set_insert(&myset, "Paladin");
    aiv_set_insert(&myset, "Rogue");
    aiv_set_insert(&myset, "Warlock");
    aiv_set_insert(&myset, "Warrior");
    aiv_set_insert(&myset, "Monk");

    print_set(&myset);
    aiv_set_find(&myset, "Warlock");
    aiv_set_find(&myset, "XQC");

    aiv_set_remove(&myset, "Rogue");
    print_set(&myset);

    // aiv_set_remove(&myset, "Monk");


    return 0;
}