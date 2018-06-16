/*
 * MIT License
 *
 * Copyright (c) 2018 Kirill Diduk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "control.h"
#include "game.h"
#include "player.h"
#include "textures.h"
#include <SDL2/SDL_rect.h>

static SDL_Rect yak_rect;

int player_load(void)
{
    int w = textures_get_width(TX_YAK_MAIN);
    int h = textures_get_height(TX_YAK_MAIN);

    yak_rect.x = (GAME_RES_X - w) / 2;
    yak_rect.y = (GAME_RES_Y - h) / 2;
    yak_rect.w = w;
    yak_rect.h = h;

    return 0;
}

void player_unload(void)
{
    /* TODO */
}

void player_update(unsigned dt)
{
    const int max_x = (signed)GAME_RES_X - yak_rect.w;
    const int max_y = (signed)GAME_RES_Y - yak_rect.h;

    (void) dt;

    if (control_pressed(CKEY_LEFT) && (yak_rect.x > 0)) {
        yak_rect.x--;
    }

    if (control_pressed(CKEY_RIGHT) && (yak_rect.x < max_x)) {
        yak_rect.x++;
    }

    if (control_pressed(CKEY_UP) && (yak_rect.y > 0)) {
        yak_rect.y--;
    }

    if (control_pressed(CKEY_DOWN) && (yak_rect.y < max_y)) {
        yak_rect.y++;
    }
}

void player_render(SDL_Renderer* rr)
{
    SDL_RenderCopy(rr, textures_get(TX_YAK_MAIN), NULL, &yak_rect);
}

/* EOF */
