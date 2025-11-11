#pragma once
#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

    __attribute__((noreturn)) void exit(void);
    void putchar(char ch);
    int getchar(void);

#ifdef __cplusplus
}
#endif