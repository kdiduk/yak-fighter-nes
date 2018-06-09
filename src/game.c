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

#include <SDL2/SDL.h>
#include <stddef.h>
#include <stdio.h>


#define TICKS_PER_FRAME (15u)
#define WAIT_EVENT_TIMEOUT (1000u)
#define MAIN_RENDERER_FLAGS (SDL_RENDERER_ACCELERATED)

static int is_running_flag = 0;
static SDL_TimerID tick_timer_id = 0;

static SDL_Window* main_window = NULL;
static SDL_Renderer* main_renderer = NULL;

static int is_running(void);
static Uint32 tick_timer_callback(Uint32 interval, void* param);


int game_init(int argc, char** argv)
{
    int error = 0;
    (void)argc, (void)argv; /* unused parameters */

    error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    if (error) {
        printf("Fatal: Unable to initialize SDL. `%s`\n", SDL_GetError());
        return error;
    }

    main_window = SDL_CreateWindow("Yak Fighter!",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   GAME_RESOLUTION_X * 3,
                                   GAME_RESOLUTION_Y * 3,
                                   SDL_WINDOW_SHOWN);
    if (!main_window) {
        printf("Fatal: Unable to create main window. `%s`\n", SDL_GetError());
        return (-1);
    }

    main_renderer = SDL_CreateRenderer(main_window, -1, MAIN_RENDERER_FLAGS);
    if (!main_renderer) {
        printf("Fatal: Unable to create main renderer. `%s`\n", SDL_GetError());
        return (-1);
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

    if (main_renderer) {
        SDL_DestroyRenderer(main_renderer);
        main_renderer = NULL;
    }

    if (main_window) {
        SDL_DestroyWindow(main_window);
        main_window = NULL;
    }

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
            break;
        case SDL_USEREVENT:
            /* TODO: update game state */
            SDL_RenderClear(main_renderer);
            /* TODO: render game */
            SDL_RenderPresent(main_renderer);
            break;
        }
    } while (is_running());

    return (0);
}

void game_quit(void)
{
    is_running_flag = 0;
}

/* static functions implementation */

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
