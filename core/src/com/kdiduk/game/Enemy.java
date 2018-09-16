package com.kdiduk.game;

public class Enemy extends Sprite {

    int hp = 0;

    public Enemy(Game game, int x) {
        super(game, SpriteType.ENEMY, TextureId.MESSER_MAIN);
        setPos(x, Game.SCREEN_HEIGHT);
        hp = 2;
    }

    @Override
    public boolean update(int frames) {
        if (hp <= 0) {
            return false;
        }

        movePos(0, -1);

        if (getPosY() + getHeight() <= 0) {
            return false;
        }

        return true;
    }
    @Override
    public void damage(int pt) {
        hp -= pt;
    }

}
