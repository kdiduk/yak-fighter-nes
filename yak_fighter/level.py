#!/usr/bin/env python3

import pygame


class Level:
    def __init__(self, game):
        self._game = game
        tile = pygame.image.load('data/images/sea_tile.png').convert()
        self._tile_size = tile.get_size()
        self._elapsed = 0
        self._scroll_pos = 0
        self._background = pygame.Surface((game.RESX, 2*game.RESY))
        for x in range(0, game.RESX, self._tile_size[0]):
            for y in range(0, 2*game.RESY, self._tile_size[1]):
                self._background.blit(tile, (x, y) + self._tile_size)

    def update(self, elapsed):
        self._elapsed += elapsed
        if self._elapsed > (1000 // self._game.FPS) + 5:
            self._elapsed = 0
            self._scroll_pos += 1
            self._scroll_pos %= self._tile_size[1]

    def render(self, display):
        shift = (2 * self._tile_size[1]) - self._scroll_pos
        display.blit(self._background,
                    (0, 0, self._game.RESX, self._game.RESY),
                    (0, shift, self._game.RESX, self._game.RESY))

# eof
