package com.kdiduk.game;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;

public class Engine {

	LinkedList<Sprite> sprites = new LinkedList<Sprite>();
	LinkedList<Sprite> newSprites = new LinkedList<Sprite>();

	public void addSprite(Sprite s) {
		newSprites.add(s);
	}

	public void update(int frameCount) {
		Iterator<Sprite> it = sprites.listIterator();
		while (it.hasNext()) {
			Sprite s = it.next();
			boolean ok = s.update(frameCount);
			if (!ok) {
				s.dispose();
				it.remove();
			}
		}

		sprites.addAll(newSprites);
		newSprites.clear();
	}

	public void render(SpriteBatch batch) {
		for (Sprite s: sprites) {
			s.render(batch);
		}
	}

	public void dispose() {
		for (Sprite s: sprites) {
			s.dispose();
		}
		sprites.clear();
	}

}
