#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "mycollections.h"


int aiv_dictionary_insert(aiv_set *head, dictionary_item *value, const char *key, const int* val)
{
    value->value = val;
    aiv_set_insert(head, &(value->key), key);
}

int aiv_print_dictionary(aiv_set *head)
{
    for (int i = 0; i< head->dimension;i++)
    {
        if (!head->hashmap[i])
            continue;

        dictionary_item* dm = head->hashmap[i];
        
        while (dm)
        {
            printf("{%s : %i}",dm->key.item.value, *(dm->value));
            dm = dm->key.item.list_item.next;
        }
    }
}

int main(int argc, char **argv)
{
    aiv_set myset;
    dictionary_item items[32];

    char* keys[] = 
    {
        "Key",
        "Key 2"
    };

    int values[] = 
    {
        54,
        68
    };

    set_init(&myset);

    aiv_dictionary_insert(&myset, &items[0], keys[0], &values[0]);

    aiv_print_dictionary(&myset);


}