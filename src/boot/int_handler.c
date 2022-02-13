#include "../interface/print.h"

typedef int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;


typedef struct regs 
{
    uint32 ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, int_err;
    uint32 eip, cs, eflags, useresp, ss;
} regs_t;

void int_handler(regs_t regs) 
{
    print_str("Interrupt received");
}