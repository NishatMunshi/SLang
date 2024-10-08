#include "main.h"

#include "slc/slc.h"
#include "ui/ui.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        UI_PRINT_USAGE(argv[0]);
        UI_ERROR("USAGE", "no source file provided.\n");
    }
    if (argc < 3) {
        UI_PRINT_USAGE(argv[0]);
        UI_ERROR("USAGE", "no output file provided.\n");
    }
    slc_compile(argv[0], argv[1], argv[2]);
    return 0;
}