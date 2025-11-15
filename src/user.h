#pragma once
#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

    __attribute__((noreturn)) void exit(void);
    void putchar(char ch);
    int getchar(void);
    int readfile(const char *filename, char *buf, int len);
    int writefile(const char *filename, const char *buf, int len);

#ifdef __cplusplus
}
#endif