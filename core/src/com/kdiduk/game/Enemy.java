package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Enemy implements Sprite {
    protected Game game = null;
    protected Texture texture = null;
    protected int posX = 0;
    protected int posY = 0;

    public Enemy(Game g, int x) {
        game = g;
        texture = new Texture(Gdx.files.internal("messer_main.png"));
        posX = x;
        posY = Game.SCREEN_HEIGHT;
    }

    @Override
    public boolean update(int frames) {
        posY--;

        if (posY + texture.getHeight() <= 0) {
            return false;
        }

        return true;
    }

    @Override
    public void render(SpriteBatch batch) {
        batch.draw(texture, posX, posY);
    }

    @Override
    public void dispose() {
        texture.dispose();
    }
}
