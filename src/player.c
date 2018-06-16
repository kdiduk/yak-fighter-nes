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
#include "engine.h"
#include "game.h"
#include "player.h"
#include "sprite.h"
#include "textures.h"
#include <SDL2/SDL_rect.h>

#define RELOAD_TIMEOUT (300u)

static int  sprite_index = 0;
static int  reload_time = 0;

static void player_fire(const SDL_Rect* rect);

int player_load(void)
{
    struct sprite spr;

    sprite_init(&spr, SPR_PLAYER, TX_YAK_MAIN, NULL, NULL);

    spr.dst_rect.x = (GAME_RES_X - spr.dst_rect.w) / 2;
    spr.dst_rect.y = (GAME_RES_Y - spr.dst_rect.h) / 2;

    sprite_index = engine_add_sprite(&spr);
    if (sprite_index < 0) {
        printf("Fatal: failed to add player sprite\n");
        return (-1);
    }
    reload_time = 0;

    return 0;
}

void player_unload(void)
{
    engine_remove_sprite_i(sprite_index);
    sprite_index = 0;
}

void player_update(struct sprite* spr, unsigned dt)
{
    SDL_Rect* rect = &(spr->dst_rect);
    const int max_x = (signed)GAME_RES_X - (rect->w);
    const int max_y = (signed)GAME_RES_Y - (rect->h);

    if (reload_time > 0) {
        reload_time -= dt;
    }

    if (reload_time < 0) {
        reload_time = 0;
    }

    if (control_pressed(CKEY_LEFT) && (rect->x > 0)) {
        rect->x--;
    }

    if (control_pressed(CKEY_RIGHT) && (rect->x < max_x)) {
        rect->x++;
    }

    if (control_pressed(CKEY_UP) && (rect->y > 0)) {
        rect->y--;
    }

    if (control_pressed(CKEY_DOWN) && (rect->y < max_y)) {
        rect->y++;
    }

    if (control_pressed(CKEY_FIRE) && !reload_time) {
        player_fire(rect);
        reload_time = RELOAD_TIMEOUT;
    }
}

void player_fire(const SDL_Rect* rect)
{
    struct sprite spr;
    sprite_init(&spr, SPR_BULLET_PLR, TX_BULLET, NULL, NULL);

    spr.dst_rect.x = rect->x;
    spr.dst_rect.y = rect->y;
    engine_add_sprite(&spr);

    spr.dst_rect.x = rect->x + rect->w - spr.dst_rect.w;
    spr.dst_rect.y = rect->y;
    engine_add_sprite(&spr);
}

/* EOF */
