package com.kdiduk.game;

import com.badlogic.gdx.ApplicationAdapter;
import com.badlogic.gdx.Gdx;
import com.badlogic.gdx.Input;
import com.badlogic.gdx.graphics.GL20;
import com.badlogic.gdx.graphics.OrthographicCamera;
import com.badlogic.gdx.graphics.Texture;
import com.badlogic.gdx.graphics.g2d.SpriteBatch;
import com.badlogic.gdx.utils.Scaling;
import com.badlogic.gdx.utils.viewport.FitViewport;
import com.badlogic.gdx.utils.viewport.Viewport;
import sun.java2d.SunCompositeContext;

public class Game extends ApplicationAdapter {
    public static final int SCREEN_WIDTH = 320;
    public static final int SCREEN_HEIGHT = 240;


    private Viewport mViewport = null;
    private OrthographicCamera mCamera = null;
	private SpriteBatch mSpriteBatch;
    private Texture mBackground = null;
    private Texture mPlayer = null;

    private int mBackgroundScrollPos = 0;
    private int mPlayerPosX = SCREEN_WIDTH / 2 - 20;
    private int mPlayerPosY = SCREEN_HEIGHT / 2 - 16;
    private int mFrameCounter = 0;
	
	@Override
	public void create() {
	    mCamera = new OrthographicCamera();
	    mCamera.setToOrtho(false, SCREEN_WIDTH, SCREEN_HEIGHT);
        mViewport = new FitViewport(SCREEN_WIDTH, SCREEN_HEIGHT, mCamera);
        mViewport.setScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);
        mSpriteBatch = new SpriteBatch();
		mBackground = new Texture(Gdx.files.internal("level_01.png"));
		mPlayer = new Texture(Gdx.files.internal("yak_main.png"));
	}

	@Override
    public void resize(int width, int height) {
	    mViewport.update(width, height);
    }

	@Override
	public void render() {
	    if (Gdx.input.isKeyPressed(Input.Keys.ESCAPE)) {
            Gdx.app.exit();
            return;
        }
        if (mFrameCounter % 2 == 0) {
            mBackgroundScrollPos++;
            if (mBackgroundScrollPos > mBackground.getHeight() - 240) {
                Gdx.app.exit();
            }

            if (Gdx.input.isKeyPressed(Input.Keys.LEFT)) {
                if (mPlayerPosX > 0) {
                    mPlayerPosX--;
                }
            }
            if (Gdx.input.isKeyPressed(Input.Keys.RIGHT)) {
                if (mPlayerPosX < SCREEN_WIDTH - mPlayer.getWidth()) {
                    mPlayerPosX++;
                }
            }
            if (Gdx.input.isKeyPressed(Input.Keys.DOWN)) {
                if (mPlayerPosY > 0) {
                    mPlayerPosY--;
                }
            }
            if (Gdx.input.isKeyPressed(Input.Keys.UP)) {
                if (mPlayerPosY < SCREEN_HEIGHT - mPlayer.getHeight()) {
                    mPlayerPosY++;
                }
            }
            if (Gdx.input.isKeyPressed(Input.Keys.SPACE)) {
                /* TOOD: Fire */
            }
        }

        mFrameCounter++;
	    mCamera.update();

		Gdx.gl.glClearColor(0, 0, 0, 1);
		Gdx.gl.glClear(GL20.GL_COLOR_BUFFER_BIT);
        mSpriteBatch.setProjectionMatrix(mCamera.combined);
		mSpriteBatch.begin();
        mSpriteBatch.draw(mBackground, 0, -mBackgroundScrollPos);
        mSpriteBatch.draw(mPlayer, mPlayerPosX, mPlayerPosY);
        mSpriteBatch.end();
	}
	
	@Override
	public void dispose() {
        mSpriteBatch.dispose();
		mBackground.dispose();
		mPlayer.dispose();
	}
}
