#define START_HASHMAP_SIZE 4
#define HASHMAP_SIZE_LIST 1


typedef struct aiv_list_item list_item;
typedef struct aiv_int_item int_item;
typedef struct aiv_string_item string_item;
typedef struct set_item set_item;
typedef struct aiv_set aiv_set;
typedef struct dictionary_item dictionary_item;

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
    char* value;
};

struct set_item
{
    string_item item;
};

struct dictionary_item
{
    set_item key;
    int *value;
};

struct aiv_set
{
    int dimension;
    struct set_item* hashmap[START_HASHMAP_SIZE];
};

unsigned int aiv_list_length(list_item* head);
void aiv_print_list(list_item* head, const char list_type);
list_item* aiv_get_list(list_item** head, const  int num);
list_item* aiv_list_get_tail(list_item *head);
list_item* aiv_get_by_string(list_item* head, char* string);
list_item* aiv_remove_item_list(list_item** head, list_item* item);
list_item* aiv_list_append(list_item** head, list_item* item);
list_item* aiv_remove_list_number(list_item** head, const unsigned int array_num);


int aiv_set_remove(aiv_set *set, const char *key);
void aiv_set_insert(aiv_set *head, set_item *value, const char *key);
set_item* aiv_set_find(aiv_set *set, const char *key);
void print_set(aiv_set *set);
void set_init(aiv_set * set);