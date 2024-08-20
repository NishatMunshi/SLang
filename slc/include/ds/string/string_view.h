#ifndef SLC_DS_STRING_STRING_VIEW_H
#define SLC_DS_STRING_STRING_VIEW_H

#include <stdbool.h>
#include <stddef.h>

typedef struct string_view_struct string_view;

string_view *string_view_create(char *cstr, size_t length);
string_view *string_view_create_from_cstr(char *cstr);

bool string_view_in_bound(string_view *string_view, size_t index);

char *string_view_get_cstr(string_view *string_view);
size_t string_view_get_length(string_view *string_view);
char string_view_at(string_view *string_view, size_t index);

bool string_view_compare(string_view *string_view_1, string_view *string_view_2);
bool string_view_compare_with_cstr(string_view *string_view, char *cstr);

void string_view_print(string_view *string_view);

#endif  // SLC_DS_STRING_STRING_VIEW_H