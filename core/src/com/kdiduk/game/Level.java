package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;

public class Level {
    protected Game game = null;
    protected Texture texture = null;
    protected int scroll = 0;

    public Level(Game g) {
        game = g;
        texture = new Texture(Gdx.files.internal("level_01.png"));
    }

    public boolean update(int frames) {
        if (frames % 2 == 0) {
            scroll++;
        }

        if (scroll >= texture.getHeight()) {
            return false;
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
