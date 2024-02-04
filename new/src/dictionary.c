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
    dictionary_item* already_in_set = aiv_dictionary_get_item_key(head, key);
    if (already_in_set)
    {
        printf("KEY %s ALREADY EXIST\n", key);

        already_in_set->value = val;
        return NULL;
    }

    dictionary_item* result = dictionary_make_item(key, val);
    aiv_set_insert_item(head, &(result->key));

    return NULL;
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
            printf("{%s : %i}\n",dm->key.item.value, (dm->value));
            dm = (dictionary_item*)dm->key.item.list_item.next;
        }
    }

    return 0;
}

dictionary_item* aiv_dictionary_get_item_key(aiv_set* head,const char* key)
{
    return (dictionary_item*)aiv_set_find(head, key);
}

dictionary_item* aiv_dictionary_remove(aiv_set* head,const char* key)
{
    if (!aiv_dictionary_get_item_key(head, key))
    {
        printf("KEY %s IS NOT IN SET", key);
        return NULL;
    }

    aiv_set_remove(head, key);
    return NULL;
}


void main_dictionary()
{
    aiv_set* myset  = set_init(4);
    //dictionary_item* di_1 = dictionary_make_item("Tough Love", 150);
    //dictionary_item* di_2 = dictionary_make_item("Torn Photo", 341);

    dictionary_item* di_1 = aiv_dictionary_insert(myset, "Tough Love", 150);
    dictionary_item* di_2 = aiv_dictionary_insert(myset, "Torn Photo", 341);
    dictionary_item* di_3 = aiv_dictionary_insert(myset, "Champion Belt", 208);
    dictionary_item* di_4 = aiv_dictionary_insert(myset, "Red Stew", 621);
    aiv_print_dictionary(myset);

    aiv_dictionary_remove(myset, "Champion Belt");

    // char *s = "XJY";
    // dictionary_item *item = dictionary_get_item_key(&myset, s);
    dictionary_item* di_6 = aiv_dictionary_insert(myset, "Torn Photo", 526);
    // if (item)
    //     printf("[%s]: %d", s, item->value);

    aiv_print_dictionary(myset);
    printf("EOF");

}