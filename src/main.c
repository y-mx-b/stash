#include "cli.h"
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("%s", cli_help());
        return 0;
    }

    struct args args = cli_lex_args(argc, argv);
    for (size_t i = 0; i < args.count; i++) {
        printf("%d: %s\n", args.args[i].type, args.args[i].value);
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
