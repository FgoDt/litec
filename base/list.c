#include "list.h"
#include "mem.h"
lc_list* lc_list_create(void* usr_data, void (*c_free)(void* usr_data, void* data))
{
    lc_list* l = lc_mallocz(sizeof(*l));
    l->c_free = c_free;
    l->usr_data = usr_data;
    return l;
}

void lc_list_destroy(lc_list* l)
{
    if(!l){
        return;
    }
    lc_list_foreach(l, e){
        if(l->c_free){
            l->c_free(l->usr_data, e->data);
        }
    }
    for(lc_list_entry* e = l->root; e != NULL; ){
        lc_list_entry* next = e->next;
        lc_list_entry_destroy(e);
        e = next;
    }
    lc_lite_free(e);
}

int lc_list_add(lc_list* l, void *data)
{
    lc_list_entry* e = lc_list_entry_create();
    e->data = data;

    if(l->root == NULL){
        l->root = e;
        l->tail = e;
    }else{
        l->tail->next = e;
        l->tail = e;
    }

    return 0;
}

int lc_list_remove(lc_list* l, void *data)
{
    if(l == NULL){
        return -1;
    }

    lc_list_entry* pre = NULL;

    lc_list_foreach(l, e){
        if(e->data == data){
            if(pre == NULL){
                l->root = e->next;
            }else{
                pre->next = e->next;
            }
            if(e == l->tail){
                l->tail = e->next;
            }
	    lc_list_entry_destroy(e);
            break;
        }
        pre = e;
    }
}

lc_list_entry* lc_list_entry_create();

void lc_list_entry_destroy(lc_list_entry* e);


