#include "cli.h"
#include "dir.h"
#include "log.h"
#include <errno.h>
#include <ftw.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static bool   cli_force   = false;
static bool   cli_init    = false;
static bool   cli_sync    = false;
static char  *cli_dir     = NULL;
static size_t cli_dir_len = 0;

/// Sync a work directory entry.
///
/// If the current entry is a directory, then `mkdir` will be called. If the current entry is a
/// file, then `symlink` will be called.
int sync_entry(
    const char *path, const struct stat *stat, const int typeflag, struct FTW *pathinfo
) {
    static char new_path[PATH_MAX];
    sprintf(new_path, "%s/%s", dir_home(), path + cli_dir_len + 1);
    switch (typeflag) {
        case FTW_F:
link:
            log("link \"%s\" -> \"%s\": ", new_path, path);
            if (symlink(path, new_path) != 0) {
                // TODO: handle errors
                // TODO: check if files already exist, require force flag to overwrite
                switch (errno) {
                    case EEXIST:
                        log("file already exists\n");
                        if (cli_force) {
                            log("unlinking \"%s\"\n", new_path);
                            unlink(new_path);
                            goto link;
                        }
                        break;
                }
            } else {
                log("success\n");
            }
            break;
        case FTW_D:
            log("create directory \"%s\": ", new_path);
            if (mkdir(new_path, 0755) != 0) {
                // TODO: handle errors
                switch (errno) {
                    case EEXIST:
                        log("directory already exists\n");
                }
            } else {
                log("success\n");
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
    // --- PARSE ARGS ---
    opterr = false;
    // TODO: add clear option to remove symlinks from home directory
    for (int c; (c = getopt(argc, argv, "hvVd:fis")) != -1;) {
        switch (c) {
            case 'v':
                // display version number and exit
                printf("%s", cli_get_version());
                return 0;
            case 'h':
                // display help message and exit
                printf("%s", cli_get_help());
                return 0;
            case 'V':
                enable_log();
                break;
            case 'f':
                cli_force = true;
                break;
            case 'i':
                cli_init = true;
                break;
            case 's':
                cli_sync = true;
                break;
            case 'd':
                // consider using realpath here?
                cli_dir     = optarg;
                cli_dir_len = strlen(optarg);
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

    // init -> cd -> exec

    // --- INIT ---
    // if unset, set default work directory
    if (!cli_dir) {
        cli_dir     = dir_cfg();
        cli_dir_len = strlen(dir_cfg());
    }

    { // log options
        log("current options:\n");
        log("  initialize: %s\n", cli_init ? "true" : "false");
        log("  force: %s\n", cli_force ? "true" : "false");
        log("  sync:%s\n", cli_sync ? "true" : "false");
        log("  work directory: \"%s\"\n", cli_dir);
        log("---\n");
    }

    // initialize work directory
    if (cli_init) {
        log("*initializing work directory*\n");
        if (mkdir(cli_dir, 0755) == -1) {
            if (errno == EEXIST) {
                // check if directory already exists
                struct stat wd_stat;
                stat(cli_dir, &wd_stat);
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
        if (chdir(cli_dir) == -1) {
            err("failed to set work directory: ");
            goto FILE_ERROR;
        }
        log("current work directory: \"%s\"\n", cli_dir);
        log("---\n");
    }

    // --- SYNC ---
    // link work directory contents
    if (cli_sync) {
        log("*sync work directory*\n");
        if (nftw(cli_dir, sync_entry, 15, 0)) {}
        log("---\n");
    }

    // --- EXEC ---
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

    // handle file operation errors from init, set work dir
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
