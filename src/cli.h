#ifndef __DOTCFG_CLI_H__
#define __DOTCFG_CLI_H__

#include <stdbool.h>

struct cli {
    bool version;
    bool help;

	bool verbose;
    bool force;
	bool init;
	bool sync;
	char *dir;
};

char *cli_help();
char *cli_version();

#endif
