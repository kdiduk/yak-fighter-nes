#!/usr/bin/env python3

import pygame


class Screen:
    def __init__(self, resolution, scale):
        self._resolution = resolution
        self._screen_size = (resolution[0]*scale, resolution[1]*scale)
        self._display = pygame.display.set_mode(self._screen_size, pygame.DOUBLEBUF)
        self._buffer = pygame.Surface(resolution, pygame.HWSURFACE)

    def blit(self, surface, rect, area=None):
        self._buffer.blit(surface, rect, area)

    def flip(self):
        pygame.transform.scale(self._buffer, self._screen_size, self._display)
        pygame.display.flip()

    def get_size(self):
        return self._screen_size

    def get_resolution(self):
        return self._resolution

# eof
