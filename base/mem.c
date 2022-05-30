#include "mem.h"
#include <stdlib.h>
#include <string.h>


void* lc_malloc(size_t size)
{
    return malloc(size);
}

void* lc_mallocz(size_t size)
{
    void *ret = lite_c_malloc(size);
    memset(ret, 0, size);
    return ret;
}

void lc_free(void* p)
{
    free(p);
}
