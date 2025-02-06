#include "cli.h"
#include <string.h>

char *cli_help() {
    return "Simple dotfile configuration utility.\n"
           "Usage:\n"
           "	<example usage>\n"
           "Options:\n"
           "	<list of options>\n"
           "Commands:\n"
           "	<list of commands>\n";
}

// TODO: change to actually parse arguments instead of just cmd
enum CMD cli_parse_cmd(const char *cmd) {
    if (!strcmp(cmd, "init")) {
        return CMD_INIT;
    } else if (!(strcmp(cmd, "help"))) {
        return CMD_HELP;
	} else if (!(strcmp(cmd, "clear"))) {
		return CMD_CLEAR;
    } else {
        return CMD_UNKNOWN;
    }
}
