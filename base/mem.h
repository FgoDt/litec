#ifndef LITE_C_BASE_MEM_H_
#define LITE_C_BASE_MEM_H_

#include <stdlib.h>

void* lc_malloc(size_t size);

void* lc_mallocz(size_t size);

void lc_free(void* p);

#endif
