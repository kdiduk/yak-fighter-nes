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

#include "textures.h"
#include <SDL2/SDL_image.h>

static SDL_Texture* texture_objects[MAX_TEXTURE_ID] = { NULL };
static int          texture_widths[MAX_TEXTURE_ID] = { 0 };
static int          texture_heights[MAX_TEXTURE_ID] = { 0 };
static const char*  texture_files[MAX_TEXTURE_ID] = { "../data/yak_main.png",
                                                      "../data/bullet.png",
                                                      "../data/level_01.png"
                                                    };

int textures_load(SDL_Renderer* rr)
{
    int i = 0;

    for (i = 0; i < MAX_TEXTURE_ID; i++) {
        SDL_Surface* srfc = IMG_Load(texture_files[i]);
        if (!srfc) {
            printf("Fatal: failed to load image '%s'\n", texture_files[i]);
            printf("     > %s\n", IMG_GetError());
            return (-1);
        }

        texture_objects[i] = SDL_CreateTextureFromSurface(rr, srfc);
        if (!texture_objects[i]) {
            SDL_FreeSurface(srfc);
            printf("Fatal: failed to create texture '%s'\n", texture_files[i]);
            printf("     > %s\n", IMG_GetError());
            return (-1);
        }

        texture_widths[i] = srfc->w;
        texture_heights[i] = srfc->h;

        SDL_FreeSurface(srfc);
    }

    return 0;
}

void textures_unload(void)
{
    int i = 0;
    for (i = 0; i < MAX_TEXTURE_ID; i++) {
        SDL_DestroyTexture(texture_objects[i]);
        texture_objects[i] = NULL;
    }
}

SDL_Texture* textures_get(enum texture_id txid)
{
    return texture_objects[txid];
}

int textures_get_width(enum texture_id txid)
{
    return texture_widths[txid];
}

int textures_get_height(enum texture_id txid)
{
    return texture_heights[txid];
}

/* EOF */
