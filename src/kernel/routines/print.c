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

void print_clear()
{   
    video_char c = (video_char) {
        c: ' '
    };

    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        for (size_t i = 0; i < NUM_COLUMNS; i++)
            _buff[_column + NUM_COLUMNS * i] = c;
    }
}

void print_str(char *_s)
{

}