#ifndef SLC_UI_H
#define SLC_UI_H

#include <stdio.h>
#include <stdlib.h>

void ui_print_usage(char *compiler_executable_name);

#define UI_INFO(STAGE, ...) {                   \
        printf("[SLC]: [%s INFO]: ", STAGE);    \
        printf(__VA_ARGS__);                    \
    }

#define UI_ERROR(STAGE, ...) {                  \
        printf("[SLC]: [%s ERROR]: ", STAGE);   \
        printf(__VA_ARGS__);                    \
        exit(1);\
    }

#endif // SLC_UI_H