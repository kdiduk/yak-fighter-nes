package com.kdiduk.yakfighter;

import java.awt.Canvas;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.Transparency;
import java.awt.image.BufferStrategy;
import java.awt.event.KeyEvent;
import java.awt.event.KeyAdapter;
import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.List;
import javax.imageio.ImageIO;

@SuppressWarnings("serial")
class ViewComponent extends Canvas
{
    private static final int    WINDOW_WIDTH = 800;
    private static final int    WINDOW_HEIGHT = 600;
    private static final String IMAGE_PATH = "/images/sea-tile.png";
    private Controller mController = null;
    private BufferedImage mBackgroundTileImage = null;
    private int mBackgroundScrollPos = 0;
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
            GraphicsConfiguration gfxConfig =
                GraphicsEnvironment.getLocalGraphicsEnvironment()
                                   .getDefaultScreenDevice()
                                   .getDefaultConfiguration();
            BufferedImage tile = ImageIO.read(
                    getClass().getResourceAsStream(IMAGE_PATH));
            mTileWidth = tile.getWidth();
            mTileHeight = tile.getHeight();
            
            mBackgroundTileImage = gfxConfig.createCompatibleImage(
                    mTileWidth, mTileHeight, Transparency.BITMASK);
            Graphics2D g = (Graphics2D)mBackgroundTileImage.getGraphics();
            g.drawImage(tile, 0, 0, null);
            g.dispose();
        }
        catch (Exception e) {
        }
        addKeyListener(new ComponentKeyAdapter());
        setIgnoreRepaint(true);
    }

    public void addSprite(Sprite s) {
        mSprites.add(s);
    }

    public void scrollBackground() {
        mBackgroundScrollPos++;
        if (mBackgroundScrollPos >= mTileHeight) {
            mBackgroundScrollPos = 0;
        }
    }

    public void render() {
        BufferStrategy bs = getBufferStrategy();
        if (bs == null) {
            createBufferStrategy(3);
            return;
        }

        Graphics2D g = (Graphics2D)bs.getDrawGraphics();
        int yy = mBackgroundScrollPos - mTileHeight;
        for (int y = yy; y < WINDOW_HEIGHT; y += mTileHeight) {
            for (int x = 0; x < WINDOW_WIDTH; x += mTileWidth) {
                g.drawImage(mBackgroundTileImage, x, y, null);
            }
        }

        for (Sprite s: mSprites) {
            g.drawImage(s.getImage(), s.getPosX(), s.getPosY(), null);
        }

        g.dispose();
        bs.show();
    }
}

/* eof */
