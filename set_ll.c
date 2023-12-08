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

// int aiv_set_find(aiv_set *set, const char *key)
// {
//     const size_t key_len = strlen(key);
//     const size_t hash = djb33x_hash(key, key_len);
//     const size_t index = hash % START_HASHMAP_SIZE;

//     //printf("hash of %s = %llu (index: %llu)\n", key, hash, index);

//     for (size_t i = 0; i < HASHMAP_SIZE_LIST; i++)
//     {
//         if (set->hashmap[index][i].key_len > 0)
//         {
//             if (set->hashmap[index][i].key_len == key_len && !memcmp(set->hashmap[index][i].key, key, key_len))
//             {
//                 printf("FOUND %s at index %llu slot %llu\n", key, index, i);
//                 return index;
//             }
//         }
//     }

//     printf("%s NOT FOUND\n", key);
//     return -1;
// }

void aiv_set_insert(aiv_set *set, const char *key)
{
    // if (aiv_set_find(set, key) == 1)
    // {
    //     printf("\n%s ALREADY EXIST\n", key);
    //     return;
    // }

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % START_HASHMAP_SIZE;
    list_item* list;
    //= ((list_item**)&(set->hashmap[index]))
    string_item value;
    printf("Index list: %llu\n", list);
    value.value = (char*)key;
    aiv_list_append(&list, (list_item*)&value);
    set->hashmap[index] = list;
}

void print_set(aiv_set *set)
{  
    for(int i = 0; i< START_HASHMAP_SIZE;i++)
    {
        printf("%llu\n", (unsigned long long)set->hashmap[i]);
        // string_item* si = &(*(set->hashmap[i])).item;
        // aiv_print_list((list_item*)si, 's');
    }
}

// int aiv_set_remove(aiv_set *set, const char *key)
// {
//     int j = aiv_set_find(set, key);
//     if (j>0)
//     {
//         set->hashmap[j][0].key = NULL;
//     }
//     return j;
// }

int main(int argc, char **argv)
{
    aiv_set myset;
    memset(&myset, 0, sizeof(aiv_set));

    aiv_set_insert(&myset, "Fortnite");
    aiv_set_insert(&myset, "Fortnite2");
    print_set(&myset);

    
    string_item* si = &(*(myset.hashmap[0])).item;
    printf("List %llu\n",  (unsigned long long)si);
    printf("Element %s\n", si->value);
    si = &(*(myset.hashmap[2])).item;
    printf("List %llu\n",  (unsigned long long)si);
    printf("Element %s\n", si->value);
    // aiv_set_insert(&myset, "Death Knight");
    // aiv_set_insert(&myset, "Demon Hunter");
    // aiv_set_insert(&myset, "Druid");
    // aiv_set_insert(&myset, "Hunter");
    // aiv_set_insert(&myset, "Mage");
    // aiv_set_insert(&myset, "Shaman");
    // aiv_set_insert(&myset, "Priest");
    // aiv_set_insert(&myset, "Paladin");
    // aiv_set_insert(&myset, "Rogue");
    // aiv_set_insert(&myset, "Warlock");
    // aiv_set_insert(&myset, "Warrior");
    // aiv_set_insert(&myset, "Monk");

    // print_set(&myset);
    // aiv_set_find(&myset, "XYZ");

    // aiv_set_remove(&myset, "Monk");


    return 0;
}