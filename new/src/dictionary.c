#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include "main.h"
#pragma region
#pragma endregion


dictionary_item* dictionary_make_item(const char* key, const int value)
{
    dictionary_item* result = (dictionary_item*)malloc(sizeof(dictionary_item));
    result->key = *aiv_make_string_set_item(key);
    result->value= value;

    return result;
}

dictionary_item* aiv_dictionary_insert(aiv_set *head, const char *key, int val)
{
    if (aiv_dictionary_get_item_key(head, key))
    {

    }
    else

    dictionary_item* result = dictionary_make_item(key, const int val);
    aiv_set_insert(head, result);

    return 0;
}

int aiv_print_dictionary(aiv_set *head)
{
    for (int i = 0; i< head->dimension;i++)
    {
        if (!head->hashmap[i])
            continue;

        dictionary_item* dm = (dictionary_item*)(head->hashmap[i]);
        
        while (dm)
        {
            printf("{%s : %i}",dm->key.item.value, (dm->value));
            dm = (dictionary_item*)dm->key.item.list_item.next;
        }
    }

    return 0;
}

dictionary_item* aiv_dictionary_get_item_key(aiv_set* head,const char* key)
{
    return (dictionary_item*)aiv_set_find(head, key);
}


void main_dictionary()
{
    aiv_set myset;
    dictionary_item* di_1 = dictionary_make_item("Tough Love", 150);
    dictionary_item* di_2 = dictionary_make_item("Torn Photo", 341);
    set_init(&myset);

    aiv_dictionary_insert(&myset, di_1);
    aiv_dictionary_insert(&myset, di_2);

    // char *s = "XJY";
    // dictionary_item *item = dictionary_get_item_key(&myset, s);
    // if (item)
    //     printf("[%s]: %d", s, item->value);

    aiv_print_dictionary(&myset);

}