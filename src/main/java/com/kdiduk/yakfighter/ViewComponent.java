package com.kdiduk.yakfighter;

import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.image.BufferStrategy;
import java.awt.event.KeyEvent;
import java.awt.event.KeyAdapter;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("serial")
class ViewComponent extends Canvas
{
    private static final int    WINDOW_WIDTH = 800;
    private static final int    WINDOW_HEIGHT = 600;
    private static final String IMAGE_PATH = "/images/sea-tile.png";
    private Controller mController = null;
    private BufferedImage mBackgroundTileImage = null;
    private int mBackgroundScrollPos = 10;
    private int mTileWidth = 0;
    private int mTileHeight = 0;
    List<Sprite> mSprites = new ArrayList<Sprite>();

    private class ComponentKeyAdapter extends KeyAdapter {
        @Override
        public void keyPressed(KeyEvent e) {
            switch (e.getKeyCode()) {
            case KeyEvent.VK_LEFT:
                mController.setKeyPressed(Controller.Key.LEFT, true);
                break;
            case KeyEvent.VK_RIGHT:
                mController.setKeyPressed(Controller.Key.RIGHT, true);
                break;
            case KeyEvent.VK_UP:
                mController.setKeyPressed(Controller.Key.UP, true);
                break;
            case KeyEvent.VK_DOWN:
                mController.setKeyPressed(Controller.Key.DOWN, true);
                break;
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {
            switch (e.getKeyCode()) {
            case KeyEvent.VK_LEFT:
                mController.setKeyPressed(Controller.Key.LEFT, false);
                break;
            case KeyEvent.VK_RIGHT:
                mController.setKeyPressed(Controller.Key.RIGHT, false);
                break;
            case KeyEvent.VK_UP:
                mController.setKeyPressed(Controller.Key.UP, false);
                break;
            case KeyEvent.VK_DOWN:
                mController.setKeyPressed(Controller.Key.DOWN, false);
                break;
            }
        }
    }

    public ViewComponent(Controller controller)
    {
        mController = controller;
        try {
            mBackgroundTileImage = ImageIO.read(getClass().getResourceAsStream(IMAGE_PATH));
        }
        catch (Exception e) {
        }
        mTileWidth = mBackgroundTileImage.getWidth();
        mTileHeight = mBackgroundTileImage.getHeight();
        addKeyListener(new ComponentKeyAdapter());
    }

    public void addSprite(Sprite s) {
        mSprites.add(s);
    }

    public void scrollBackground(int dy) {
        mBackgroundScrollPos += dy;
        mBackgroundScrollPos %= mTileHeight;
    }

    public void render() {
        BufferStrategy bufferStrategy = getBufferStrategy();
        if (bufferStrategy == null) {
            createBufferStrategy(3);
            return;
        }
        Graphics gg = bufferStrategy.getDrawGraphics();

        // draw the image in the upper-left corner
        int xx = 0;
        int yy = mBackgroundScrollPos;
        gg.drawImage(mBackgroundTileImage, xx, yy, null);

        for (int i = 1; i * mTileWidth <= WINDOW_WIDTH; i++) {
            gg.copyArea(xx,
                       yy,
                       mTileWidth,
                       mTileHeight,
                       i * mTileWidth,
                       0);
        }
        for (int i = 1; i * mTileHeight <= WINDOW_HEIGHT; i *= 2) {
            gg.copyArea(xx,
                       yy,
                       WINDOW_WIDTH,
                       i * mTileHeight,
                       0,
                       i * mTileHeight);
        }
        if (mBackgroundScrollPos > 0) {
            gg.copyArea(xx,
                       yy,
                       WINDOW_WIDTH,
                       mTileHeight,
                       0,
                       -mTileHeight);
        }

        for (Sprite s: mSprites) {
            gg.drawImage(s.getImage(), s.getPosX(), s.getPosY(), null);
        }

        gg.dispose();
        bufferStrategy.show();
    }
}

/* eof */
