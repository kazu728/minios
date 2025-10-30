#pragma once

struct sbiret
{
    long error;
    long value;
};

#ifdef __cplusplus
extern "C"
{
#endif

    void putchar(char ch);

#define PANIC(fmt, ...)                                                       \
    do                                                                        \
    {                                                                         \
        printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
        while (1)                                                             \
        {                                                                     \
        }                                                                     \
    } while (0)

#ifdef __cplusplus
}
#endif