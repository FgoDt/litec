#ifndef LITE_C_BASE_STR_H_
#define LITE_C_BASE_STR_H_

#include <stdlib.h>
#include <string.h>
#include "vector.h"

typedef struct lc_str
{
    char *c_str;
    int len;
} lc_str;

lc_str *lc_str_create_with_len(const char *s, int len);

lc_str *lc_str_create(const char *s);

void lc_str_destroy(lc_str *str);

int lc_str_cmp_str(const lc_str *a, const lc_str *b);

int lc_str_cmp(const lc_str *a, const char *b);

int lc_str_index_of(const lc_str *a, const char *sub);

lc_str *lc_str_format(const char *fmt, ...);

int lc_str_append(lc_str *str, const char *data);

int lc_str_append_lc_str(lc_str *str, const lc_str *data);

lc_vector *lc_str_split_char(lc_str *str, char sp);

lc_str *lc_str_get_one_line(const char *str);

#endif
