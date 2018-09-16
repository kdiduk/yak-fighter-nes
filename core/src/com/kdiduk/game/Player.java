package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;

public class Player extends Sprite {
	protected static final Integer RELOADING_FRAMES = 40;
	protected static final Integer POS_X_DELTA = 5;
	protected static final Integer POS_Y_DELTA = 8;
	protected int reloading = 0;
	protected int hpLevel = 10;

	public Player(Game game) {
		super(game, SpriteType.PLAYER, TextureId.YAK_MAIN);
		setPosX((Game.SCREEN_WIDTH - getWidth()) / 2);
		setPosY((Game.SCREEN_HEIGHT - getHeight()) / 2);
	}

	@Override
	public boolean update(int frameCount) {
		if (hpLevel <= 0) {
			return false;
		}

		if (reloading > 0) {
			reloading--;
		}

		if (Gdx.input.isKeyPressed(Input.Keys.LEFT) && (frameCount % 2 == 0)) {
			if (getPosX() > 0) {
				movePos(-1,0);
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.RIGHT) && (frameCount % 2 == 0)) {
			if (getPosX() < Game.SCREEN_WIDTH - getWidth()) {
				movePos(1, 0);
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.DOWN) && (frameCount % 2 == 0)) {
			if (getPosY() > 0) {
				movePos(0,-1);
			}
		}
		if (Gdx.input.isKeyPressed(Input.Keys.UP) && (frameCount % 2 == 0)) {
			if (getPosY() < Game.SCREEN_HEIGHT - getHeight()) {
				movePos(0, 1);
			}
		}

		if (Gdx.input.isKeyPressed(Input.Keys.SPACE) && reloading == 0) {
			fire();
		}

		return true;
	}

	@Override
	public void damage(int pt) {
		hpLevel -= pt;
	}

	protected void fire() {
		int y = getPosY() + getHeight() - POS_Y_DELTA;
		int x = getPosX() + POS_X_DELTA;
		getGame().getEngine().addSprite(new Bullet(getGame(), x, y));

		x = getPosX() + getWidth() - POS_X_DELTA;
		getGame().getEngine().addSprite(new Bullet(getGame(), x, y));

		reloading = RELOADING_FRAMES;
	}
}

/* eof */
