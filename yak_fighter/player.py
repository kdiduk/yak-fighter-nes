#!/usr/bin/env python3

from yak_fighter.bullet import Bullet
from yak_fighter.controls import Key
import pygame


class Player:
    def __init__(self, game):
        self._game = game
        self._controller = game.get_controller()
        self._sprite = pygame.image.load('data/images/yak_main.png').convert_alpha()
        self._rect = self._sprite.get_rect().move(150, 100)
        self._elapsed = 0
        self._reloading = 0

    def update(self, elapsed):
        if self._reloading > 0:
            self._reloading -= elapsed
            if self._reloading < 0: self._reloading = 0

        self._elapsed += elapsed
        if self._elapsed < (1000 // self._game.FPS) + 5:
            return

        self._elapsed = 0
        if self._controller.is_pressed(Key.LEFT) and self._rect.left > 0:
            self._rect = self._rect.move((-2, 0))
        if self._controller.is_pressed(Key.RIGHT) and self._rect.right < self._game.RESX:
            self._rect = self._rect.move((2, 0))
        if self._controller.is_pressed(Key.UP) and self._rect.top > 0:
            self._rect = self._rect.move((0, -2))
        if self._controller.is_pressed(Key.DOWN) and self._rect.bottom < self._game.RESY:
            self._rect = self._rect.move((0, 2))
        if self._controller.is_pressed(Key.FIRE) and self._reloading <= 0:
            self._game.add_object(Bullet(self._game, self._rect))
            self._reloading = 400

    def render(self, screen):
        screen.blit(self._sprite, self._rect)