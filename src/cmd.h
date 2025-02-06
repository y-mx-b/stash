#ifndef __DOTCFG_CMD_H__
#define __DOTCFG_CMD_H__

enum CMD {
    CMD_INIT,
    CMD_CLEAR,
    CMD_HELP,
    CMD_UNKNOWN,
};

void cmd_init();
void cmd_clear();

#endif
