#include "cli.h"
#include "dir.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	struct cli cli = {
		.version =  false,
		.help = false,
		.force = false,
	};

	opterr = false;
    int c;
    while ((c = getopt(argc, argv, "hvf")) != -1) {
		switch (c) {
			case 'v':
				cli.version = true;
				break;
			case 'h':
				cli.help = true;
				break;
			case 'f':
				cli.force = true;
				break;
			case '?':
				fprintf(stderr, "unexpected option `%c` in argument `%s`\n", optopt, argv[optind]);
				return 1;
		}
    }

    if (optind < argc) {
		chdir(dir_cfg());
		if (execvp(argv[optind], argv+optind) == -1) {
			fprintf(stderr, "unknown executable: `%s\n", argv[optind]);
		}
        return 1;
    }

	if (cli.version) {
		printf("%s", cli_version());
		return 0;
	} else if (cli.help) {
		printf("%s", cli_help());
		return 0;
	}

    return 0;
}
