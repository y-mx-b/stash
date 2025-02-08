#include "dir.h"
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *dir_home() {
    // TODO: check HOME first
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
}

char *_CFG_DIR = NULL;

char *dir_cfg() {
    if (_CFG_DIR == NULL) {
        const char   *h  = dir_home();
        unsigned long hl = strlen(h);

        _CFG_DIR = malloc(hl + 6);
        strncpy(_CFG_DIR, h, hl);
        strncpy(_CFG_DIR + hl, "/.dotcfg", 8);
    }
    return _CFG_DIR;
}

int _CFG_DIR_LEN = 0;

char dir_cfg_len() {
	if (_CFG_DIR_LEN == 0) {
		_CFG_DIR_LEN = strlen(dir_cfg());
	}

	return _CFG_DIR_LEN;
}
