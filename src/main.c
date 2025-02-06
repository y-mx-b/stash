#include <stdio.h>
#include "cli.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("%s", cli_help());
        return 0;
    }

    switch (cli_parse_cmd(argv[1])) {
        case CMD_INIT:
            cmd_init();
            break;

        case CMD_CLEAR:
			cmd_clear();
            break;

        case CMD_UNKNOWN:
            printf("unknown\n");
            break;

        case CMD_HELP:
            printf("%s", cli_help());
            break;
    }

    return 0;
}
