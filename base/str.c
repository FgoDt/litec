#include "str.h"
#include "mem.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

lc_str *lc_str_create_with_len(const char *s, int len)
{
  lc_str *str = lc_mallocz(sizeof(*str));
  str->c_str = lc_malloc(len + 1);
  str->c_str[len] = 0;
  memcpy(str->c_str, s, len);
  str->len = len;
  return str;
}

lc_str *lc_str_create(const char *s)
{
  return lc_str_create_with_len(s, strlen(s));
}

void lc_str_destroy(lc_str *str)
{
  if (!str)
  {
    return;
  }
  if (str->c_str)
  {
    lc_free(str->c_str);
  }
  lc_free(str);
}

int lc_str_cmp(const lc_str *a, const char *b)
{
  return strcmp(a->c_str, b);
}

int lc_str_cmp_str(const lc_str *a, const lc_str *b)
{
  if (a->len != b->len)
  {
    return a->len - b->len;
  }
  return strcmp(a->c_str, b->c_str);
}

int lc_str_index_of(const lc_str *a, const char *sub)
{
  char *pos = strstr(a->c_str, sub);
  if (pos == NULL)
  {
    return -1;
  }
  return pos - a->c_str;
}

lc_str *lc_str_format(const char *fmt, ...)
{
  char tmp[1024];
  va_list args;
  va_start(args, fmt);
  int n = vsnprintf(tmp, 1023, fmt, args);
  tmp[n] = 0;
  va_end(args);
  return lc_str_create(tmp);
}

int lc_str_append(lc_str *str, const char *data)
{
  int c_str_len = strlen(data);
  int total_len = str->len + c_str_len;

  char *tmp = lc_malloc(total_len + 1);
  tmp[total_len] = 0;
  memcpy(tmp, str->c_str, str->len);
  memcpy(tmp + str->len, data, c_str_len);
  lc_free(str->c_str);
  str->c_str = tmp;
  str->len = total_len;
  return 0;
}

int lc_str_append_lc_str(lc_str *str, const lc_str *data)
{
  int total_len = str->len + data->len;
  char *tmp = lc_malloc(total_len + 1);
  tmp[total_len] = 0;
  memcpy(tmp, str->c_str, str->len);
  memcpy(tmp + str->len, data->c_str, data->len);
  lc_free(str->c_str);
  str->c_str = tmp;
  str->len = total_len;
  return 0;
}

static void lc_dummy_custom_free(void *usr_data, void *data)
{
  lc_str *str = data;
  if (!str)
  {
    return;
  }
  lc_str_destroy(str);
}

lc_vector *lc_str_split_char(lc_str *str, char sp)
{
  int i = 0;
  int s = 0;

  lc_vector *v = lc_vector_create(0, NULL, lc_dummy_custom_free);
  while (i <= str->len)
  {
    if (str->c_str[i] == sp)
    {
      lc_str *val = lc_str_create_with_len(str->c_str + s, i - s);
      lc_vector_append(v, val);
      s = i + 1;
    }
    i++;
  }
  if (i > s)
  {
    lc_str *val = lc_str_create_with_len(str->c_str + s, i - s);
    lc_vector_append(v, val);
  }
  return v;
}

lc_str *lc_str_get_one_line(const char *str)
{
  int i = 0;
  while (str[i] != '\n' && str[i] != 0)
  {
    i++;
  }
  lc_str *val = lc_str_create_with_len(str, i);
  return val;
}
