#!/usr/bin/env python3

import pygame


class Game:
    FPS = 50
    RESX = 320
    RESY = 240
    SCALE = 3

    def __init__(self):
        pygame.init()
        self._is_quit_event = False
        self._scroll_pos = 0
        self._screen = pygame.display.set_mode(
                # (Game.RESX * Game.SCALE, Game.RESY * Game.SCALE),
                (0,0),
                pygame.DOUBLEBUF | pygame.FULLSCREEN)
        self._left_pressed = False
        self._right_pressed = False
        self._up_pressed = False
        self._down_pressed = False
        self._tile = pygame.image.load('data/images/sea_tile.png').convert()
        self._tile_size = self._tile.get_size()

        player = pygame.image.load('data/images/yak_main.png').convert_alpha()
        player_rect = player.get_rect()
        self._player = pygame.transform.scale(player,
                                              (Game.SCALE * player_rect.width,
                                               Game.SCALE * player_rect.height))
        self._player_rect = self._player.get_rect().move((Game.SCALE * 150, Game.SCALE * 100))
        self._scroll_elapsed = 0
        _background = pygame.Surface((Game.RESX, 2*Game.RESY))
        for x in range(0, Game.RESX, self._tile_size[0]):
            for y in range(0, 2*Game.RESY, self._tile_size[1]):
                rect = (x, y, x + self._tile_size[0], y + self._tile_size[1])
                _background.blit(self._tile, rect)
        self._background = pygame.transform.scale(
                _background,
                (Game.SCALE * Game.RESX, 2 * Game.SCALE * Game.RESY))

    def quit(self):
        self._is_quit_event = True

    def run(self):
        clock = pygame.time.Clock()
        elapsed = 0
        while True:
            self._update_system_events()
            if self._is_quit_event:
                break

            self._update(elapsed)
            self._render(elapsed)

            elapsed = clock.tick_busy_loop(Game.FPS)

    def _update(self, ms_elapsed):
        self._scroll_elapsed += ms_elapsed
        if (self._scroll_elapsed > (1000 // Game.FPS) + 5):
            self._scroll_elapsed = 0
            self._scroll_pos += 1
            self._scroll_pos %= self._tile_size[1]
            if self._left_pressed:
                self._player_rect = self._player_rect.move((-1 * Game.SCALE, 0))
            if self._right_pressed:
                self._player_rect = self._player_rect.move((1 * Game.SCALE, 0))
            if self._up_pressed:
                self._player_rect = self._player_rect.move((0, -1 * Game.SCALE))
            if self._down_pressed:
                self._player_rect = self._player_rect.move((0, 1 * Game.SCALE))

    def _render(self, ms_elapsed):
        screen_size = (Game.RESX * Game.SCALE, Game.RESY * Game.SCALE)
        shift = 2* self._tile_size[1] - self._scroll_pos
        clip = (0, shift * Game.SCALE,
                screen_size[0],
                screen_size[1] + shift * Game.SCALE)
        self._screen.blit(
                self._background,
                (0, 0, screen_size[0], screen_size[1]),
                clip)
        self._screen.blit(self._player, self._player_rect)
        pygame.display.flip()

    def _update_system_events(self):
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                self.quit()
            elif e.type == pygame.KEYDOWN:
                if e.key == pygame.K_ESCAPE:
                    self.quit()
                elif e.key == pygame.K_LEFT:
                    self._left_pressed = True
                elif e.key == pygame.K_RIGHT:
                    self._right_pressed = True
                elif e.key == pygame.K_UP:
                    self._up_pressed = True
                elif e.key == pygame.K_DOWN:
                    self._down_pressed = True
            elif e.type == pygame.KEYUP:
                if e.key == pygame.K_LEFT:
                    self._left_pressed = False
                elif e.key == pygame.K_RIGHT:
                    self._right_pressed = False
                elif e.key == pygame.K_UP:
                    self._up_pressed = False
                elif e.key == pygame.K_DOWN:
                    self._down_pressed = False

# eof
