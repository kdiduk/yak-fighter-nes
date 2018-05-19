#!/usr/bin/env python3

from yak_fighter.controls import Controller
from yak_fighter.controls import Key
from yak_fighter.screen import Screen
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
        self._resolution = (Game.RESX, Game.RESY)
        screen_size = (Game.RESX * Game.SCALE, Game.RESY * Game.SCALE)
        self._screen = Screen(self._resolution, screen_size)
        self._controller = Controller()
        self._tile = pygame.image.load('data/images/sea_tile.png').convert()
        self._tile_size = self._tile.get_size()

        self._player = pygame.image.load('data/images/yak_main.png').convert_alpha()
        self._player_rect = self._player.get_rect().move((150, 100))
        self._scroll_elapsed = 0
        self._background = pygame.Surface((Game.RESX, 2*Game.RESY))
        for x in range(0, Game.RESX, self._tile_size[0]):
            for y in range(0, 2*Game.RESY, self._tile_size[1]):
                rect = (x, y, x + self._tile_size[0], y + self._tile_size[1])
                self._background.blit(self._tile, rect)

    def quit(self):
        self._is_quit_event = True

    def run(self):
        clock = pygame.time.Clock()
        elapsed = 0
        while not self._is_quit_event:
            self._update_system_events()
            self._update(elapsed)
            self._render(elapsed)
            elapsed = clock.tick_busy_loop(Game.FPS)

    def _update(self, ms_elapsed):
        if self._controller.is_pressed(Key.CANCEL):
            self.quit()
            return

        self._scroll_elapsed += ms_elapsed
        if self._scroll_elapsed > (1000 // Game.FPS) + 5:
            self._scroll_elapsed = 0
            self._scroll_pos += 1
            self._scroll_pos %= self._tile_size[1]
            if self._controller.is_pressed(Key.LEFT) and self._player_rect.left > 0:
                self._player_rect = self._player_rect.move((-2, 0))
            if self._controller.is_pressed(Key.RIGHT) and self._player_rect.right < Game.RESX:
                self._player_rect = self._player_rect.move((2, 0))
            if self._controller.is_pressed(Key.UP) and self._player_rect.top > 0:
                self._player_rect = self._player_rect.move((0, -2))
            if self._controller.is_pressed(Key.DOWN) and self._player_rect.bottom < Game.RESY:
                self._player_rect = self._player_rect.move((0, 2))

    def _render(self, ms_elapsed):
        shift = (2 * self._tile_size[1]) - self._scroll_pos
        self._screen.blit(self._background,
                          (0, 0) + self._resolution,
                          (0, shift) + self._resolution)
        self._screen.blit(self._player, self._player_rect)
        self._screen.flip()

    def _update_system_events(self):
        if pygame.event.get(pygame.QUIT):
            self.quit()
        self._controller.update(
            pygame.event.get((pygame.KEYUP, pygame.KEYDOWN)))

        # remove remaining events from the queue
        pygame.event.get()

# eof
