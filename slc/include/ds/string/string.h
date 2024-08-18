#ifndef SLC_DS_STRING_STRING_H
#define SLC_DS_STRING_STRING_H

#include "ds/string/string_view.h"
#include <stdio.h>

typedef struct string_struct string;

string *string_create_from_cstr(char *cstr);
string *string_create_from_string_view(string_view *string_view);
string *string_create_from_num(long num);
string *string_create_from_string(string *string);

void string_concat(string *dst, string *src);

void string_write_into_file(string *string, FILE *file);

#endif // SLC_DS_STRING_STRING_H