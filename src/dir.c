#include "dir.h"
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/// Return the user's home directory.
///
/// The user's `pw` struct is checked.
const char *dir_home() {
    // TODO: check HOME first
    struct passwd *pw = getpwuid(getuid());
    return pw->pw_dir;
}

/// Lazy-loaded default work directory.
char *_CFG_DIR = NULL;

/// Return the default `dotconfig` work directory.
char *dir_cfg() {
    if (_CFG_DIR == NULL) {
        const char   *h  = dir_home();
        unsigned long hl = strlen(h);

        _CFG_DIR = malloc(hl + 6);
        strncpy(_CFG_DIR, h, hl);
        strncpy(_CFG_DIR + hl, "/.stash", 8);
    }
    return _CFG_DIR;
}
