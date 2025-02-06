#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *help() {
    return "Simple dotfile configuration utility.\n"
           "Usage:\n"
           "	<example usage>\n"
           "Options:\n"
           "	<list of options>\n"
           "Commands:\n"
           "	<list of commands>\n";
}

const char *home_dir() {
    // TODO: check HOME first
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
}

char *_CFG_DIR = NULL;

char *cfg() {
    if (_CFG_DIR == NULL) {
        const char   *h  = home_dir();
        unsigned long hl = strlen(h);

        _CFG_DIR = malloc(hl + 6);
        strncpy(_CFG_DIR, h, hl);
        strncpy(_CFG_DIR + hl, "/.cfg", 6);
    }
    return _CFG_DIR;
}

void init() {
    printf("%s\n", cfg());
    mkdir(cfg(), 0755);
}

enum CMD {
    CMD_INIT,
    CMD_HELP,
    CMD_UNKNOWN,
};

enum CMD parse_cmd(const char *cmd) {
    if (!strcmp(cmd, "init")) {
        return CMD_INIT;
    } else if (!(strcmp(cmd, "help"))) {
        return CMD_HELP;
    } else {
        return CMD_UNKNOWN;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("%s", help());
        return 0;
    }

    switch (parse_cmd(argv[1])) {
        case CMD_INIT:
            printf("init\n");
            init();
            break;
        case CMD_UNKNOWN:
            printf("unknown\n");
            break;
        case CMD_HELP:
            printf("%s", help());
            break;
    }

    return 0;
}
