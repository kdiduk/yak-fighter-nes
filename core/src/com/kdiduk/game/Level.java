package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Level {
    protected static final int NEXT_ENEMY_DELTA = 60;

    protected Game game = null;
    protected Texture texture = null;
    protected int scroll = 0;
    protected int nextEnemy = 0;

    public Level(Game g) {
        game = g;
        texture = new Texture(Gdx.files.internal("level_01.png"));
        nextEnemy = NEXT_ENEMY_DELTA + (int)(Math.random() * 120);
    }

    public boolean update(int frames) {
        if (frames % 2 == 0) {
            scroll++;
        }

        if (scroll >= texture.getHeight()) {
            return false;
        }

        if (nextEnemy > 0) {
            nextEnemy--;
        }
        else {
            nextEnemy = NEXT_ENEMY_DELTA + (int)(Math.random() + 120);
            int x = 0 + (int)(Math.random() * (Game.SCREEN_WIDTH - 40));
            Enemy enemy = new Enemy(game, x);
            game.getEngine().addSprite(enemy);
        }

        return true;
    }

    public void render(SpriteBatch batch) {
        batch.draw(texture, 0, -scroll);
    }

    public void dispose() {
        texture.dispose();
    }
}
