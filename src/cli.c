#include "cli.h"

char *cli_help() {
    return "Simple dotfile configuration utility.\n"
           "Usage:\n"
           "	dotcfg [-fiV] [-d WORK_PATH] [<COMMAND> <ARGS...>]\n"
           "Options:\n"
           "  -h\tdisplay this help message\n"
           "  -v\tdisplay version number\n"
           "  -V\tdisplay verbose logging\n"
           "  -f\toverwrite existing files\n"
           "  -i\tinitialize work directory\n"
           "  -d\tprovide a work directory\n"
           "\t  (default: \"~/.dotcfg\")\n";
}

char *cli_version() {
    return "dotcfg 0.1.0\n";
}
