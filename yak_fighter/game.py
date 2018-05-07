#!/usr/bin/env python3

import pygame


class Game:
    def __init__(self):
        self._is_quit_event = False
        pygame.init()
        pygame.display.set_mode((320, 240), 0)

    def quit(self):
        self._is_quit_event = True

    def run(self):
        frames_per_sec = 50
        clock = pygame.time.Clock()
        while True:
            self._update_system_events()
            if self._is_quit_event:
                break

            # todo

            clock.tick(frames_per_sec)

    def _update_system_events(self):
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                self.quit()
            elif e.type == pygame.KEYDOWN and e.key == pygame.K_ESCAPE:
                self.quit()

# eof
