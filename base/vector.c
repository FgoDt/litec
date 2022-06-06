#include "vector.h"
#include "mem.h"
#include <string.h>

lc_vector *lc_vector_create(unsigned int caps, void *usr_data, void (*cfree)(void *usr_data, void *data))
{
    lc_vector *v = lc_mallocz(sizeof(*v));
    v->caps = caps;
    v->usr_data = usr_data;
    v->cfree = cfree;
    if (v->caps == 0)
    {
        v->caps = 8;
    }
    v->data = lc_mallocz(sizeof(void *) * v->caps);
    return v;
}

void lc_vector_destroy(lc_vector *v)
{
    if (!v)
    {
        return;
    }

    if (v->data)
    {
        if (v->cfree)
        {
            for (size_t i = 0; i < v->size; i++)
            {
                v->cfree(v->usr_data, v->data[i]);
            }
        }
        lc_free(v->data);
    }
    lc_free(v);
}

static void lc_vector_extend(lc_vector *v)
{
    v->caps = v->caps * 2;
    void **tmp = lc_mallocz(sizeof(void *) * v->caps);
    memcpy(tmp, v->data, v->size * sizeof(void *));
    lc_free(v->data);
    v->data = tmp;
}

int lc_vector_append(lc_vector *v, void *data)
{
    if (v->size == v->caps)
    {
        lc_vector_extend(v);
    }
    v->data[v->size++] = data;
}

int lc_vector_remove(lc_vector *v, void *data)
{
    int del_index = -1;
    for (size_t i = 0; i < v->size; i++)
    {
        if (data == v->data[i])
        {
            del_index = i;
            break;
        }
    }
    if (del_index == -1)
    {
        return -1;
    }
    return lc_vector_remove_index(v, del_index);
}

int lc_vector_remove_index(lc_vector *v, unsigned int index)
{
    if (v->size <= index)
    {
        return -1;
    }
    for (size_t i = index; i < v->size - 1; i++)
    {
        v->data[i] = v->data[index + 1];
    }
    v->size--;
    return 0;
}

int lc_vector_set(lc_vector *v, unsigned int index, void *data)
{
    if (v->size < index)
    {
        return -1;
    }
    v->data[index] = data;
    return 0;
}

void *lc_vector_get(lc_vector *v, unsigned int index)
{
    if (v->size < index)
    {
        return NULL;
    }
    return v->data[index];
}
