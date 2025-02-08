#include "cli.h"

char *cli_help() {
    return "Simple dotfile configuration utility.\n"
           "Usage:\n"
           "	<example usage>\n"
           "Options:\n"
           "	<list of options>\n"
           "Commands:\n"
           "	<list of commands>\n";
}

char *cli_version() {
	return "dotcfg 0.1.0\n";
}
