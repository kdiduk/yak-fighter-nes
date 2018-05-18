#!/usr/bin/env python3

from enum import Enum


Key = Enum('Key', \
           'ACTION JUMP CANCEL ENTER LEFT RIGHT UP DOWN')


class Controller:
    def __init__(self):
        self._keys = dict()
        self.set_all_pressed(False)

    def is_pressed(self, key):
        if key not in self._keys:
            # TODO: throw an exception
            return False
        else:
            return self._keys[key]

    def set_pressed(self, key, state):
        if key not in self._keys:
            return
        self._keys[key] = state

    def set_all_pressed(self, state):
        for k in Key:
            self._keys[k] = state;

# eof
