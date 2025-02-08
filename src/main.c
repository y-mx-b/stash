#include "cli.h"
#include "dir.h"
#include "log.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {

    // default options
    struct cli cli = {
        .version = false,
        .help    = false,
        .verbose = false,
        .force   = false,
        .init    = false,
		.sync = false,
        .dir     = dir_cfg(),
    };

    // parse args
    opterr = false;
	for (int c; (c = getopt(argc, argv, "hvVd:fis")) != -1;) {
        switch (c) {
            case 'v':
                cli.version = true;
                break;
            case 'h':
                cli.help = true;
                break;
            case 'V':
                cli.verbose = true;
                break;
            case 'f':
                cli.force = true;
                break;
            case 'i':
                cli.init = true;
                break;
			case 's':
				cli.sync = true;
				break;
            case 'd':
                // consider using realpath here?
                cli.dir = optarg;
                break;
            default:
                // if still parsing args, error must be unexpected argument
                if (optind < argc) {
                    err("unexpected option `%c` in `%s`\n", optopt, argv[optind]);
                } else {
                    err("expected argument for option `-d`\n");
                }
                return 1;
                break;
        }
	}

    // priority: version -> help -> init -> cd -> exec

	// display version number
    if (cli.version) {
        printf("%s", cli_version());
        return 0;
    }

	// display help message
	if (cli.help) {
        printf("%s", cli_help());
        return 0;
    }

    // log options
    log(cli.verbose, "current options:\n");
    log(cli.verbose, "  verbose: %s\n", cli.verbose ? "true" : "false");
    log(cli.verbose, "  initialize: %s\n", cli.init ? "true" : "false");
    log(cli.verbose, "  force: %s\n", cli.force ? "true" : "false");
    log(cli.verbose, "  work directory: \"%s\"\n", cli.dir);
	log(cli.verbose, "---\n");

    // initialize work directory
    if (cli.init) {
		log(cli.verbose, "*initializing work directory*\n");
        if (mkdir(cli.dir, 0755) == -1) {
            if (errno == EEXIST) {
                // check if directory already exists
                struct stat wd_stat;
                stat(cli.dir, &wd_stat);
                if (S_ISDIR(wd_stat.st_mode)) {
                    log(cli.verbose, "directory already exists\n");
                }
            } else {
                // handle other errors
                err("failed to initialize work directory: ");
                goto FILE_ERROR;
            }
        }
		log(cli.verbose, "---\n");
    }

    // set work directory
    log(cli.verbose, "*setting work directory*\n");
    if (chdir(cli.dir) == -1) {
        err("failed to set work directory: ");
        goto FILE_ERROR;
    }
    log(cli.verbose, "current work directory: \"%s\"\n", cli.dir);
	log(cli.verbose, "---\n");

	// link work directory contents
	log(cli.verbose, "*sync work directory*\n");
	log(cli.verbose, "**not yet implemented\n");
	log(cli.verbose, "---\n");

    // execute the rest of the arguments as command + args
    log(cli.verbose, "*passing execution*\n");
	log(cli.verbose, "---\n");
    if (optind < argc) {
        if (execvp(argv[optind], argv + optind) == -1) {
            err("unknown executable: `%s`\n", argv[optind]);
        }

        return 1;
    }

    return 0;

FILE_ERROR:
    switch (errno) {
        case EACCES:
            err("permission denied\n");
            break;
        case ENOENT:
            err("path does not exist\n");
            break;
        case EEXIST:
            err("file exists\n");
            break;
        // TODO: add more cases
        default:
            err("?\n");
            break;
    }

    return 1;
}
