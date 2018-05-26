#!/usr/bin/env python3

from yak_fighter.controls import Controller
from yak_fighter.controls import Key
from yak_fighter.level import Level
from yak_fighter.player import Player
from yak_fighter.screen import Screen
import pygame


class Game:
    FPS = 60
    RESX = 320
    RESY = 240
    SCALE = 3

    def __init__(self):
        pygame.init()
        self._is_quit_event = False
        self._screen = Screen((Game.RESX, Game.RESY), Game.SCALE)
        self._controller = Controller()
        self._level = Level(self)
        self._player = Player(self)

    def get_controller(self):
        return self._controller

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
        self._level.update(ms_elapsed)
        self._player.update(ms_elapsed)

    def _render(self, ms_elapsed):
        self._level.render(self._screen)
        self._player.render(self._screen)
        self._screen.flip()

    def _update_system_events(self):
        if pygame.event.get(pygame.QUIT):
            self.quit()
        self._controller.update(
            pygame.event.get((pygame.KEYUP, pygame.KEYDOWN)))

        # remove remaining events from the queue
        pygame.event.get()

# eof
