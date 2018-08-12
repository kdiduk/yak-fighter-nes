package com.kdiduk.game.desktop;

import com.badlogic.gdx.backends.lwjgl.LwjglApplication;
import com.badlogic.gdx.backends.lwjgl.LwjglApplicationConfiguration;
import com.kdiduk.game.Game;

public class DesktopLauncher {
    public static final String GAME_TITLE = "Yak Fighter!";
    public static final int GAME_WIDTH = 960;
    public static final int GAME_HEIGHT = 720;

	public static void main (String[] arg) {
		LwjglApplicationConfiguration config = new LwjglApplicationConfiguration();
		config.title = GAME_TITLE;
		config.width = GAME_WIDTH;
		config.height = GAME_HEIGHT;
		config.resizable = false;
        config.fullscreen = true;
		new LwjglApplication(new Game(), config);
	}
}
