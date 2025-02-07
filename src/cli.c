#include "cli.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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
enum cmd cli_parse_cmd(const char *cmd) {
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

struct arg cli_lex_option(char *opt) {
    int i = 0;
    while (opt[i] == '-') {
        i++;
    }

    if (i == 2 && opt[i] == '\0') {
        // `--`
        return (struct arg) {
            .type  = ARG_STOP,
            .value = opt + i,
        };
    } else {
        // any other option
        return (struct arg) {
            .type  = ARG_OPTION,
            .value = opt + i,
        };
    }
}

struct args cli_lex_args(int argc, char **argv) {
    int         count = argc - 1; // skip first cli arg, just program name
    struct args args  = {
         .count = count,
         .args  = malloc(sizeof(struct arg) * (count)),
    };

    enum arg_type lex_options = ARG_OPTION;
    for (int i = 1; i < argc; i++) {
        if ((argv[i][0] == '-') && (lex_options != ARG_STOP)) {
            args.args[i - 1] = cli_lex_option(argv[i]);
            lex_options      = args.args[i - 1].type;
        } else {
            args.args[i - 1] = (struct arg) {
                .type  = ARG_VALUE,
                .value = argv[i],
            };
        }
    }

    return args;
}
