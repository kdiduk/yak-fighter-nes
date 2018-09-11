package com.kdiduk.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;

public class Game extends ApplicationAdapter {
	public static final int SCREEN_WIDTH = 320;
	public static final int SCREEN_HEIGHT = 240;

	private Viewport viewport = null;
	private OrthographicCamera camera = null;
	private SpriteBatch spriteBatch;
	private Texture background = null;
	private Player player = null;
	private Engine engine = null;
	private int backgroundScrollPos = 0;
	private int frameCounter = 0;
	
	@Override
	public void create() {
		camera = new OrthographicCamera();
		camera.setToOrtho(false, SCREEN_WIDTH, SCREEN_HEIGHT);
		viewport = new FitViewport(SCREEN_WIDTH, SCREEN_HEIGHT, camera);
		viewport.setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		spriteBatch = new SpriteBatch();
		background = new Texture(Gdx.files.internal("level_01.png"));
		player = new Player(this);
		engine = new Engine();
		engine.addSprite(player);
	}

	public Engine getEngine() {
		return engine;
	}

	@Override
	public void resize(int width, int height) {
		viewport.update(width, height);
	}

	@Override
	public void render() {
		engine.update(frameCounter);
		if (Gdx.input.isKeyPressed(Input.Keys.ESCAPE)) {
			Gdx.app.exit();
			return;
		}
		if (frameCounter % 2 == 0) {
			backgroundScrollPos++;
		}

		frameCounter++;
		camera.update();

		Gdx.gl.glClearColor(0, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
		spriteBatch.setProjectionMatrix(camera.combined);
		spriteBatch.begin();
		spriteBatch.draw(background, 0, -backgroundScrollPos);
		engine.render(spriteBatch);
		spriteBatch.end();
	}

	@Override
	public void dispose() {
		spriteBatch.dispose();
		background.dispose();
		engine.dispose();
	}
}

/* eof */
