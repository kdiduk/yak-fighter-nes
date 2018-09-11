package com.kdiduk.game;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public interface Sprite {
	boolean update(int frameCount);
	void render(SpriteBatch spriteBatch);
	void dispose();
}
