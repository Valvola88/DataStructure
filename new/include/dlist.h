
typedef struct dlist_node dlist_node;
typedef struct int_dlist_node int_dlist_node;

struct dlist_node
{
    dlist_node *prev;
    dlist_node *next;
    int count;
};

struct int_dlist_node
{
    dlist_node node;
    int value;
};