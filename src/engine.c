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

#include "bullet.h"
#include "engine.h"
#include "player.h"
#include <string.h>

#define MAX_SPRITES (500)

struct sprite engine_sprites[MAX_SPRITES];

void engine_init(void)
{
    memset(engine_sprites, 0, MAX_SPRITES * sizeof(struct sprite));
}

void engine_shutdown(void)
{
    memset(engine_sprites, 0, MAX_SPRITES * sizeof(struct sprite));
}

int engine_add_sprite(const struct sprite* spr)
{
    int i = 0;
    for (i = 0; i < MAX_SPRITES; i++) {
        if (engine_sprites[i].type == SPR_NONE) {
            break;
        }
    }

    if (i == MAX_SPRITES) {
        printf("Fatal: maximum sprite number exceeded\n");
        return (-1);
    }

    engine_sprites[i] = *spr;
    return i;
}

void engine_set_sprite(int i, const struct sprite* spr)
{
    engine_sprites[i] = *spr;
}

void engine_remove_sprite(struct sprite* spr)
{
    spr->type = SPR_NONE;
}

void engine_remove_sprite_i(int i)
{
    engine_sprites[i].type = SPR_NONE;
}

void engine_update(unsigned dt)
{
    int i = 0;

    for (i = 0; i < MAX_SPRITES; i++) {
        struct sprite* spr = &(engine_sprites[i]);
        switch (spr->type) {
        case SPR_NONE:
            break;
        case SPR_PLAYER:
            player_update(spr, dt);
            break;
        case SPR_ENEMY:
            break;
        case SPR_BULLET_PLR:
            bullet_update(spr, dt);
            break;
        case SPR_BULLET_ENM:
            break;
        case SPR_POWERUP:
            break;
        }
    }
}

void engine_render(SDL_Renderer* rr)
{
    int i = 0;
    for (i = 0; i < MAX_SPRITES; i++) {
        if (engine_sprites[i].type == SPR_NONE) {
            continue;
        }

        SDL_RenderCopy(
            rr,
            textures_get(engine_sprites[i].tx_id),
            &(engine_sprites[i].src_rect),
            &(engine_sprites[i].dst_rect));
    }
}

/* EOF */
