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

#include "sprite.h"
#include "textures.h"

void sprite_init(struct sprite* spr,
                 enum sprite_type type,
                 enum texture_id tx_id,
                 const SDL_Rect* src_rect,
                 const SDL_Rect* dst_rect)
{
    spr->type = type;
    spr->tx_id = tx_id;

    if (src_rect) {
        spr->src_rect = *src_rect;
    } else {
        spr->src_rect.x = 0;
        spr->src_rect.y = 0;
        spr->src_rect.w = textures_get_width(tx_id);
        spr->src_rect.h = textures_get_height(tx_id);
    }

    if (dst_rect) {
        spr->dst_rect = *dst_rect;
    } else {
        spr->dst_rect.x = 0;
        spr->dst_rect.y = 0;
        spr->dst_rect.w = textures_get_width(tx_id);
        spr->dst_rect.h = textures_get_height(tx_id);
    }
}

/* EOF */
