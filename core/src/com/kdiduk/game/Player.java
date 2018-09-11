package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Player implements Sprite {

	protected Game mGame = null;
	protected Texture mTexture = null;
	private int mPosX = 0;
	private int mPosY = 0;

	public Player(Game game) {
		mGame = game;
		mTexture = new Texture(Gdx.files.internal("yak_main.png"));
		mPosX = (Game.SCREEN_WIDTH - mTexture.getWidth()) / 2;
		mPosY = (Game.SCREEN_HEIGHT - mTexture.getHeight()) / 2;
	}

	@Override
	public boolean update(int frameCount) {
		if (frameCount % 2 == 0) {
			return true;
		}

		if (Gdx.input.isKeyPressed(Input.Keys.LEFT)) {
			if (mPosX > 0) {
				mPosX--;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.RIGHT)) {
			if (mPosX < Game.SCREEN_WIDTH - mTexture.getWidth()) {
				mPosX++;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.DOWN)) {
			if (mPosY > 0) {
				mPosY--;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.UP)) {
			if (mPosY < Game.SCREEN_HEIGHT - mTexture.getHeight()) {
				mPosY++;
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.SPACE)) {
			/* TOOD: Fire */
		}

		return true;
	}

	@Override
	public void render(SpriteBatch spriteBatch) {
		spriteBatch.draw(mTexture, mPosX, mPosY);
	}

	@Override
	public void dispose() {
		if (mTexture != null) {
			mTexture.dispose();
		}
	}
}

/* eof */
