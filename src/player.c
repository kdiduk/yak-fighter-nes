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

/**
 * Create on: 13 October, 2018.
 * Barcelona, Spain
 */

#include "neslib.h"
#include "player.h"
#include <stdint.h>


const uint8_t spr_palette_data[]={
    0x0F, 0x0A, 0x1A, 0x0D,
    0x0F, 0x0A, 0x1A, 0x02,
    0x0F, 0x15, 0x25, 0x35,
    0x0f, 0x19, 0x29, 0x39
};


static uint8_t pos_x = 0;
static uint8_t pos_y = 0;

static uint8_t i;
static uint8_t j;
static uint8_t sprite;


void fastcall player_init(void)
{
    pal_spr(spr_palette_data);
    bank_spr(0);
    oam_size(0);
    pos_x = 100;
    pos_y = 100;
}

void fastcall player_update(void)
{

}

void fastcall player_render(void)
{
    sprite = 4;
    for (i = 0; i < 4; ++i)
    {
        for (j = 0; j < 4; ++j)
        {
            sprite = oam_spr(pos_x + (j << 3),
                             pos_y + (i << 3),
                             (i << 4) + j,
                             ((i == 1) && (j == 1 || j == 2)),
                             sprite);
        }
    }
}

/* EOF */
