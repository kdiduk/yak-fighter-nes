#!/usr/bin/env python3

import pygame


class Bullet:
    def __init__(self, game, rect):
        self._game = game
        self._sprite = pygame.image.load('data/images/bullet.png').convert_alpha()
        self._rect_left = self._sprite.get_rect()
        self._rect_right = self._sprite.get_rect()
        self._elapsed = 0

        self._rect_left.topleft = rect.topleft
        self._rect_right.topright = rect.topright

        self._rect_left.move_ip(3, 3)
        self._rect_right.move_ip(-3, 3)

    def update(self, elapsed):
        self._rect_left.move_ip(0, -2)
        self._rect_right.move_ip(0, -2)
        if self._rect_left.bottom <= 0 or self._rect_right.bottom <= 0:
            self._game.remove_object(self)

    def render(self, screen):
        screen.blit(self._sprite, self._rect_left)
        screen.blit(self._sprite, self._rect_right)

# eof
