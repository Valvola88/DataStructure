#ifndef AIV_LLIST_H
#define AIV_LLIST_H

typedef struct aiv_list_item list_item;
typedef struct aiv_int_item int_item;
typedef struct aiv_string_item string_item;

struct aiv_list_item
{
    struct aiv_list_item* next;
    unsigned int count;
};

struct aiv_int_item
{
    list_item list_item;
    int value;
};

struct aiv_string_item
{
    list_item list_item;
    const char* value;
};

//MAKE
string_item* aiv_make_item_string(const char* value);

//ADD
list_item* aiv_list_append(list_item** head, list_item* item);

//GET
list_item* aiv_get_list(list_item* head, const  int num);
list_item* aiv_list_get_tail(list_item *head);
list_item* aiv_get_by_string(list_item* head,const char* string);

//REMOVE
list_item* aiv_remove_item_list(list_item** head, list_item* item);
list_item* aiv_remove_list_number(list_item** head, const unsigned int array_num);

//UTILS
void aiv_print_list(list_item* head, const char list_type);
unsigned int aiv_list_length(list_item* head);
#endif