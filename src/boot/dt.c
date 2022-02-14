
#include "./flags.h"

typedef int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

extern void gdt_flush(uint32);
extern void idt_flush(uint32);

void gdt_init();
void idt_init();

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

void set_gdt_entry(int _i, uint32 _lim, uint32 _base, uint8 _access_fl, uint8 _granularity);

void init_dt() {
    gdt_init();
    idt_init();
}

void gdt_init() 
{
    _gdt_ptr.limit = sizeof(gdt_entry_t)*5 - 1;
    _gdt_ptr.base = &_gdt_entries;

    const uint8 gran_f = ( (GRAN_F | SIZE_F) << 3 ) & 0xFF;
    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0xFFFFFFFF, PRESENT_B | D_TYPE_B | EX_B | RW_B, gran_f);
    set_gdt_entry(2, 0, 0xFFFFFFFF, PRESENT_B | D_TYPE_B | RW_B, gran_f);
    set_gdt_entry(3, 0, 0xFFFFFFFF, PRESENT_B | PRIV_LVL | D_TYPE_B | EX_B | RW_B , gran_f);
    set_gdt_entry(4, 0, 0xFFFFFFFF, PRESENT_B | PRIV_LVL | D_TYPE_B | RW_B, gran_f);

    gdt_flush(&_gdt_ptr);
}

void set_gdt_entry(int _i, uint32 _lim, uint32 _base, uint8 _access_fl, uint8 _granularity)
{
    _gdt_entries[_i].base_l = _base & 0xFFFF;
    _gdt_entries[_i].base_m = (_base >> 16) & 0xFF;
    _gdt_entries[_i].base_h = (_base >> 24) & 0xFF;

    _gdt_entries[_i].lim_l = _lim & 0xFFFF;
    _gdt_entries[_i].granularity = (_lim >> 16) & 0x0F;

    _gdt_entries[_i].granularity |= _granularity & 0xF0; 
    _gdt_entries[_i].access_fl = _access_fl;
}

typedef struct 
{
    uint16 base_l;
    uint16 code_selector;
    uint8 reserved;
    uint8 flags;
    uint16 base_h;
} __attribute__((packed)) idt_entry_t;

typedef struct 
{
    uint16 limit;
    uint32 base;
} __attribute__((packed)) idt_ptr_t;

idt_entry_t _idt_entries[256];
idt_ptr_t _idt_ptr;

//interrupt handlers
extern void i0h();
extern void i1h();
extern void i2h();
extern void i3h();
extern void i4h();
extern void i5h();
extern void i6h();
extern void i7h();
extern void i8h();
extern void i9h();
extern void i10h();
extern void i11h();
extern void i12h();
extern void i13h();
extern void i14h();
extern void i15h();
extern void i16h();
extern void i17h();
extern void i18h();
extern void i19h();
extern void i20h();
extern void i21h();
extern void i22h();
extern void i23h();
extern void i24h();
extern void i25h();
extern void i26h();
extern void i27h();
extern void i28h();
extern void i29h();
extern void i30h();
extern void i31h();

void set_idt_entry(uint8 _i, uint32 _base, uint16 _code_selector, uint8 _fl);

void idt_init() 
{
    _idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    _idt_ptr.base = &_idt_entries;

    set_idt_entry( 0,   i0h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 1,   i1h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 2,   i2h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 3,   i3h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 4,   i4h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 5,   i5h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 6,   i6h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 7,   i7h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 8,   i8h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 9,   i9h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 10, i10h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 11, i11h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 12, i12h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 13, i13h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 14, i14h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 15, i15h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 16, i16h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 17, i17h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 18, i18h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 19, i19h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 20, i20h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 21, i21h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 22, i22h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 23, i23h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 24, i24h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 25, i25h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 26, i26h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 27, i27h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 28, i28h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 29, i29h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 30, i30h, 0x08, I_PRESENT_B | GT_32INT_G );
    set_idt_entry( 31, i31h, 0x08, I_PRESENT_B | GT_32INT_G );

    idt_flush(&_idt_entries);
}

void set_idt_entry(uint8 _i, uint32 _base, uint16 _code_selector, uint8 _fl) 
{
    _idt_entries[_i].base_l = _base & 0xFFFF;
    _idt_entries[_i].base_h = ( _base >> 16 ) & 0xFFFF;
    _idt_entries[_i].code_selector = _code_selector;
    _idt_entries[_i].reserved = 0;
    _idt_entries[_i].flags = _fl;
}