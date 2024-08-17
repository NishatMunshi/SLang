#include "ui/ui.h"

void ui_print_usage(char *compiler_executable_name) {
    UI_INFO("USAGE", "%s <source_filename> <output_filename>\n", compiler_executable_name);
}