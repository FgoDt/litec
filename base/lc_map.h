#ifndef LITE_C_BASE_MAP_H_
#define LITE_C_BASE_MAP_H_

typedef enum lc_map_key_type{
    lc_map_key_char,
    lc_map_key_number,
    lc_map_key_ptr
}lc_map_key_type;

typedef struct lc_map_entry{
    void *key;
    void *val;
    struct lc_map_entry *next;
}lc_map_entry;

typedef struct lc_map{
    uint64_t (*hash)(uint64_t caps, void* key);
    int (*equal)(void* a, void *b);
    lc_map_entry** datas;
    void* usr_data;
    void (*cfree)(void* usr_data, void* data);
    int caps;
}lc_map;

lc_map* lc_map_create(void* usr_data, void(*cfree)(void* usr_data, void* data));

void lc_map_destroy(lc_map* m);

int lc_map_set_custom_hash(lc_map* m, uint64_t (*hash)(uint64_t caps, void* key), int(*equal)(void* a, void *b));

int lc_map_add(lc_map* m, void* key, void *data);

void* lc_map_get(lc_map* m, void* key);

void* lc_map_del(lc_map* m, void* key);

#endif
