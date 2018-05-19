#!/usr/bin/env python3

from enum import Enum
import pygame

Key = Enum('Key', \
           'ENTER FIRE CANCEL LEFT RIGHT UP DOWN')


class Controller:
    def __init__(self):
        self._keys = dict()
        for k in Key: self._keys[k] = False

    def is_pressed(self, key):
        if key not in self._keys:
            # TODO: throw an exception
            return False
        else:
            return self._keys[key]

    def update(self, events):
        for e in events:
            pressed = False
            if e.type == pygame.KEYDOWN:
                pressed = True
            elif e.type == pygame.KEYUP:
                pressed = False
            else:
                continue

            if e.key == pygame.K_ESCAPE: self._keys[Key.CANCEL] = pressed
            elif e.key == pygame.K_SPACE: self._keys[Key.FIRE] = pressed
            elif e.key == pygame.K_LEFT: self._keys[Key.LEFT] = pressed
            elif e.key == pygame.K_RIGHT: self._keys[Key.RIGHT] = pressed
            elif e.key == pygame.K_UP: self._keys[Key.UP] = pressed
            elif e.key == pygame.K_DOWN: self._keys[Key.DOWN] = pressed
# eof
