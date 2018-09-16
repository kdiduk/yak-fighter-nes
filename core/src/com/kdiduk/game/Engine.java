package com.kdiduk.game;

import com.badlogic.gdx.graphics.g2d.SpriteBatch;

import java.util.Iterator;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.SortedMap;

public class Engine {

	LinkedList<Sprite> sprites = new LinkedList<Sprite>();
	LinkedList<Sprite> newSprites = new LinkedList<Sprite>();

	public void addSprite(Sprite s) {
		newSprites.add(s);
	}

	public void update(int frameCount) {
		detectCollisions();
		Iterator<Sprite> it = sprites.listIterator();
		while (it.hasNext()) {
			Sprite s = it.next();
			boolean ok = s.update(frameCount);
			if (!ok) {
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
		sprites.clear();
	}

	public void detectCollisions() {
		ListIterator<Sprite> it = sprites.listIterator();
		while (it.hasNext()) {
			Sprite s = it.next();
			final int iNext = it.nextIndex();
			if (iNext >= sprites.size()) {
				break;
			}
			ListIterator<Sprite> jt = sprites.listIterator(iNext);
			while (jt.hasNext()) {
				Sprite t = jt.next();
				if (!detectCollision(s, t)) {
					detectCollision(t, s);
				}
			}
		}
	}

	protected boolean detectCollision(Sprite s, Sprite t) {
		if (s.getType() == SpriteType.PLAYER) {
			if (t.getType() == SpriteType.ENEMY) {
				// TODO
			}
		}
		else if (s.getType() == SpriteType.PLAYER_BULLET) {
			if (t.getType() == SpriteType.ENEMY) {
				if ((t.getPosX() <= s.getPosX()) && (s.getPosX() <= (t.getPosX() + t.getWidth()))
					&& (t.getPosY() <= s.getPosY()) && (s.getPosY() <= (t.getPosY() + t.getHeight())))
				{
					s.damage(1);
					t.damage(1);
					return true;
				}
			}
		}
		return false;
	}
}
