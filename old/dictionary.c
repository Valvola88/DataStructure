#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "mycollections.h"
#pragma region
#pragma endregion


int aiv_dictionary_insert(aiv_set *head, dictionary_item *value, const char *key, int val)
{
    value->value = val;
    aiv_set_insert(head, &(value->key), key);

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


int main(int argc, char **argv)
{
    aiv_set myset;
    dictionary_item items[32];

    char* keys[] = 
    {
        "Key",
        "Door"
    };

    int values[] = 
    {
        54,
        68
    };

    set_init(&myset);

    aiv_dictionary_insert(&myset, &items[0], keys[0], values[0]);
    aiv_dictionary_insert(&myset, &items[1], keys[1], values[1]);

    // char *s = "XJY";
    // dictionary_item *item = dictionary_get_item_key(&myset, s);
    // if (item)
    //     printf("[%s]: %d", s, item->value);

    aiv_print_dictionary(&myset);

}