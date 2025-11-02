#pragma once

#include "common.h"

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

#define PROCS_MAX 8 // 最大プロセス数

#define PROC_UNUSED 0   // 未使用のプロセス管理構造体
#define PROC_RUNNABLE 1 // 実行可能なプロセス

    struct process
    {
        int pid;             // プロセスID
        int state;           // プロセスの状態: PROC_UNUSED または PROC_RUNNABLE
        vaddr_t sp;          // コンテキストスイッチ時のスタックポインタ
        uint8_t stack[8192]; // カーネルスタック
    };

#ifdef __cplusplus
}
#endif