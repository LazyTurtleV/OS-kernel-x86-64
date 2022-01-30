#pragma once

#include <stdint.h>
#include <stddef.h>

enum {
    BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	PINK,
	YELLOW,
	WHITE,
};

void print_clear();
void print_str(char *_s);