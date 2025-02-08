#ifndef __DOTCFG_LOG_H__
#define __DOTCFG_LOG_H__

extern int verbose;
void enable_log();
#define log(...) do { if (verbose) { fprintf(stderr, __VA_ARGS__); } } while (0)
#define err(...) fprintf(stderr, __VA_ARGS__)

#endif
