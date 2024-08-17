#ifndef SLC_H
#define SLC_H

#include <stdio.h>
#include <stdlib.h>

void slc_init(char *compiler_executable_name);
void slc_print_usage();
void slc_compile(char *source_file_name, char *output_file_name);
void slc_print_source_file_name();

#define SLC_INFO(STAGE, ...)                \
    printf("[SLC]: [%s INFO]: ", STAGE);    \
    printf(__VA_ARGS__);                    \

#define SLC_ERROR(STAGE, ...)               \
    printf("[SLC]: [%s ERROR]: ", STAGE);   \
    printf(__VA_ARGS__);                    \
    exit(1);

#endif // SLC_H