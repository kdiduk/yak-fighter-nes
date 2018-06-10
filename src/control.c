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

static int key_states[MAX_CONTROL_KEY] = { 0 };

void control_update(const SDL_KeyboardEvent* event)
{
    int state = (event->type == SDL_KEYDOWN) ? (1) : (0);

    switch (event->keysym.sym) {
    case SDLK_RETURN:
        key_states[CKEY_RETURN] = state;
        break;
    case SDLK_ESCAPE:
        key_states[CKEY_ESCAPE] = state;
        break;
    case SDLK_SPACE:
        key_states[CKEY_FIRE] = state;
        break;
    case SDLK_LEFT:
        key_states[CKEY_LEFT] = state;
        break;
    case SDLK_RIGHT:
        key_states[CKEY_RIGHT] = state;
        break;
    case SDLK_UP:
        key_states[CKEY_UP] = state;
        break;
    case SDLK_DOWN:
        key_states[CKEY_DOWN] = state;
        break;
    default:
        break;
    }
}

int control_pressed(enum control_key key)
{
    return key_states[key];
}

/* EOF */
