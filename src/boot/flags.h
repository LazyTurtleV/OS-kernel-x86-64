#pragma once 

typedef enum ACCESS_BYTE_FIELDS {
    /*the flag must be set in 1 for any valid segment*/
    PRESENT_B = 1 << 7,
    /*CPU priv lvl of the segment: 0 - the lowest (user apps); 3 - the highest (kernel)*/
    PRIV_LVL = 3 << 5,
    /*being set in 0 means the descriptor describes a system segment, 1 - a code or data*/ 
    D_TYPE_B = 1 << 4,
    /*the flag determines if a segment is executable: 0 - data, 1 - code*/
    EX_B = 1 << 3,
    /*for data selectors: 0 - a segment grows up, 1 - grows down
    code selectors: 1 - allows code be executed with equal or lower priv lvl*/
    DC_B = 1 << 2,
    /*for code seg.: 0 - read access forbidden, 1 - allowed (write access is never allowed)
    for data seg.: 0 - write access forbidden, 1 - allowed (read access is never allowed)*/
    RW_B = 1 << 1,
    /*shouldn't be used - the lowest bit is system-used and normally is set by it*/
    AC_B = 1
} ACCESS_BYTE_FIELDS;

typedef enum GRANULARITY_FLAGS {
    /*the flag indicates the size the limit is scaled by:
    0 - the limit in 1 Byte blocks;
    1 - in 1 KB*/
    GRAN_F = 1 << 3,
    /*if the flag set in 0, the descriptor defines a 16-bit protected mode seg.,
    1 - a 32-bit*/
    SIZE_F = 1 << 2,
    /*if set, the descriptor defines a 64-bit code seg., G_SIZE_F in this case should be cleared.
    for any other segments except of code it should be set in 0*/
    LMODE_F = 1 << 1
} GRANULARITY_FLAGS;