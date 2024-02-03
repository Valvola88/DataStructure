#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "mycollections.h"

//extern void aiv_print_list(list_item* head, const char list_type);

// struct set_item
// {
//     string_item item;
// };

// struct aiv_set
// {
//     int dimension;
//     struct set_item* hashmap[START_HASHMAP_SIZE];
// };

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

    set_item* r_item = (set_item*)aiv_get_by_string((list_item*)&(set->hashmap[index]->item),key);
    if (r_item)
    {
        printf("Found %s at index %d\n", key, (int)index);
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

void aiv_set_insert(aiv_set *head, set_item *value, const char *key)
{

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % START_HASHMAP_SIZE;
    printf("Key %s | Index %llu\n",key,index);
    //string_item value;
    value->item.value = (char*)key;
    //value.value = (char*)key;

    aiv_list_append((list_item**)&(head->hashmap[index]), (list_item*)value);
    // printf("Idx: %llu\n", set->hashmap[0]);
    //aiv_print_list(set->hashmap[index], 's');
    // printf("Nx: %llu\n", value.list_item.next);

    //return value;
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
        set_item* si = (set->hashmap[i]);
        aiv_print_list((list_item *)si, 's');
    }
}

int aiv_set_remove(aiv_set *set, const char *key)
{
    set_item* item_to_remove = aiv_set_find(set, key);

    if (item_to_remove == NULL)
        return -1;

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);

    const size_t index = hash % START_HASHMAP_SIZE;

    list_item* head = (list_item*)&(set->hashmap[index]->item);
    aiv_remove_item_list(&head, (list_item*)item_to_remove);

    return 0;
}

// int main(int argc, char **argv)
// {
//     aiv_set myset;
//     set_item items[32];
//     char* classes[] =
//     {
//         "Death Knight",
//         "Demon Hunter",
//         "Druid",
//         "Hunter",
//         "Mage",
//         "Paladin",
//         "Priest",
//         "Rogue",
//         "Shaman",
//         "Warlock",
//         "Warrior"
//     };
//     for(int i = 0; i< 4;i++)
//     {
//         myset.hashmap[i] = NULL;
//     }
//     for(int i = 0; i< 11;i++)
//     {
//         aiv_set_insert(&myset, &items[i], classes[i]);
//     }
//     aiv_set_insert(&myset, &items[12], classes[1]);
//     print_set(&myset);
//     aiv_set_find(&myset, "Warlock");
//     aiv_set_find(&myset, "XQC");
//     aiv_set_remove(&myset, "Rogue");
//     print_set(&myset);
//     // aiv_set_remove(&myset, "Monk");
//     return 0;
// }