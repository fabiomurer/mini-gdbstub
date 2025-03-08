#ifndef GDBSTUB_H
#define GDBSTUB_H

#include <stdbool.h>
#include <stddef.h>

#define TARGET_RV32 \
    "<target version=\"1.0\"><architecture>riscv:rv32</architecture></target>"
#define TARGET_RV64 \
    "<target version=\"1.0\"><architecture>riscv:rv64</architecture></target>"
#define TARGET_X86_64 \
    "<target version=\"1.0\"><architecture>i386:x86-64</architecture></target>"

#define GDB_CPU_X86_64_NUM_AVX_REGISTERS 73
/* Register sizes in bytes for x86_64 architecture including AVX */
static const int x86_64_reg_size[GDB_CPU_X86_64_NUM_AVX_REGISTERS] = {
    8,   /* GDB_CPU_X86_64_REG_RAX     = 0  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RBX     = 1  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RCX     = 2  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RDX     = 3  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RSI     = 4  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RDI     = 5  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RBP     = 6  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RSP     = 7  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R8      = 8  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R9      = 9  - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R10     = 10 - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R11     = 11 - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R12     = 12 - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R13     = 13 - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R14     = 14 - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_R15     = 15 - 64-bit general purpose */
    8,   /* GDB_CPU_X86_64_REG_RIP     = 16 - 64-bit instruction pointer */
    4,   /* GDB_CPU_X86_64_REG_EFLAGS  = 17 - 32-bit flags */
    4,   /* GDB_CPU_X86_64_REG_CS      = 18 - 16-bit segment register (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_SS      = 19 - 16-bit segment register (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_DS      = 20 - 16-bit segment register (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_ES      = 21 - 16-bit segment register (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_FS      = 22 - 16-bit segment register (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_GS      = 23 - 16-bit segment register (padded to 4) */
    
    10,  /* GDB_CPU_X86_64_REG_ST0     = 24 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST1     = 25 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST2     = 26 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST3     = 27 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST4     = 28 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST5     = 29 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST6     = 30 - 80-bit FPU register */
    10,  /* GDB_CPU_X86_64_REG_ST7     = 31 - 80-bit FPU register */
    
    4,   /* GDB_CPU_X86_64_REG_FCTRL   = 32 - 16-bit FPU control word (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_FSTAT   = 33 - 16-bit FPU status word (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_FTAG    = 34 - 8-bit FPU tag word (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_FISEG   = 35 - 16-bit FPU IP selector (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_FIOFF   = 36 - 32-bit FPU IP offset */
    4,   /* GDB_CPU_X86_64_REG_FOSEG   = 37 - 16-bit FPU operand selector (padded to 4) */
    4,   /* GDB_CPU_X86_64_REG_FOOFF   = 38 - 32-bit FPU operand offset */
    4,   /* GDB_CPU_X86_64_REG_FOP     = 39 - 16-bit FPU opcode (padded to 4) */
    
    16,  /* GDB_CPU_X86_64_REG_XMM0    = 40 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM1    = 41 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM2    = 42 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM3    = 43 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM4    = 44 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM5    = 45 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM6    = 46 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM7    = 47 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM8    = 48 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM9    = 49 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM10   = 50 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM11   = 51 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM12   = 52 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM13   = 53 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM14   = 54 - 128-bit SSE register */
    16,  /* GDB_CPU_X86_64_REG_XMM15   = 55 - 128-bit SSE register */
    
    4,   /* GDB_CPU_X86_64_REG_MXCSR   = 56 - 32-bit SSE control/status register */
    
    /* AVX YMM registers upper halves (128-bit each) */
    16,  /* GDB_CPU_X86_64_REG_YMM0H   = 57 - 128-bit upper half of YMM0 */
    16,  /* GDB_CPU_X86_64_REG_YMM1H   = 58 - 128-bit upper half of YMM1 */
    16,  /* GDB_CPU_X86_64_REG_YMM2H   = 59 - 128-bit upper half of YMM2 */
    16,  /* GDB_CPU_X86_64_REG_YMM3H   = 60 - 128-bit upper half of YMM3 */
    16,  /* GDB_CPU_X86_64_REG_YMM4H   = 61 - 128-bit upper half of YMM4 */
    16,  /* GDB_CPU_X86_64_REG_YMM5H   = 62 - 128-bit upper half of YMM5 */
    16,  /* GDB_CPU_X86_64_REG_YMM6H   = 63 - 128-bit upper half of YMM6 */
    16,  /* GDB_CPU_X86_64_REG_YMM7H   = 64 - 128-bit upper half of YMM7 */
    16,  /* GDB_CPU_X86_64_REG_YMM8H   = 65 - 128-bit upper half of YMM8 */
    16,  /* GDB_CPU_X86_64_REG_YMM9H   = 66 - 128-bit upper half of YMM9 */
    16,  /* GDB_CPU_X86_64_REG_YMM10H  = 67 - 128-bit upper half of YMM10 */
    16,  /* GDB_CPU_X86_64_REG_YMM11H  = 68 - 128-bit upper half of YMM11 */
    16,  /* GDB_CPU_X86_64_REG_YMM12H  = 69 - 128-bit upper half of YMM12 */
    16,  /* GDB_CPU_X86_64_REG_YMM13H  = 70 - 128-bit upper half of YMM13 */
    16,  /* GDB_CPU_X86_64_REG_YMM14H  = 71 - 128-bit upper half of YMM14 */
    16   /* GDB_CPU_X86_64_REG_YMM15H  = 72 - 128-bit upper half of YMM15 */
};

typedef enum {
    EVENT_NONE,
    EVENT_CONT,
    EVENT_DETACH,
    EVENT_STEP,
} gdb_event_t;

typedef enum {
    ACT_NONE,
    ACT_RESUME,
    ACT_SHUTDOWN,
} gdb_action_t;

typedef enum {
    BP_SOFTWARE = 0,
} bp_type_t;

struct target_ops {
    gdb_action_t (*cont)(void *args);
    gdb_action_t (*stepi)(void *args);
    int (*read_reg)(void *args, int regno, void* value);
    int (*write_reg)(void *args, int regno, void* value);
    int (*read_mem)(void *args, size_t addr, size_t len, void *val);
    int (*write_mem)(void *args, size_t addr, size_t len, void *val);
    bool (*set_bp)(void *args, size_t addr, bp_type_t type);
    bool (*del_bp)(void *args, size_t addr, bp_type_t type);
    void (*on_interrupt)(void *args);

    void (*set_cpu)(void *args, int cpuid);
    int (*get_cpu)(void *args);
};

typedef struct gdbstub_private gdbstub_private_t;

typedef struct {
    char *target_desc;
    int smp;
    int reg_num;
    size_t reg_byte;
    size_t* regs_byte;
} arch_info_t;

typedef struct {
    struct target_ops *ops;
    arch_info_t arch;
    gdbstub_private_t *priv;
} gdbstub_t;

bool gdbstub_init(gdbstub_t *gdbstub,
                  struct target_ops *ops,
                  arch_info_t arch,
                  char *s);
bool gdbstub_run(gdbstub_t *gdbstub, void *args);
void gdbstub_close(gdbstub_t *gdbstub);

#endif
