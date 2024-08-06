#include "../include/main.h"
#include "../include/slc.h"

int main(int argc, char **argv) {
    slc_init(argv[0]);
    if (argc < 2) {
        slc_print_usage();
        slc_print_error_and_exit("[USAGE ERROR]: no source file provided");
    }
    if (argc < 3) {
        slc_print_usage();
        slc_print_error_and_exit("[USAGE ERROR]: no output file provided");
    }
    slc_compile(argv[1], argv[2]);
    return 0;
}