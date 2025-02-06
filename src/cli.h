#ifndef __DOTCFG_CLI_H__
#define __DOTCFG_CLI_H__

#include "cmd.h"

char *cli_help();
enum CMD cli_parse_cmd(const char *cmd);

#endif
