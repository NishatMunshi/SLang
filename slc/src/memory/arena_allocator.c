#include "memory/arena_allocator.h"
#include "ui/slc.h"

#include <stdio.h>
#include <stdlib.h>

#define ARENA_ALLOCATOR_CARACITY_IN_BYTES (1024ul * 1024ul)

typedef struct arena_allocator_struct {
    void *begin;
    size_t next_free_spot;
} arena_allocator;

static arena_allocator *allocator = NULL;

#define ARENA_ALLOCATOR_ERROR(...) SLC_ERROR("ARENA_ALLOCATOR", __VA_ARGS__)

void arena_allocator_init() {
    allocator = calloc(1, ARENA_ALLOCATOR_CARACITY_IN_BYTES);
    allocator->begin = (char *)allocator + sizeof(struct arena_allocator_struct);
    if (!allocator->begin) {
        ARENA_ALLOCATOR_ERROR("unable to allocate %zu bytes for arena allocator\n", ARENA_ALLOCATOR_CARACITY_IN_BYTES);
    }
    allocator->next_free_spot = 0;
}

void *arena_allocator_allocate(size_t num_of_bytes){
    if (allocator->next_free_spot + num_of_bytes > ARENA_ALLOCATOR_CARACITY_IN_BYTES) {
        ARENA_ALLOCATOR_ERROR("not enough memory to allocate %zu bytes\n", num_of_bytes);
    }
    void *pointer = (char *)allocator->begin + allocator->next_free_spot;
    allocator->next_free_spot += num_of_bytes;
    return pointer;
}