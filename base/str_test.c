#include "str.h"
#include <stdio.h>

int main()
{
    lc_str *str = lc_str_create("abcdef");
    lc_str_destroy(str);
    str = lc_str_format("abc:%02.2f %d %s %x haha\n", 0.2f, 20, "200", 120);
    lc_str_append(str, "gg ff gogo abc def=12 sdfbc=213\n");
    lc_vector *sps = lc_str_split_char(str, ' ');
    // lc_str *cmp_str = lc_str_create("20");
    // if (!lc_str_cmp(lc_vector_get(sps, 1), cmp_str))
    //{
    // printf("error on cmp \n");
    //}
    for (int i = 0; i < sps->size; i++)
    {
        lc_str *str = lc_vector_get(sps, i);
        printf("%s\n", str->c_str);
    }
    lc_vector_destroy(sps);
    lc_str_destroy(str);
    // lc_str_destroy(cmp_str);
    return 0;
}
