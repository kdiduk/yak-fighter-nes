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

#include "game.h"
#include "level.h"
#include "textures.h"
#include <SDL2/SDL_rect.h>

#define SCROLL_TIMEOUT (40u)

static SDL_Rect camera_rect;
static unsigned scroll_elapsed_ms = 0;

int level_load(void)
{
    camera_rect.x = 0;
    camera_rect.y = textures_get_height(TX_LEVEL_01) - GAME_RES_Y;
    camera_rect.w = GAME_RES_X;
    camera_rect.h = GAME_RES_Y;

    scroll_elapsed_ms = 0;

    return 0;
}

void level_unload(void)
{
    /* TODO */
}

void level_update(unsigned dt)
{
    scroll_elapsed_ms += dt;
    if (scroll_elapsed_ms >= SCROLL_TIMEOUT) {
        scroll_elapsed_ms = 0;
        camera_rect.y--;
    }

    if (camera_rect.y < 0) {
        game_quit();
    }
}

void level_render(SDL_Renderer* rr)
{
    SDL_RenderCopy(rr, textures_get(TX_LEVEL_01), &camera_rect, NULL);
}

/* EOF */
