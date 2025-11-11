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
        int pid;              // プロセスID
        int state;            // プロセスの状態: PROC_UNUSED または PROC_RUNNABLE
        vaddr_t sp;           // コンテキストスイッチ時のスタックポインタ
        uint32_t *page_table; // プロセスのページテーブルの物理アドレス
        uint8_t stack[8192];  // カーネルスタック
    };

#define SATP_SV32 (1u << 31)
#define PAGE_V (1 << 0) // 有効化ビット
#define PAGE_R (1 << 1) // 読み込み可能
#define PAGE_W (1 << 2) // 書き込み可能
#define PAGE_X (1 << 3) // 実行可能
#define PAGE_U (1 << 4) // ユーザーモードでアクセス可能

#define USER_BASE 0x1000000
#define SSTATUS_SPIE (1 << 5)

#define SCAUSE_ECALL 8
#define PROC_EXITED 2

#ifdef __cplusplus
}
#endif