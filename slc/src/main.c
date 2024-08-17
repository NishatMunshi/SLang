#include "main.h"
#include "ui/slc.h"

int main(int argc, char **argv) {
    slc_init(argv[0]);
    if (argc < 2) {
        slc_print_usage();
        SLC_ERROR("USAGE", "no source file provided.\n");
    }
    if (argc < 3) {
        slc_print_usage();
        SLC_ERROR("USAGE", "no output file provided.\n");
    }
    slc_compile(argv[1], argv[2]);
    return 0;
}