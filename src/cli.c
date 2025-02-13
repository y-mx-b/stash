#include "cli.h"

char *cli_get_help() {
    return "Simple dotfile configuration utility.\n"
           "Usage:\n"
           "	stash [-fisV] [-d WORK_PATH] [<COMMAND> <ARGS> ...]\n"
           "Options:\n"
           "  -h\tdisplay this help message\n"
           "  -v\tdisplay version number\n"
           "  -V\tdisplay verbose logging\n"
           "  -d\tprovide a work directory\n"
           "\t  (default: \"~/.stash\")\n"
           "  -f\toverwrite existing files\n"
           "  -i\tinitialize work directory\n"
           "  -s\tsync files\n";
}

char *cli_get_version() {
    return "stash 0.1.0\n";
}
