package com.kdiduk.game;

public class Bullet extends Sprite {

	protected int hp = 1;

	public Bullet(Game game, int x, int y) {
		super(game, SpriteType.PLAYER_BULLET, TextureId.BULLET);
		setPos(x - (texture.getWidth() / 2), y);
	}

	@Override
	public boolean update(int frameCount) {
		if (hp <= 0) {
			return false;
		}
		
		posY++;
		if (posY >= Game.SCREEN_HEIGHT) {
			return false;
		}

		return true;
	}

	@Override
	public void damage(int pt) {
		hp -= pt;
	}
}
