#include "utils/utils.h"
#include "memory/arena_allocator.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t utils_count_digits_in_num(size_t num) {
    size_t i = 0;
    do {
        num = num / 10;
        i++;
    } while (num);
    return i;
}

size_t utils_absl(long num) { 
    return num >= 0 ? (size_t)num : (size_t)(-num);
}