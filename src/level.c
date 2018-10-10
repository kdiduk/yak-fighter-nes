/* ****************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2018 Kirill Diduk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * ************************************************************************* */

#include "level.h"
#include "neslib.h"
#include "system.h"
#include <stdint.h>

/* ************************************************************************* */

#define MAX_SCROLL_X (256)
#define MAX_SCROLL_Y (240)
#define NAMETABLE_SIZE (960)
#define NAMETABLE_ROW_SIZE (64)
#define ATTRTABLE_SIZE (64)

/* ************************************************************************* */

static const uint8_t bg_palette[] = {
    0x02, 0x12, 0x22, 0x32,
    0x00, 0x10, 0x20, 0x30,
    0x03, 0x13, 0x23, 0x33,
    0x07, 0x17, 0x27, 0x37
};

const uint8_t nametable_row[NAMETABLE_ROW_SIZE] = {
    0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
    0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,

    0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,
    0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11
};

const uint8_t attribute_table[ATTRTABLE_SIZE] = { 0x00 };

/* ************************************************************************** */

static uint16_t scroll_x;
static uint16_t scroll_y;
static uint8_t i;
static uint16_t ptr;

/* ************************************************************************** */

void fastcall level_load(void)
{
    pal_bg(bg_palette);

    bank_bg(1);
    ptr = NAMETABLE_A;
    for (i = 0; i < NAMETABLE_SIZE / NAMETABLE_ROW_SIZE; ++i)
    {
        vram_adr(ptr);
        vram_write(nametable_row, NAMETABLE_ROW_SIZE);
        ptr += NAMETABLE_ROW_SIZE;
    }
    vram_adr(NAMETABLE_A + NAMETABLE_SIZE);
    vram_write(attribute_table, ATTRTABLE_SIZE);

    ptr = NAMETABLE_C;
    for (i = 0; i < NAMETABLE_SIZE / NAMETABLE_ROW_SIZE; ++i)
    {
        vram_adr(ptr);
        vram_write(nametable_row, NAMETABLE_ROW_SIZE);
        ptr += NAMETABLE_ROW_SIZE;
    }
    vram_adr(NAMETABLE_C + NAMETABLE_SIZE);
    vram_write(attribute_table, ATTRTABLE_SIZE);

    scroll_x = 0;
    scroll_y = (2 * MAX_SCROLL_Y) - 1;
}


void fastcall level_update(uint8_t frames)
{
    if (frames % 2)
    {
        if (scroll_y > 0)
        {
            scroll_y--;
        }
        else
        {
            scroll_y = (2 * MAX_SCROLL_Y) - 1;
        }
    }

    if (frames % 25 == 0)
    {
        ++scroll_x;
        if (scroll_x >= 2 * MAX_SCROLL_X)
        {
            scroll_x = 0;
        }
    }

    scroll(scroll_x, scroll_y);
}

void fastcall level_render(void)
{
}

/* eof */
