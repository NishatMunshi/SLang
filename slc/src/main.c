#include "main.h"
#include "ui/ui.h"
#include "slc/slc.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        ui_print_usage(argv[0]);
        UI_ERROR("USAGE", "no source file provided.\n");
    }
    if (argc < 3) {
        ui_print_usage(argv[0]);
        UI_ERROR("USAGE", "no output file provided.\n");
    }
    slc_compile(argv[0], argv[1], argv[2]);
    return 0;
}