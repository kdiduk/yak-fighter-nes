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
#include <stdint.h>


//general purpose vars
static uint8_t i,j;
static uint8_t spr;

// total number of balls on the screen
// since there are 64 HW sprites, it is absolute max
#define BALLS_MAX   (64)

// balls parameters
static uint8_t ball_x[BALLS_MAX];
static uint8_t ball_y[BALLS_MAX];
static uint8_t ball_dx[BALLS_MAX];
static uint8_t ball_dy[BALLS_MAX];


// palette for balls, there are four sets for different ball colors
const uint8_t sp_palette[16]={
    0x0f,0x17,0x27,0x37,
    0x0f,0x11,0x21,0x31,
    0x0f,0x15,0x25,0x35,
    0x0f,0x19,0x29,0x39
};

void main(void)
{
    ppu_off();
    level_load();
    pal_spr(sp_palette);
    ppu_on_all(); //enable rendering

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
    j = 0;
    spr = 0;
    while (1)
    {
        level_update();

        ppu_wait_nmi();
        level_render();

        for (i=0; i<(BALLS_MAX/2); ++i, ++j)
        {
            //set a sprite for current ball
            //0x40 is tile number, i&3 is palette
            spr = oam_spr(ball_x[j], ball_y[j], 0x75, j&3, spr);

            //move the ball
            ball_x[j] += ball_dx[j];
            ball_y[j] += ball_dy[j];

            //bounce the ball off the edges
            if (ball_x[j] >= (256-8))
            {
                ball_dx[j] =- ball_dx[j];
            }

            if (ball_y[j] >= (240-8))
            {
                ball_dy[j] =- ball_dy[j];
            }
        }

        if (j >= BALLS_MAX)
        {
            j = 0;
            spr = 0;
        }
    }
}

/* eof */
