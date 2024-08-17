#ifndef SLC_UI_H
#define SLC_UI_H

#include <stdio.h>
#include <stdlib.h>

#define UI_INFO(STAGE, ...) {               \
    printf("[SLC]: [%s INFO]: ", STAGE);    \
    printf(__VA_ARGS__);                    \
}

#define UI_ERROR(STAGE, ...) {              \
    printf("[SLC]: [%s ERROR]: ", STAGE);   \
    printf(__VA_ARGS__);                    \
    exit(1);                                \
}

#define UI_PRINT_USAGE(COMPILER_EXECUTABLE_NAME) {                                          \
    UI_INFO("USAGE", "%s <source_filename> <output_filename>\n", COMPILER_EXECUTABLE_NAME); \
}

#endif // SLC_UI_H