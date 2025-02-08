#ifndef __STASH_LOG_H__
#define __STASH_LOG_H__

/// Flag to store whether verbose logging is enabled.
extern int verbose;
void       enable_log();
/// Log a formatted message to `stderr`.
#define log(...)                                       \
    do {                                               \
        if (verbose) { fprintf(stderr, __VA_ARGS__); } \
    } while (0)
/// Write a formatted error message to `stderr`.
#define err(...) fprintf(stderr, __VA_ARGS__)

#endif
