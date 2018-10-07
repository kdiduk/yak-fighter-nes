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

#include <stdint.h>
#include "neslib.h"
#include "system.h"


//general purpose vars
static uint8_t i,j;
static uint8_t spr;
static uint16_t xscr, yscr;
static uint16_t addr;

// total number of balls on the screen
// since there are 64 HW sprites, it is absolute max
#define BALLS_MAX   (64)

// balls parameters
static uint8_t ball_x[BALLS_MAX];
static uint8_t ball_y[BALLS_MAX];
static uint8_t ball_dx[BALLS_MAX];
static uint8_t ball_dy[BALLS_MAX];

const uint8_t bg_palette[] = {
    0x02, 0x12, 0x22, 0x32,
    0x22, 0x36, 0x17, 0x0F,
    0x22, 0x30, 0x21, 0x0F,
    0x22, 0x27, 0x17, 0x0F
};

// palette for balls, there are four sets for different ball colors
const uint8_t sp_palette[16]={
    0x0f,0x17,0x27,0x37,
    0x0f,0x11,0x21,0x31,
    0x0f,0x15,0x25,0x35,
    0x0f,0x19,0x29,0x39
};


const uint8_t nametable_row[64] = {
    0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
    0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,

    0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,
    0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11,0x10,0x11
};

const uint8_t nametable_attr[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void main(void)
{
    ppu_off();
    pal_bg(bg_palette);
    pal_spr(sp_palette);//set palette for sprites

    bank_bg(1);
    addr = NAMETABLE_A;
    for (i = 0; i < 15; ++i)
    {
        vram_adr(addr);
        vram_write(nametable_row, sizeof(nametable_row));
        addr += sizeof(nametable_row);
    }
    vram_adr(addr);
    vram_write(nametable_attr, 8);

    addr = NAMETABLE_C;
    for (i = 0; i < 15; ++i)
    {
        vram_adr(addr);
        vram_write(nametable_row, sizeof(nametable_row));
        addr += sizeof(nametable_row);
    }
    vram_adr(addr);
    vram_write(nametable_attr, 8);

    ppu_on_all();//enable rendering

    //initialize balls parameters
    for(i=0; i<BALLS_MAX; ++i)
    {
        // starting coordinates
        ball_x[i] = rand8();
        ball_y[i] = rand8();

        //direction bits
        j = rand8();

        //horizontal speed -3..-3, excluding 0
        spr = 1 + (rand8() % 3);
        ball_dx[i] = (j & 1) ? (-spr): (spr);

        //vertical speed
        spr = 1 + (rand8() % 3);
        ball_dy[i] = (j & 2) ? (-spr) : (spr);
    }

    // now the main loop
    yscr = 240;
    xscr = 0;
    while (1)
    {
        j = frame_count();
        if (j % 2)
        {
            --yscr;
            if (yscr == 0)
            {
                yscr = 240;
            }
        }
        if (j % 25 == 0)
        {
            ++xscr;
            if (xscr == 240)
            {
                xscr = 0;
            }
        }

        spr = 0;
        ppu_wait_nmi();
        for (i=0; i<BALLS_MAX; ++i)
        {
            //set a sprite for current ball
            //0x40 is tile number, i&3 is palette
            spr = oam_spr(ball_x[i], ball_y[i], 0x75, i&3, spr);

            //move the ball
            ball_x[i] += ball_dx[i];
            ball_y[i] += ball_dy[i];

            //bounce the ball off the edges
            if (ball_x[i] >= (256-8))
            {
                ball_dx[i] =- ball_dx[i];
            }

            if (ball_y[i] >= (240-8))
            {
                ball_dy[i] =- ball_dy[i];
            }
        }

        scroll(xscr, yscr);
    }
}

/* eof */
