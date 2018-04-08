package com.kdiduk.yakfighter;

import java.awt.event.*;
import java.util.Collections;
import java.util.EnumMap;
import java.util.Map;



class Controller extends KeyAdapter {
    public enum Key {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        FIRE
    };

    private Map<Key, Boolean> mKeyPressed =
        Collections.synchronizedMap(new EnumMap<Key, Boolean>(Key.class));

    public Controller() {
        resetAll();
    }

    public boolean isKeyPressed(Key key) {
        return mKeyPressed.get(key);
    }

    public void setKeyPressed(Key key, boolean isSet) {
        mKeyPressed.put(key, isSet);
    }

    public void resetAll() {
        for (Key key: Key.values()) {
            mKeyPressed.put(key, false);
        }
    }

}

/* eof */
