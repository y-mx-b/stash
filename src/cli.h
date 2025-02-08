#ifndef __DOTCFG_CLI_H__
#define __DOTCFG_CLI_H__

#include <stdbool.h>

struct cli {
    bool version;
    bool help;

    bool force;
};

char *cli_help();
char *cli_version();

#endif
