#ifndef __DOTCFG_LOG_H__
#define __DOTCFG_LOG_H__

#define err(...) fprintf(stderr, __VA_ARGS__)
#define log(COND, ...) do { if ((COND)) { fprintf(stderr, __VA_ARGS__); } } while (0)

#endif
