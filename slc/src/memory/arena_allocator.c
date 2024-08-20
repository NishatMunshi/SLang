#include "memory/arena_allocator.h"

#include <stdio.h>
#include <stdlib.h>

#include "ui/ui.h"

#define ARENA_ALLOCATOR_CARACITY_IN_BYTES (1024ul * 1024ul)

static struct arena_allocator_struct {
    void *begin;
    size_t next_free_spot;
} arena_allocator = {0};

#define ARENA_ALLOCATOR_ERROR(...) UI_ERROR("ARENA_ALLOCATOR", __VA_ARGS__)

static void arena_allocator_init() {
    arena_allocator.begin = calloc(1, ARENA_ALLOCATOR_CARACITY_IN_BYTES);
    if (!arena_allocator.begin) {
        ARENA_ALLOCATOR_ERROR("unable to allocate %zu bytes for arena arena_allocator\n", ARENA_ALLOCATOR_CARACITY_IN_BYTES);
    }
    arena_allocator.next_free_spot = 0;
}

void *arena_allocator_allocate(size_t num_of_bytes) {
    if (!arena_allocator.begin) {
        arena_allocator_init();
    }
    if (arena_allocator.next_free_spot + num_of_bytes > ARENA_ALLOCATOR_CARACITY_IN_BYTES) {
        ARENA_ALLOCATOR_ERROR("not enough memory to allocate %zu bytes\n", num_of_bytes);
    }
    void *pointer = (char *)arena_allocator.begin + arena_allocator.next_free_spot;
    arena_allocator.next_free_spot += num_of_bytes;
    return pointer;
}