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

#ifndef YF_SPRITE_H
#define YF_SPRITE_H

#include "textures.h"
#include <SDL2/SDL_rect.h>

enum sprite_type {
    SPR_NONE = 0,
    SPR_PLAYER,
    SPR_ENEMY,
    SPR_BULLET_PLR,
    SPR_BULLET_ENM,
    SPR_POWERUP
};

struct sprite {
    enum sprite_type    type;
    enum texture_id     tx_id;
    SDL_Rect            src_rect;
    SDL_Rect            dst_rect;
};

void sprite_init(struct sprite* spr,
                 enum sprite_type type,
                 enum texture_id tx_id,
                 const SDL_Rect* src_rect,
                 const SDL_Rect* dst_rect);

#endif /* YF_SPRITE_H */
