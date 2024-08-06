#ifndef SLC_H
#define SLC_H

void slc_init(char *compiler_executable_name);
void slc_print_usage();
void slc_print_error_and_exit(char *message);
void slc_compile(char *source_file_name, char *output_file_name);
void slc_print_source_file_name();
void slc_print_compiler_execuatable_name();

#endif // SLC_H