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
#include "textures.h"

void bullet_fire(const SDL_Rect* rect)
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

void bullet_update(struct sprite* spr, unsigned dt)
{
    (void) dt;

    spr->dst_rect.y -= 2;
    if (spr->dst_rect.y < 0) {
        engine_remove_sprite(spr);
    }
}
