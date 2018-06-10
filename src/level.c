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
#include <SDL2/SDL_image.h>

#define SCROLL_TIMEOUT (40u)

static SDL_Texture* bg_texture = NULL;
static SDL_Rect camera_rect;
static unsigned scroll_elapsed_ms = 0;

int level_load(SDL_Renderer* renderer)
{
    SDL_Surface* surface = NULL;

    surface = IMG_Load("../data/level_01.png");
    if (!surface) {
        printf("Fatal: failed to load image. `%s`\n", IMG_GetError());
        return (-1);
    }

    bg_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!bg_texture) {
        SDL_FreeSurface(surface);
        printf("Fatal: failed to create texture from surface. `%s`\n",
               SDL_GetError());
        return (-1);
    }

    camera_rect.x = 0;
    camera_rect.y = surface->h - GAME_RESOLUTION_Y;
    camera_rect.w = GAME_RESOLUTION_X;
    camera_rect.h = GAME_RESOLUTION_Y;

    SDL_FreeSurface(surface);

    scroll_elapsed_ms = 0;

    return 0;
}

void level_update(unsigned elapsed)
{
    scroll_elapsed_ms += elapsed;
    if (scroll_elapsed_ms >= SCROLL_TIMEOUT) {
        scroll_elapsed_ms = 0;
        camera_rect.y--;
    }

    if (camera_rect.y < 0) {
        game_quit();
    }
}

void level_render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, bg_texture, &camera_rect, NULL);
}

void level_unload(void)
{
    if (bg_texture) {
        SDL_DestroyTexture(bg_texture);
        bg_texture = NULL;
    }
}

/* EOF */
