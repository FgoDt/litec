#ifndef LITE_C_BASE_STR_H_
#define LITE_C_BASE_STR_H_

#include <stdlib.h>
#include <string.h>

typedef struct lc_str{
    char* c_str;
    int len;
}lc_str;

lc_str* lc_str_create(const char* s);

void lc_str_destroy(lc_str* str);

int lc_str_cmp(const lc_str* a, const lc_str* b);

int lc_str_index_of(const lc_str* a, const char* sub);

lc_str* lc_str_format(const char* fmt, ...);

#endif
