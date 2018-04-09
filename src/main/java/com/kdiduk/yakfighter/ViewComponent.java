package com.kdiduk.yakfighter;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("serial")
class ViewComponent extends JComponent
{
    private static final int    WINDOW_WIDTH = 800;
    private static final int    WINDOW_HEIGHT = 600;
    private static final String IMAGE_PATH = "/images/sea-tile.png";
    private Controller mController = null;
    private Image mBackgroundTileImage = null;
    private int mBackgroundScrollPos = 10;
    private BufferedImage[] mBuffers = new BufferedImage[2];
    private int mBufferIndex = 0;
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

        java.net.URL imgUrl = getClass().getResource(IMAGE_PATH);
        mBackgroundTileImage = new ImageIcon(imgUrl).getImage();

        mBuffers[0] = new BufferedImage(WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        BufferedImage.TYPE_INT_RGB);
        mBuffers[1] = new BufferedImage(WINDOW_WIDTH,
                                        WINDOW_HEIGHT,
                                        BufferedImage.TYPE_INT_RGB);

        addKeyListener(new ComponentKeyAdapter());
        setFocusable(true);
    }

    public int getBackBufferIndex() {
        return mBufferIndex;
    }

    public int getTopBufferIndex() {
        return (1 - mBufferIndex);
    }

    public void updateBufferIndex() {
        mBufferIndex = 1 - mBufferIndex;
    }

    public void addSprite(Sprite s) {
        mSprites.add(s);
    }

    public void scrollBackground(int dy) {
        int imageHeight = mBackgroundTileImage.getHeight(this);
        mBackgroundScrollPos += dy;
        mBackgroundScrollPos %= imageHeight;
    }

    public void render() {
        BufferedImage buffer = mBuffers[getBackBufferIndex()];

        Graphics gg = buffer.createGraphics();

        int imageWidth = mBackgroundTileImage.getWidth(this);
        int imageHeight = mBackgroundTileImage.getHeight(this);
 
        // draw the image in the upper-left corner
        int xx = 0;
        int yy = mBackgroundScrollPos;
        gg.drawImage(mBackgroundTileImage, xx, yy, null);

        for (int i = 1; i * imageWidth <= WINDOW_WIDTH; i++) {
                gg.copyArea(xx,
                           yy,
                           imageWidth,
                           imageHeight,
                           i * imageWidth,
                           0);
        }
        for (int i = 1; i * imageHeight <= WINDOW_HEIGHT; i *= 2) {
                gg.copyArea(xx,
                           yy,
                           WINDOW_WIDTH,
                           i * imageHeight,
                           0,
                           i * imageHeight);
        }
        if (mBackgroundScrollPos > 0) {
            for (int i = 0; i * imageWidth <= getWidth(); i++) {
                gg.copyArea(xx,
                           yy,
                           imageWidth,
                           imageHeight,
                           i * imageWidth,
                           -imageHeight);
            }
        }

        for (Sprite s: mSprites) {
            gg.drawImage(s.getImage(), s.getPosX(), s.getPosY(), null);
        }

        updateBufferIndex();
    }

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        BufferedImage buffer = mBuffers[getTopBufferIndex()];
        g.drawImage(buffer, 0, 0, null);
        Toolkit.getDefaultToolkit().sync();
    }

    public Dimension getPreferredSize()
    {
        return new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

}

/* eof */
