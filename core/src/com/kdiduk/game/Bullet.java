package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Bullet implements Sprite {

	protected Game game = null;
	protected Texture texture = null;
	protected Integer posX = 0;
	protected Integer posY = 0;

	public Bullet(Game game, int x, int y) {
		this.game = game;
		this.texture = new Texture(Gdx.files.internal("bullet.png"));
		this.posX = x - (texture.getWidth() / 2);
		this.posY = y;
	}

	@Override
	public boolean update(int frameCount) {
		posY++;
		if (posY >= Game.SCREEN_HEIGHT) {
			return false;
		}

		return true;
	}

	@Override
	public void render(SpriteBatch spriteBatch) {
		spriteBatch.draw(texture, posX, posY);
	}

	@Override
	public void dispose() {
		texture.dispose();
	}
}
