#ifndef LITE_C_VECTOR_H_
#define LITE_C_VECTOR_H_

typedef struct lc_vector
{
    void **data;
    void (*cfree)(void *usr_data, void *data);
    void *usr_data;
    unsigned int caps;
    unsigned int size;
} lc_vector;

lc_vector *lc_vector_create(unsigned int caps, void *usr_data, void (*cfree)(void *usr_data, void *data));

void lc_vector_destroy(lc_vector *v);

int lc_vector_append(lc_vector *v, void *data);

int lc_vector_remove(lc_vector *v, void *data);

int lc_vector_remove_index(lc_vector *v, unsigned int index);

int lc_vector_set(lc_vector *v, unsigned int index, void *data);

void *lc_vector_get(lc_vector *v, unsigned int index);

#endif