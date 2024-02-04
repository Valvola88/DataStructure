#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "main.h"


#pragma region Old_LList
#pragma endregion

int_item* aiv_make_int_item(int i)
{
    int_item* result = (int_item *)malloc(sizeof(int_item));
    result->value = i;

    return result;
}

string_item* aiv_make_item_string(const char* value)
{
    string_item* result = (string_item*)malloc(sizeof(string_item));
    result->value = value;
    result->list_item.count = 0;
    result->list_item.next = NULL;
    return result;
}

void aiv_destroy_llist(list_item *head)
{
    list_item *current = head;
    list_item *next = current->next;

    while (next)
    {
        next = current->next;
        free(current);
        current = next;
    }
    
}

list_item* aiv_list_get_tail(list_item *head)
{
    if (!head)
        return NULL;

    list_item* current_item = head;
    list_item* last_item = head;

    while (current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
}

list_item* aiv_list_append(list_item** head, list_item* item) 
{

    list_item* tail = aiv_list_get_tail(*head);

    if (!tail)
    {
        *head = item;
        (*head)->count = 1;
    }
    else
    {
        tail->next = item;
        (*head)->count++;
    }

    item->next = NULL;
    return item;
}

unsigned int aiv_list_length(list_item* head){
    return head->count;
}

list_item* aiv_list_pop(list_item** head)
{
    if (!(*head))
        return NULL;
    
    list_item* current_head= *head;
    const unsigned int current_count = current_head->count;
    *head = (*head)->next;
    if (*head)
    {
        (*head)->count = current_count - 1;
    }
    current_head->next = NULL;

    return current_head;
}

void aiv_print_list(list_item* head, const char list_type)
{
    list_item* curr_item = head;

    if (!head)
    {
        printf("[]\n");
        return;
    }

    if (list_type == 'i')
    {
        while (curr_item)
        {
            printf("[%d]", ((int_item*)curr_item)->value);
            curr_item = curr_item->next;
        }
    }
    else if (list_type == 's')
    {
        while (curr_item != NULL)
        {
            printf("-");
            printf("[%s]", ((string_item*)curr_item)->value);
            curr_item = curr_item->next;
        }
    }
    printf("\n");
    
}

list_item* aiv_get_list(list_item* head, const  int num)
{
    if (num >= aiv_list_length(head))
        return NULL;
    
    unsigned int curr_num = num;
    list_item* return_item = head;
    while (curr_num > 0)
    {
        return_item = return_item->next;
        curr_num--;
    }

    return return_item;
}

list_item* aiv_remove_list_number(list_item** head, const unsigned int array_num)
{
    if (array_num >= (*head)->count)
        return NULL;
    
    if (!(*head))
        return NULL;
    
    if (array_num == 0)
        return aiv_list_pop(head);
    
    list_item* h = *head;
    list_item* prev_item = *head;
    list_item* curr_item = (*head)->next;
    list_item* return_item = NULL;

    int depth = 1;
    while (depth <= array_num)
    {
        if (depth == array_num)
        {
            return_item = curr_item;
            prev_item->next = curr_item->next;
            h->count--;
            return return_item;
            
        }

        prev_item = prev_item->next;
        curr_item = curr_item->next;
        depth++;   
    }
    (*head)->count--;
    return NULL;
    
}

list_item* aiv_remove_item_list(list_item** head, list_item* item)
{
    if (!(*head))
        return NULL;

    if (*head == item)
    {
        //printf("Pop\t");
        return aiv_list_pop(head);
    }

    list_item* return_item = NULL;
    list_item* prev_item = *head;
    list_item* curr_item = (*head)->next;
        
    while (curr_item)
    {
        if (curr_item == item)
        {
            return_item = curr_item;
            prev_item->next = curr_item->next;
            return return_item;
        }

        prev_item = prev_item->next;
        curr_item = curr_item->next;   
    }
    
    return NULL;
}

void aiv_reverse_list(list_item** head)
{
    const unsigned int current_count = (*head)->count;

    list_item* h = *head;
    list_item* t = aiv_list_get_tail(*head);

    const unsigned int l = aiv_list_length(h);
    h->count = 0;

    list_item* a = *head;
    list_item* b = a->next;
    list_item* c;

    //const unsigned int l = aiv_list_length(*head) - 1;

    for(int i = 0; i< l - 1 ;i++){
        c = b->next;
        b->next = a;
        a = b;
        b = c;
    }

    h->next = NULL;
    *head = t;
    (*head)->count = l;

}

//#define add_list(x,y) aiv_list_append(&x,&y)
list_item* aiv_get_by_string(list_item* head,const char* string)
{
    list_item* current = head;
    if (head == NULL)
        return NULL;

    int i = 0;
    while (current)
    {
        //printf("I: %i: Current = %s, Paragon = %s.\n",i,((string_item*)current)->value, string);
        if((strcmp(((string_item*)current)->value, string)) == 0)
        {
            //printf("String %s found at %i\n", string, i);
            return current;
        }
        i++;
        current = current->next;
    }
    
    //printf("%s Not Found\n", string);
    return NULL;
    
}

void aiv_free_llist(list_item* head)
{
    list_item* current = head;
    if (head == NULL)
        return;
    list_item* next = current->next;

    while(next)
    {
        free(current);
        current = next;
        next = current->next;
    }
    
    free(current);
}

void main_string_llist(){
    list_item* head = NULL;
    string_item* si1 = aiv_make_item_string("Test1");
    string_item* si2 = aiv_make_item_string("Test2");
    string_item* si3 = aiv_make_item_string("Test3");

    aiv_list_append(&head, (list_item*)si1);
    aiv_list_append(&head, (list_item*)si2);
    aiv_list_append(&head, (list_item*)si3);
   
    aiv_print_list(head, 's');

    aiv_remove_item_list(&head, aiv_get_by_string(head,"Test1"));
    aiv_print_list(head, 's');

    const char* search = "Test1";

    string_item* searched = (string_item*)aiv_get_by_string(head, search);
    if (searched)
    {
        printf("%s found", search);
    }
    else
    {
        printf("%s not found", search);
    }

    aiv_free_llist(head);
}

void main_int_llist(){
        list_item* head = NULL;

    int_item* ii1 = aiv_make_int_item(100);
    int_item* ii2 = aiv_make_int_item(200);
    int_item* ii3 = aiv_make_int_item(300);
    int_item* ii4 = aiv_make_int_item(400);
    int_item* ii5 = aiv_make_int_item(500);
    int_item* ii6 = aiv_make_int_item(600);
    int_item* ii7 = aiv_make_int_item(700);
    int_item* ii8 = aiv_make_int_item(800);
    // int_item ii1;
    // ii1.value = 100;
    // int_item ii2;
    // ii2.value = 200;
    // int_item ii3;
    // ii3.value = 300;
    // int_item ii4;
    // ii4.value = 400;
    // int_item ii5;
    // ii5.value = 500;
    // int_item ii6;
    // ii6.value = 600;
    // int_item ii7;
    // ii7.value = 700;
    // int_item ii8;
    // ii8.value = 800;

    //add_list(head, ii1);
    aiv_list_append(&head, (list_item*)ii1);
    aiv_list_append(&head, (list_item*)ii2);
    aiv_list_append(&head, (list_item*)ii3);
    aiv_list_append(&head, (list_item*)ii4);
    aiv_list_append(&head, (list_item*)ii5);
    aiv_list_append(&head, (list_item*)ii6);
    aiv_list_append(&head, (list_item*)ii7);
    aiv_list_append(&head, (list_item*)ii8);

    aiv_print_list(head, 'i');

    aiv_remove_list_number(&head , 4);
    aiv_print_list(head, 'i');

    aiv_reverse_list(&head);
    aiv_print_list(head, 'i');
    int_item* searched = (int_item*)aiv_get_list(head, 3);
    
    if (searched)
        printf("{%i}",searched->value);
    else
        printf("NULL");

}