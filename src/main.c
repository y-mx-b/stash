#include "cli.h"
#include "dir.h"
#include "log.h"
#include <errno.h>
#include <ftw.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static bool cli_force = false;

int link_entry(const char *path, const struct stat *stat, const int typeflag, struct FTW *pathinfo) {
	static char new_path[PATH_MAX];
	sprintf(new_path, "%s/%s", dir_home(), path + dir_cfg_len() + 1);
	switch (typeflag) {
		case FTW_F:
			log("create symlink: \"%s\" -> \"%s\"\n", new_path, path);
			if (symlink(path, new_path) != 0) {
				// TODO: handle errors
				// TODO: check if files already exist, require force flag to overwrite
			}
			break;
		case FTW_D:
			log("create directory: \"%s\"\n", new_path);
			if (mkdir(new_path, 0755) != 0) {
				// TODO: handle errors
			}
			break;
		case FTW_NS:
			err("failed to access path: \"%s\"\n", path);
			break;
		default:
			err("unexpected entry: %s\n", path);
			break;
	}

    return 0;
}

int main(int argc, char **argv) {
    // default options
    struct cli cli = {
        .version = false,
        .help    = false,
        .init    = false,
        .sync    = false,
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
				enable_log();
                break;
            case 'f':
                cli_force = true;
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

    { // log options
        log("current options:\n");
        log("  initialize: %s\n", cli.init ? "true" : "false");
        log("  force: %s\n", cli_force ? "true" : "false");
		log("  sync:%s\n", cli.sync ? "true" : "false");
        log("  work directory: \"%s\"\n", cli.dir);
        log("---\n");
    }

    // initialize work directory
    if (cli.init) {
        log("*initializing work directory*\n");
        if (mkdir(cli.dir, 0755) == -1) {
            if (errno == EEXIST) {
                // check if directory already exists
                struct stat wd_stat;
                stat(cli.dir, &wd_stat);
                if (S_ISDIR(wd_stat.st_mode)) { log("directory already exists\n"); }
            } else {
                // handle other errors
                err("failed to initialize work directory: ");
                goto FILE_ERROR;
            }
        }
        log("---\n");
    }

    { // set work directory
        log("*setting work directory*\n");
        if (chdir(cli.dir) == -1) {
            err("failed to set work directory: ");
            goto FILE_ERROR;
        }
        log("current work directory: \"%s\"\n", cli.dir);
        log("---\n");
    }

    // link work directory contents
	if (cli.sync) {
		log("*sync work directory*\n");
		if (nftw(cli.dir, link_entry, 15, 0)) {}
		log("---\n");
	}

	{ // execute the rest of the arguments as command + args
		log("*passing execution*\n");
		log("---\n");
		if (optind < argc) {
			if (execvp(argv[optind], argv + optind) == -1) {
				err("unknown executable: `%s`\n", argv[optind]);
			}

			return 1;
		}
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
