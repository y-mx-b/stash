#include "cmd.h"
#include "dir.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void cmd_init() {
    printf("%s\n", dir_cfg());
    mkdir(dir_cfg(), 0755);
}

void cmd_clear() {
    printf("clear: %s\n", dir_cfg());
    rmdir(dir_cfg());
}
