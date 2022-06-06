#ifndef LITE_C_BASE_LIST_H_
#define LITE_C_BASE_LIST_H_

typedef struct lc_list_entry{
    struct lc_list_entry *next;
    void *data;
}lc_list_entry;

typedef struct lc_list{
    int count;
    void (*c_free)(void* usr_data, void* data);
    lc_list_entry* root;
    lc_list_entry* tail;
    void* usr_data;
}lc_list;

lc_list* lc_list_create(void* usr_data, void (*c_free)(void* usr_data, void* data));

void lc_list_destroy(lc_list* l);

int lc_list_add(lc_list* l, void *data);

int lc_list_remove(lc_list* l, void *data);

lc_list_entry* lc_list_entry_create();

void lc_list_entry_destroy(lc_list_entry* e);

//void* lc_list_get_index(lc_list* l, int index)

#define lc_list_foreach(l, e) \
    for(lc_list_entry *e = l->root; e != NULL ; e = e->next)

#endif
