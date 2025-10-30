#pragma once

struct sbiret
{
    long error;
    long value;
};

#ifdef __cplusplus
extern "C" {
#endif

void putchar(char ch);

#ifdef __cplusplus
}
#endif