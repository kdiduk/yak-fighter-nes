package com.kdiduk.game;

import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public abstract class Sprite {
	protected Game gameObj = null;
	protected SpriteType spriteType = SpriteType.UNDEFINED;
	protected Texture texture = null;
	protected int posX = 0;
	protected int posY = 0;

	public abstract boolean update(int frameCount);
	public abstract void damage(int pt);

	public Sprite(Game game, SpriteType type, TextureId txId) {
		gameObj = game;
		texture = game.getTextureManager().getTexture(txId);
		spriteType = type;
	}

	public void render(SpriteBatch spriteBatch) {
		spriteBatch.draw(getTexture(), getPosX(), getPosY());
	}

	public SpriteType getType() {
		return spriteType;
	}

	public void setPosX(int x) {
		posX = x;
	}

	public void setPosY(int y) {
		posY = y;
	}

	public void setPos(int x, int y) {
		posX = x;
		posY = y;
	}

	public void movePos(int dx, int dy) {
		posX += dx;
		posY += dy;
	}

	public int getPosX() {
		return posX;
	}

	public int getPosY() {
		return posY;
	}

	public Game getGame() {
		return gameObj;
	}

	public Texture getTexture() {
		return texture;
	}

	public int getWidth() {
		return texture.getWidth();
	}

	public int getHeight() {
		return texture.getHeight();
	}
}
