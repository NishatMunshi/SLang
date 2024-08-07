#ifndef SLC_UTILS_H
#define SLC_UTILS_H

#include <assert.h>
#include <stddef.h>

size_t utils_count_digits_in_num(size_t num);
size_t utils_absl(long num);

#define UNREACHABLE assert(false && "unreachable")

#endif // SLC_UTILS_H