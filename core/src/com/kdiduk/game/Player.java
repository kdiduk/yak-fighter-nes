package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Player implements Sprite {
	protected static final Integer RELOADING_FRAMES = 40;
	protected static final Integer POS_X_DELTA = 5;
	protected static final Integer POS_Y_DELTA = 8;
	protected Game game = null;
	protected Texture texture = null;
	protected Integer posX = 0;
	protected Integer posY = 0;
	protected Integer reloading = 0;

	public Player(Game g) {
		game = g;
		texture = new Texture(Gdx.files.internal("yak_main.png"));
		posX = (Game.SCREEN_WIDTH - texture.getWidth()) / 2;
		posY = (Game.SCREEN_HEIGHT - texture.getHeight()) / 2;
	}

	@Override
	public boolean update(int frameCount) {
		if (reloading > 0) {
			reloading--;
		}

		if (Gdx.input.isKeyPressed(Input.Keys.LEFT) && (frameCount % 2 == 0)) {
			if (posX > 0) {
				posX--;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.RIGHT) && (frameCount % 2 == 0)) {
			if (posX < Game.SCREEN_WIDTH - texture.getWidth()) {
				posX++;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.DOWN) && (frameCount % 2 == 0)) {
			if (posY > 0) {
				posY--;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.UP) && (frameCount % 2 == 0)) {
			if (posY < Game.SCREEN_HEIGHT - texture.getHeight()) {
				posY++;
			}
		}

		if (Gdx.input.isKeyPressed(Input.Keys.SPACE) && reloading == 0) {
			fire();
		}

		return true;
	}

	@Override
	public void render(SpriteBatch spriteBatch) {
		spriteBatch.draw(texture, posX, posY);
	}

	@Override
	public void dispose() {
		if (texture != null) {
			texture.dispose();
		}
	}

	protected void fire() {
		int y = posY + texture.getHeight() - POS_Y_DELTA;
		int x = posX + POS_X_DELTA;
		game.getEngine().addSprite(new Bullet(game, x, y));

		x = posX + texture.getWidth() - POS_X_DELTA;
		game.getEngine().addSprite(new Bullet(game, x, y));

		reloading = RELOADING_FRAMES;
	}
}

/* eof */
