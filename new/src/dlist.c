#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "dlist.h"
#include "main.h"

unsigned int list_get_len(dlist_node* head){
    return head->count;
}

dlist_node *list_get_tail(dlist_node *head)
{
    if (!head)
        return NULL;

    dlist_node* current_item = head;
    dlist_node* last_item = head;

    while (current_item)
    {
        last_item = current_item;
        current_item = current_item->next;
    }
    
    return last_item;
    
}

dlist_node *list_append (dlist_node **head, dlist_node *item)
{
    dlist_node *tail = list_get_tail(*head);
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

    item->prev = tail;
    item->next = NULL;

    return item;
}

dlist_node* list_get_pos(dlist_node** head, const  int pos)
{
    if (pos >= list_get_len(*head))
        return NULL;
    
    unsigned int curr_num = pos;
    dlist_node* return_item = *head;
    while (curr_num > 0)
    {
        return_item = return_item->next;
        curr_num--;
    }

    return return_item;
}

dlist_node *list_append_after (dlist_node **head, dlist_node *item, const int pos)
{
    if (pos < 0 || pos > list_get_len(*head) - 1)
        return NULL;

    if (pos == list_get_len(*head) - 1)
    {
        dlist_node* prev_node = list_get_tail(*head);

        prev_node->next = item;
        item->prev = prev_node;
        item->next = NULL;
        
    }
    else 
    {
        dlist_node* prev_node = list_get_pos(head, pos);
        dlist_node* next_node = prev_node->next;

        prev_node->next = item;
        next_node->prev = item;
        item->prev = prev_node;
        item->next = next_node;
    }
    
    (*head)->count++;

    return item;
}

dlist_node *list_insert_before (dlist_node **head, dlist_node *item, const int pos)
{
    if (pos < 0 || pos > list_get_len(*head))
        return NULL;

    if (pos == 0)
    {
        dlist_node* next_item = (*head);

        next_item->prev = item;
        item->prev = NULL;
        item->next = next_item;

        item->count = next_item->count;

        *head = item;
        
    }
    else 
    {
        dlist_node* next_node = list_get_pos(head, pos);
        dlist_node* prev_node = next_node->prev;

        prev_node->next = item;
        next_node->prev = item;
        item->prev = prev_node;
        item->next = next_node;
    }
    
    (*head)->count++;

    return item;
}

dlist_node *list_remove(dlist_node **head, const int pos)
{
    dlist_node* to_remove = list_get_pos(head, pos);

    if(to_remove == NULL)
        return NULL;

    (*head)->count--;
    if (to_remove->prev == NULL)
    {
        (*head)->next = to_remove->next;
        (*head) = (*head)->next;
    }
    else
    {
        to_remove->prev->next = to_remove->next;
    }

    if (to_remove->next == NULL)
    {
        
    }
    else
    {
        to_remove->next->prev = to_remove->prev;
    }

    return to_remove;
}

void aiv_print_list(dlist_node* head, const char list_type)
{
    dlist_node* curr_item = head;
    if (list_type == 'i')
    {
        while (curr_item)
        {
            printf("[%d]", (*(int_dlist_node*)curr_item).value);
            curr_item = curr_item->next;
        }
    }
    printf("\n"); 
}

void aiv_shuffle_list(dlist_node **head)
{
    dlist_node *curr_node = *head;
    const unsigned int l = list_get_len(*head);
    (*head)->count = 0;

    dlist_node *ord_node_list[l];
    int ord_list[l];
    int shf_list[l];

    for(int i  =0 ; i< l; i++)
    {
        ord_list[i] = i;
        ord_node_list[i] = curr_node;
        curr_node = curr_node->next;
        ord_node_list[i]->prev = NULL;
        ord_node_list[i]->next = NULL;
    }
    for(int i = 0;  i<l; i++)
    {
        int t = -1;
        while (t == -1)
        {
            int r = rand()%l;
            t = ord_list[r];
        }

        ord_list[t] = -1;
        shf_list[i] = t;
        //printf("[%i]", shf_list[i]);
    }

    *head = NULL;
    for(int i = 0; i < l; i++)
    {
        list_append(head, ord_node_list[shf_list[i]]);
    }

}

void main_dlist()
{
    srand(time(NULL));
    dlist_node *head = NULL;

    int_dlist_node arr[8];

    for (int i = 0 ; i < 8; i++)
    {
        arr[i].value = (i + 1) * 100;
        list_append(&head, (dlist_node *)&arr[i]);
    }

    aiv_print_list(head, 'i');

    int_dlist_node i1;
    i1.value = 150;
    int_dlist_node i2;
    i2.value = 250;

    list_insert_before(&head, (dlist_node *)&i1, 3);
    list_append_after(&head, (dlist_node *)&i2, 6);
    aiv_print_list(head, 'i');
    list_remove(&head, 8);
    aiv_print_list(head, 'i');

    aiv_shuffle_list(&head);
    aiv_print_list(head, 'i');
    printf("{%i}\n",((int_dlist_node*)list_get_pos(&head, 3))->value);
    printf("l: (%i)",list_get_len(head));
}