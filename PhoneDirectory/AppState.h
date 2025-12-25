#pragma once
#ifndef APP_STATE_H
#define APP_STATE_H

typedef enum
{
    STATE_WAIT_START,
    STATE_MAIN_MENU,
    STATE_LIST,
    STATE_ADD,
    STATE_DELETE,
    STATE_UPDATE,
    STATE_EXIT
} AppState;

#endif
