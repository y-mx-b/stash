#include "cmd.h"
#include <stdio.h>
#include "dir.h"
#include <unistd.h>
#include <sys/stat.h>

void cmd_init() {
    printf("%s\n", dir_cfg());
    mkdir(dir_cfg(), 0755);
}

void cmd_clear() {
	printf("clear: %s\n", dir_cfg());
    rmdir(dir_cfg());
}
