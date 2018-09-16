package com.kdiduk.game;

import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.graphics.Texture;

import java.util.EnumMap;

public class TextureManager {
    protected final EnumMap<TextureId, Texture> textureMap;

    public TextureManager() {
        textureMap = new EnumMap<TextureId, Texture>(TextureId.class);
        for (TextureId id: TextureId.values()) {
            textureMap.put(id, new Texture(Gdx.files.internal(id.toString())));
        }
    }

    public Texture getTexture(TextureId id) {
        return textureMap.get(id);
    }

    public void dispose() {
        for (Texture tx: textureMap.values()) {
            tx.dispose();
        }
    }
}
