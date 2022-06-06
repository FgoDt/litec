#include "lc_map.h"
#include "lc_mem.h"

//default key use char* key
static uint64_t default_hash(uint64_t caps, void *key)
{
    uint64_t ret = 0;
    const char* str_key = key;
    while(*str_key){
        ret = (ret << 4) + *str++;
        uint64_t g = ret & 0xF000000000000000;
        if(g){
            ret ^= g >> 56;
        }
        ret &= ~g;
    }
    return ret % caps;
}

static int default_equal(void *key1, void *key2)
{
    return !strcmp((const char*)key1, (const char*)key2)
}

lc_map* lc_map_create(void* usr_data, void(*cfree)(void* usr_data, void* data))
{
    lc_map* m = lc_mallocz(sizeof(*m));
    m->usr_data = usr_data;
    m->cfree = cfree;
    return m;
}

void lc_map_destroy(lc_map* m)
{
    if(!m){
        return;
    }
    if(m->datas){
        for(uint64_t i = 0; i < m->caps; i ++){
            for(lc_map_entry* e = m->datas[i]; e != NULL; ){
                lc_map_entry* next = e->next;
                if(m->cfree){
                    m->cfree(m->usr_data, e->val);
                }
                lc_free(e);
                e = next;
            }
        }
        lc_free(m->datas);
    }

    lc_free(m->datas);
}

int lc_map_set_custom_hash(lc_map* m, uint64_t (*hash)(uint64_t caps, void* key), int(*equal)(void* a, void *b))
{
    if(!hash || !equal){
        return -1;
    }

    m->hash = hash;
    m->equal = equal;
    return 0;
}

int lc_map_add(lc_map* m, void* key, void *data)
{
    uint64_t loc = m->hash(m->caps, key);
    lc_map_entry* e = lc_mallocz(sizeof(*e));
    e->key = key;
    e->data = data;
    e->next = m->datas[loc];
    m->datas[loc] = e;
    return 0;
}

void* lc_map_get(lc_map* m, void* key)
{
    uint64_t loc = m->hash(m->caps, key);
    lc_map_entry* e = m->datas[loc];
    for(; e != NULL; e = e->next){
        if(m->equal(key, e->key)){
            return e->data;
        }
    }
    return NULL;
}

int lc_map_del(lc_map* m, void* key)
{
    uint64_t loc = m->hash(m->caps, key);
    lc_map_entry* e = m->datas[loc];
    lc_map_entry* pre = NULL;
    for(; e != NULL; e = e->next){
        if(m->equal(key, e->key)){
            if(pre){
                pre->next = e->next;
            }else{
                e->datas[loc] = NULL;
            }
            lc_free(e);
            return 0;
        }
        pre = e;
    }
    return -1;
}


