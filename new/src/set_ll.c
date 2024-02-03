#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "set_ll.h"
#include "main.h"

size_t djb33x_hash(const char *key, const size_t keylen)
{
    size_t hash = 5381;

    for (size_t i = 0; i < keylen; i++)
    {
        hash = ((hash << 5) + hash) ^ key[i];
    }

    return hash;
}

set_item* aiv_make_string_set_item(const char* string)
{
    set_item* result = (set_item*)malloc(sizeof(set_item));
    result->item = *(aiv_make_item_string(string));

    return result;

}

set_item* aiv_set_find(aiv_set *set, const char *key)
{
    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % START_HASHMAP_SIZE;

    set_item* r_item = (set_item*)aiv_get_by_string((list_item*)&(set->hashmap[index]->item),key);
    if (r_item)
    {
        //printf("Found %s at index %d\n", key, (int)index);
        return r_item;
    }

    //printf("%s NOT FOUND\n", key);
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

set_item* aiv_set_insert(aiv_set *head, const char *key)
{
    if (aiv_set_find(head, key))
    {
        printf("Key %s already exists\n", key);
        return NULL;
    }

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % START_HASHMAP_SIZE;

    set_item* result = aiv_make_string_set_item(key);

    aiv_list_append((list_item**)&(head->hashmap[index]), (list_item *)&(result->item));

    return result;
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

set_item * aiv_set_remove(aiv_set *set, const char *key)
{
    set_item* item_to_remove = aiv_set_find(set, key);

    if (item_to_remove == NULL)
        return NULL;

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % START_HASHMAP_SIZE;

    list_item* head = (list_item*)(set->hashmap[index]);
    list_item* search = aiv_get_by_string(head, key);

    if (head == search)
    {
        list_item* next = search->next;
        aiv_remove_item_list(&head, search);
        set->hashmap[index] = (set_item *)next;
    }
    else
        aiv_remove_item_list(&head, search);

    return item_to_remove;
}

void print_found_list(aiv_set *set, const char* key)
{
    set_item* searched = aiv_set_find(set, key);
    if (searched)
    {
        printf("%s found\n", searched->item.value);
    }
    else
    {
        printf("%s not found\n", key);
    }
}

void print_remove_list(aiv_set *set, const char* key)
{
    set_item* searched = aiv_set_remove(set, key);
    if (searched)
    {
        printf("%s removed\n", key);
    }
    else
    {
        printf("%s not removed\n", key);
    }
}

void main_set_ll()
{
    aiv_set myset;
    set_item* items[16];
    char* classes[] =
    {
        "Death Knight",
        "Demon Hunter",
        "Druid",
        "Hunter",
        "Mage",
        "Paladin",
        "Priest",
        "Rogue",
        "Shaman",
        "Warlock",
        "Warrior"
    };
    set_init(&myset);
    
    for(int i = 0; i< 11;i++)
    {
        items[i] = aiv_set_insert(&myset, classes[i]);
    }
    set_item* monk = aiv_set_insert(&myset, "Monk");
    print_set(&myset);
    // printf("\n");
    // aiv_set_insert(&myset, monk, monk->item.value);
    // aiv_set_insert(&myset, monk, monk->item.value);
    print_found_list(&myset, "Warlock");
    print_found_list(&myset, "Mechanic");

    //print_remove_list(&myset, "Rogue");
    print_remove_list(&myset, "Mage");
    print_remove_list(&myset, "Druid");
    print_remove_list(&myset, "Death Knight");
    print_remove_list(&myset, "Mechanic");

    print_set(&myset);


    // aiv_set_find(&myset, "Mechanic");
     ;
    // print_set(&myset);
}