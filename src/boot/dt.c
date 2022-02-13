
#include "./flags.h"

typedef int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

extern void gdt_flush(uint32);

void gdt_init();

typedef struct 
{
    uint16 lim_l;
    uint16 base_l;
    uint8 base_m;
    uint8 access_fl;
    uint8 granularity;
    uint8 base_h;
} __attribute__((packed)) gdt_entry_t;

typedef struct 
{
    uint16 limit;
    uint32 base;
} __attribute__((packed)) gdt_ptr_t;

gdt_entry_t _gdt_entries[5];
gdt_ptr_t _gdt_ptr;

void init_dt() {
    gdt_init();
}

void gdt_init() 
{
    _gdt_ptr.limit = sizeof(gdt_entry_t)*5 - 1;
    _gdt_ptr.base = &_gdt_entries;

    const uint8 gran_f = ( (GRAN_F | SIZE_F) << 3 ) & 0xF;
    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0xFFFFFFFF, PRESENT_B | D_TYPE_B | EX_B | RW_B, gran_f);
    set_gdt_entry(1, 0, 0xFFFFFFFF, PRESENT_B | D_TYPE_B | RW_B, gran_f);
    set_gdt_entry(1, 0, 0xFFFFFFFF, PRESENT_B | PRIV_LVL | D_TYPE_B | EX_B | RW_B , gran_f);
    set_gdt_entry(1, 0, 0xFFFFFFFF, PRESENT_B | PRIV_LVL | D_TYPE_B | RW_B, gran_f);

    gdt_flush(&_gdt_ptr);
}

void set_gdt_entry(int _i, uint32 _lim, uint32 _base, uint8 _access_fl, uint8 _granularity)
{
    _gdt_entries[_i].base_l = _base & 0xFFFF;
    _gdt_entries[_i].base_m = (_base >> 16) & 0xFF;
    _gdt_entries[_i].base_h = (_base >> 24) & 0xFF;

    _gdt_entries[_i].lim_l = _lim & 0xFFFF;
    _gdt_entries[_i].granularity = (_lim >> 16) & 0xFF;

    _gdt_entries[_i].granularity |= _granularity & 0xF0; 
    _gdt_entries[_i].access_fl = _access_fl;
}