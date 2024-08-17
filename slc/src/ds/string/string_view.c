#include "ds/string/string_view.h"
#include "memory/arena_allocator.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

struct string_view_struct {
    char *beg;
    size_t length;
};

string_view *string_view_create(char *cstr, size_t length) {
    string_view *string_view = arena_allocator_allocate(sizeof(struct string_view_struct));
    string_view->beg = cstr;
    string_view->length = length;

    return string_view;
}

string_view *string_view_create_from_cstr(char *cstr) {
    return string_view_create(cstr, strlen(cstr));
}

void string_view_print(string_view *string_view) {
    for (size_t i = 0; i < string_view->length; ++i) {
        printf("%c", string_view->beg[i]);
    }
}

char string_view_at(string_view *string_view, size_t index) {
    return string_view->beg[index];
}

bool string_view_in_bound(string_view *string_view, size_t index) {
    return index < string_view->length;
}

char *string_view_get_cstr(string_view *string_view) {
    return string_view->beg;
}
size_t string_view_get_length(string_view *string_view) {
    return string_view->length;
}

bool string_view_compare(string_view *string_view_1, string_view *string_view_2) {
    if (string_view_get_length(string_view_1) != string_view_get_length(string_view_2)) {
        return false;
    }

    for (size_t i = 0; string_view_in_bound(string_view_1, i); ++i) {
        if (string_view_at(string_view_1, i) != string_view_at(string_view_2, i)) {
            return false;
        }
    }
    return true;
}

bool string_view_compare_with_ctr(string_view *string_view, char *cstr){
    if(string_view_get_length(string_view) != strlen(cstr)) {
        return false;
    }
    for (size_t i = 0; string_view_in_bound(string_view, i); ++i) {
        if (string_view_at(string_view, i) != cstr[i]) {
            return false;
        }
    }
    return true;
}
