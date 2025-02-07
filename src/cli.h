#ifndef __DOTCFG_CLI_H__
#define __DOTCFG_CLI_H__

#include "cmd.h"
#include <stddef.h>

enum arg_type {
    ARG_OPTION,
    ARG_STOP,
    ARG_VALUE,
};

struct arg {
    enum arg_type type;
    char         *value;
};

struct args {
    size_t      count;
    struct arg *args;
};

char       *cli_help();
enum cmd    cli_parse_cmd(const char *cmd);
struct args cli_lex_args(int argc, char **argv);
struct arg  cli_lex_option(char *opt);

#endif
