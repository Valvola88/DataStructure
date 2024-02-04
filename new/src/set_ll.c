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

aiv_set* set_init(const int set_size)
{
    aiv_set* result = (aiv_set*)malloc(sizeof(aiv_set));
    result->dimension = set_size;
    
    result->hashmap[set_size] = (set_item*)malloc(sizeof(set_item) * set_size);

    for(int i = 0; i< result->dimension;i++)
    {
        result->hashmap[i] = NULL;
    }

    return result;
}

void aiv_set_insert_item(aiv_set *head, set_item *item)
{
    if (item == NULL)
        return;

    if (aiv_set_find(head, item->item.value))
    {
        printf("Key %s already exists\n", item->item.value);
        return;
    }

    const size_t key_len = strlen(item->item.value);
    const size_t hash = djb33x_hash(item->item.value, key_len);
    const size_t index = hash % head->dimension;

    aiv_list_append((list_item**)&(head->hashmap[index]), (list_item *)&(item->item));
}

set_item* aiv_set_insert_string(aiv_set *head, const char *key)
{
    if (aiv_set_find(head, key))
    {
        printf("Key %s already exists\n", key);
        return NULL;
    }

    const size_t key_len = strlen(key);
    const size_t hash = djb33x_hash(key, key_len);
    const size_t index = hash % head->dimension;

    set_item* result = aiv_make_string_set_item(key);

    aiv_list_append((list_item**)&(head->hashmap[index]), (list_item *)&(result->item));

    return result;
}

void print_set(aiv_set *set)
{  
    for(int i = 0; i< set->dimension;i++)
    {
        printf("%i)",i+ 1);
        if (set->hashmap[i] == NULL)
        {
            printf("-[NULL]\n");
            continue;
        }
        // //printf("%llu\n", (unsigned long long)set->hashmap[i]);
        set_item* si = (set->hashmap[i]);
        aiv_print_list((list_item *)si, 's');
    }
}

set_item* aiv_set_remove(aiv_set *set, const char *key)
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

aiv_set* aiv_reash_set(aiv_set* set, const int size)
{
    aiv_set* new_set = set_init(size);
    new_set->dimension = size;

    for(int i = 0; i < set->dimension; i++)
    {
        set_item* item;
        do
        {
            //printf("POP \t");
            item = (set_item*)aiv_list_pop((list_item **)&(set->hashmap[i]));
            if (item)
            {
                aiv_set_insert_item(new_set,item);
                printf("READDED %s\n",item->item.value);
            }
        }
        while(item);
    }

    return new_set;

}

void aiv_free_set(aiv_set* set)
{
    for(int i = 0; i < set->dimension; i++)
    {
        aiv_free_llist((list_item*)set->hashmap[i]);
    }

    free(set);
}

void main_set_ll()
{
    aiv_set* myset = set_init(5);
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
    
    for(int i = 0; i< 11;i++)
    {
        items[i] = aiv_set_insert_string(myset, classes[i]);
    }
    set_item* monk = aiv_set_insert_string(myset, "Monk");
    print_set(myset);
    // printf("\n");
    // aiv_set_insert(&myset, monk, monk->item.value);
    // aiv_set_insert(&myset, monk, monk->item.value);
    print_found_list(myset, "Warlock");
    print_found_list(myset, "Mechanic");

    //print_remove_list(&myset, "Rogue");
    print_remove_list(myset, "Mage");
    print_remove_list(myset, "Druid");
    print_remove_list(myset, "Death Knight");
    print_remove_list(myset, "Mechanic");

    print_set(myset);

    myset = aiv_reash_set(myset, 9);

    print_set(myset);
    aiv_free_set(myset);
    // aiv_set_find(&myset, "Mechanic");
    // print_set(&myset);
}