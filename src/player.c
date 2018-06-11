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
#include <SDL2/SDL_image.h>

static SDL_Texture* yak_texture = NULL;
static SDL_Rect     yak_rect;

int player_load(SDL_Renderer* rr)
{
    SDL_Surface* surface = NULL;

    surface = IMG_Load("../data/yak_main.png");
    if (!surface) {
        printf("Fatal: failed to load image. `%s`\n", IMG_GetError());
        return (-1);
    }

    yak_texture = SDL_CreateTextureFromSurface(rr, surface);
    if (!yak_texture) {
        SDL_FreeSurface(surface);
        printf("Fatal: failed to create texture from surface. `%s`\n", SDL_GetError());
        return (-1);
    }

    yak_rect.x = (GAME_RES_X - surface->w) / 2;
    yak_rect.y = (GAME_RES_Y - surface->h) / 2;
    yak_rect.w = surface->w;
    yak_rect.h = surface->h;

    SDL_FreeSurface(surface);

    return 0;
}

void player_unload(void)
{
    if (yak_texture) {
        SDL_DestroyTexture(yak_texture);
        yak_texture = NULL;
    }
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
    SDL_RenderCopy(rr, yak_texture, NULL, &yak_rect);
}

/* EOF */
