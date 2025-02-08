#include "cli.h"

char *cli_help() {
    return "Simple dotfile configuration utility.\n"
           "Usage:\n"
           "	dotcfg [-fiV] [-d WORK_PATH] [<COMMAND> <ARGS...>]\n"
           "Options:\n"
           "  -h\tdisplay this help message\n"
           "  -v\tdisplay version number\n"
           "  -V\tdisplay verbose logging\n"
           "  -d\tprovide a work directory\n"
           "\t  (default: \"~/.dotcfg\")\n"
           "  -f\toverwrite existing files\n"
           "  -i\tinitialize work directory\n"
		   "  -s\tsync files";
}

char *cli_version() {
    return "dotcfg 0.1.0\n";
}
