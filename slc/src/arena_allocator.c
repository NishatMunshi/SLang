#include "../include/arena_allocator.h"
#include "../include/slc.h"

#include <stdio.h>
#include <stdlib.h>

#define ARENA_ALLOCATOR_CARACITY_IN_BYTES (1024ul * 1024ul)

typedef struct arena_allocator_struct {
    void *begin;
    size_t next_free_spot;
} arena_allocator;

static arena_allocator *allocator = NULL;

#define ARENA_ALLOCATOR_ERROR() printf("[ARENA_ALLOCATOR ERROR]: ")

void arena_allocator_init() {
    allocator = calloc(1, ARENA_ALLOCATOR_CARACITY_IN_BYTES);
    allocator->begin = (char *)allocator + sizeof(struct arena_allocator_struct);
    if (!allocator->begin) {
        slc_print_compiler_execuatable_name();
        ARENA_ALLOCATOR_ERROR();
        printf("unable to allocate %zu bytes for arena allocator\n", ARENA_ALLOCATOR_CARACITY_IN_BYTES);
        exit(1);
    }
    allocator->next_free_spot = 0;
}

void *arena_allocator_allocate(size_t num_of_bytes){
    if (allocator->next_free_spot + num_of_bytes > ARENA_ALLOCATOR_CARACITY_IN_BYTES) {
        slc_print_compiler_execuatable_name();
        ARENA_ALLOCATOR_ERROR();
        printf("not enough memory to allocate %zu bytes\n", num_of_bytes);
        exit(1);
    }
    void *pointer = (char *)allocator->begin + allocator->next_free_spot;
    allocator->next_free_spot += num_of_bytes;
    return pointer;
}