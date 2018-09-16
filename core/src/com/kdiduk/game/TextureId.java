package com.kdiduk.game;

public enum TextureId {
    YAK_MAIN("yak_main.png"),
    MESSER_MAIN("messer_main.png"),
    BULLET("bullet.png"),
    LEVEL_01("level_01.png");

    private final String text;

    TextureId(String str) {
        text = str;
    }

    @Override
    public String toString() {
        return text;
    }
}
