#include "./headers/print.h"

const static size_t NUM_COLUMNS = 80;
const static size_t NUM_ROWS = 25;

typedef struct video_char {
    uint8_t c,
    uint8_t color
} video_char;

video_char* _buff = (video_char*) 0xb8000;
size_t _column = 0;
size_t _row = 0;

void _print_char();
void _print_newline();
void _clear_row();

void print_clear()
{   
    for (size_t i = 0; i < NUM_ROWS; i++)
        _clear_row(i);
}

void print_str(char *_s)
{
    for(char *ptr = _s; *ptr != '\0'; ptr++)
        _print_char(*ptr);
}

void _clear_row(size_t _i)
{
    video_char c = (video_char) {
        c: ' '
    };

    for (size_t j = 0; j < NUM_COLUMNS; j++)
        _buff[_i + NUM_COLUMNS * j] = c;
}

void _print_newline()
{
    _column = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        for (size_t i = 0; i < NUM_COLUMNS; i++)
        {
            video_char c = _buff[_column + NUM_COLUMNS * i];
            _buff[_column + NUM_COLUMNS * (i - 1)] = c;
        }
    }

    _clear_row(NUM_ROWS - 1);
}

void _print_char(char _c)
{    
    if (_c == '\n')
    {
        _print_newline();
        return;
    }

    if (_column > NUM_COLUMNS)
        _print_newline();

    _buff[_column + NUM_COLUMNS * _row] = (video_char){
        c: (uint8_t)_c,
    }

    _column++;
}
