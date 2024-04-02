#include <kernel/types.h>

constexpr u32 CF_MASK = 1u << 0;    // Carry Flag
constexpr u32 PF_MASK = 1u << 2;    // Parity Flag
constexpr u32 AF_MASK = 1u << 4;    // Adjust Flag
constexpr u32 ZF_MASK = 1u << 6;    // Zero Flag
constexpr u32 SF_MASK = 1u << 7;    // Sign Flag
constexpr u32 TF_MASK = 1u << 8;    // Trap Flag
constexpr u32 IF_MASK = 1u << 9;    // Interrupt Enable Flag
constexpr u32 DF_MASK = 1u << 10;   // Direction Flag
constexpr u32 OF_MASK = 1u << 11;   // Overflow Flag
constexpr u32 IOPL_MASK = 3u << 12; // I/O Privilege Level (two bits)
constexpr u32 NT_MASK = 1u << 14;   // Nested Task Flag
constexpr u32 RF_MASK = 1u << 16;   // Resume Flag
constexpr u32 VM_MASK = 1u << 17;   // Virtual-8086 Mode Flag
constexpr u32 AC_MASK = 1u << 18;   // Alignment Check
constexpr u32 VIF_MASK = 1u << 19;  // Virtual Interrupt Flag
constexpr u32 VIP_MASK = 1u << 20;  // Virtual Interrupt Pending
constexpr u32 ID_MASK = 1u << 21;   // ID Flag

bool check_eflags(u32 mask);
