package com.kdiduk.yakfighter;

import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferStrategy;
import java.awt.event.KeyEvent;
import java.awt.event.KeyAdapter;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;
import javax.swing.JPanel;

@SuppressWarnings("serial")
class ViewComponent extends JPanel
{
    private static final int    WINDOW_WIDTH = 800;
    private static final int    WINDOW_HEIGHT = 600;
    private static final String IMAGE_PATH = "/images/sea-tile.png";
    private Controller mController = null;
    private BufferedImage mBackgroundTileImage = null;
    private BufferedImage mScreenImage = null;
    private int mBackgroundScrollPos = 10;
    private int mTileWidth = 0;
    private int mTileHeight = 0;
    private Graphics2D mGraphics;
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
        mScreenImage = new BufferedImage(
                WINDOW_WIDTH,
                WINDOW_HEIGHT,
                BufferedImage.TYPE_INT_RGB);
        mGraphics = (Graphics2D)mScreenImage.getGraphics();
        try {
            mBackgroundTileImage = ImageIO.read(
                    getClass().getResourceAsStream(IMAGE_PATH));
        }
        catch (Exception e) {
        }
        mTileWidth = mBackgroundTileImage.getWidth();
        mTileHeight = mBackgroundTileImage.getHeight();
        addKeyListener(new ComponentKeyAdapter());
        setIgnoreRepaint(true);
    }

    public void addSprite(Sprite s) {
        mSprites.add(s);
    }

    public void scrollBackground(int dy) {
        mBackgroundScrollPos += dy;
        mBackgroundScrollPos %= mTileHeight;
    }

    public void render() {
        int yy = mBackgroundScrollPos - mTileHeight;
        for (int x = 0; x < WINDOW_WIDTH; x += mTileWidth) {
            for (int y = yy; y < WINDOW_HEIGHT; y += mTileHeight) {
                mGraphics.drawImage(mBackgroundTileImage, x, y, null);
            }
        }

        for (Sprite s: mSprites) {
            mGraphics.drawImage(s.getImage(), s.getPosX(), s.getPosY(), null);
        }

        Graphics g = getGraphics();
        g.drawImage(mScreenImage, 0, 0, null);
        g.dispose();
    }
}

/* eof */
