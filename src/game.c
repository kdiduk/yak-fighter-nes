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
#include "level.h"
#include "player.h"
#include "textures.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stddef.h>
#include <stdio.h>

#define TICKS_PER_FRAME     (20u)
#define WAIT_EVENT_TIMEOUT  (1000u)
#define WINDOW_FLAGS        (0)
#define RENDERER_FLAGS      (SDL_RENDERER_SOFTWARE)
#define WINDOW_WIDTH        (3u * GAME_RES_X)
#define WINDOW_HEIGHT       (3u * GAME_RES_Y)

static int              is_running_flag     = 0;
static SDL_TimerID      tick_timer_id       = 0;
static unsigned         last_update_ticks   = 0;
static SDL_Window*      main_window         = NULL;
static SDL_Renderer*    main_renderer       = NULL;

static void     update(void);
static void     render(void);
static int      is_running(void);
static Uint32   tick_timer_callback(Uint32 interval, void* param);

int game_init(int argc, char** argv)
{
    int error = 0;
    int img_status = 0;
    (void)argc, (void)argv; /* unused parameters */

    error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    if (error) {
        printf("Fatal: Unable to init SDL. `%s`\n", SDL_GetError());
        return error;
    }

    img_status = IMG_Init(IMG_INIT_PNG);
    if ((img_status&IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf("Fatal: Unable to init SDL Image. `%s`\n", IMG_GetError());
        return (-1);
    }

    main_window = SDL_CreateWindow("Yak Fighter!",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   WINDOW_WIDTH,
                                   WINDOW_HEIGHT,
                                   WINDOW_FLAGS);
    if (!main_window) {
        printf("Fatal: Unable to create main window. `%s`\n", SDL_GetError());
        return (-1);
    }

    main_renderer = SDL_CreateRenderer(main_window, -1, RENDERER_FLAGS);
    if (!main_renderer) {
        printf("Fatal: Unable to create main renderer. `%s`\n", SDL_GetError());
        return (-1);
    }

    error = SDL_RenderSetLogicalSize(main_renderer, GAME_RES_X, GAME_RES_Y);
    if (error) {
        printf("Error: SDL_RenderSetLogicalSize(): `%s`\n", SDL_GetError());
        return error;
    }

    if (SDL_ShowCursor(SDL_DISABLE) < 0) {
        printf("Warning: failed to hide the cursor\n");
    }

    error = SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
    if (error) {
        printf("Fatal: failed to set render draw color. `%s`'n", SDL_GetError());
        return error;
    }

    error = textures_load(main_renderer);
    if (error) {
        printf("Fatal: failed to load textures\n");
        return error;
    }

    error = level_load();
    if (error) {
        printf("Fatal: failed to load game level\n");
        return error;
    }

    error = player_load();
    if (error) {
        printf("Fatal: failed to load the player\n");
        return error;
    }

    tick_timer_id = SDL_AddTimer(TICKS_PER_FRAME, tick_timer_callback, NULL);
    if (tick_timer_id == 0) {
        printf("Fatal: SDL_AddTimer() failed. `%s`\n", SDL_GetError());
        return (-1);
    }

    return 0;
}

void game_shutdown(void)
{
    if (tick_timer_id) {
        SDL_RemoveTimer(tick_timer_id);
        tick_timer_id = 0;
    }

    player_unload();
    level_unload();
    textures_unload();

    if (main_renderer) {
        SDL_DestroyRenderer(main_renderer);
        main_renderer = NULL;
    }

    if (main_window) {
        SDL_DestroyWindow(main_window);
        main_window = NULL;
    }

    IMG_Quit();
    SDL_Quit();
}

int game_run(void)
{
    SDL_Event event;

    is_running_flag = 1;
    do {
        if (SDL_WaitEventTimeout(&event, WAIT_EVENT_TIMEOUT) == 0) {
            printf("Fatal: wait SDL event failed. `%s`\n", SDL_GetError());
            game_quit();
            return (-1);
        }

        switch (event.type) {
        case SDL_QUIT:
            game_quit();
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            control_update(&event.key);
            break;
        case SDL_USEREVENT:
            update();
            render();
            break;
        }

        if (control_pressed(CKEY_ESCAPE)) {
            game_quit();
        }
    } while (is_running());

    return (0);
}

void game_quit(void)
{
    is_running_flag = 0;
}

/* static functions implementation */

void update(void)
{
    const unsigned dt = SDL_GetTicks() - last_update_ticks;

    level_update(dt);
    player_update(dt);
    last_update_ticks = SDL_GetTicks();
}

void render(void)
{
    SDL_RenderClear(main_renderer);
    level_render(main_renderer);
    player_render(main_renderer);
    SDL_RenderPresent(main_renderer);
}

int is_running(void)
{
    return is_running_flag;
}

Uint32 tick_timer_callback(Uint32 interval, void *param)
{
    SDL_Event event;

    (void) interval, (void) param; /* unused params */

    if (!is_running()) {
        return 0;
    }

    event.type = SDL_USEREVENT;
    event.user.code = 0;
    event.user.data1 = NULL;
    event.user.data2 = NULL;

    SDL_PushEvent(&event);

    return TICKS_PER_FRAME;
}

/* EOF */
