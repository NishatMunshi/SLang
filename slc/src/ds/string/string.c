#include "ds/string/string.h"
#include "memory/arena_allocator.h"
#include "utils/utils.h"

#include <stdio.h>

struct string_struct {
    string_view *string_view;
    struct string_struct *next;
};

string *string_create_from_cstr(char *cstr) {
    return string_create_from_string_view(string_view_create_from_cstr(cstr));
}

string *string_create_from_string_view(string_view *string_view) {
    string *string = arena_allocator_allocate(sizeof(struct string_struct));
    string->string_view = string_view;
    string->next = NULL;
    return string;
}

string *string_create_from_num(long num) {
    char *template = "%li";
    char *cstr = arena_allocator_allocate(utils_count_digits_in_num(utils_absl(num)) + 2); // 1 char for a '-' sign, 1 char for the null char
    sprintf(cstr, template, num);
    return string_create_from_cstr(cstr);
}

string *string_create_from_string(string *string) {
    return string_create_from_string_view(string->string_view);
}

void string_concat(string *dst, string *src) {
    if (dst->next == NULL) {
        dst->next = src;
    } else {
        string_concat(dst->next, src);
    }
}

void string_write_into_file(string *string, FILE *file) {
    if (string == NULL) {
        return;
    } else {
        fwrite(string_view_get_cstr(string->string_view), sizeof(char), string_view_get_length(string->string_view), file);
        string_write_into_file(string->next, file);
    }
}
