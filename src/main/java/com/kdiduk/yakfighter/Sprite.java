package com.kdiduk.yakfighter;

import java.awt.*;
import java.awt.image.BufferedImage;
import javax.imageio.ImageIO;
import javax.swing.*;

class Sprite {
    private static final String IMAGE_PATH = "/images/yak-main.png";
    private BufferedImage mImage = null;
    private int mPosX = 0;
    private int mPosY = 0;
    private int mWidth = 0;
    private int mHeight = 0;
    
    public Sprite() throws Exception {

        GraphicsConfiguration gfxConfig =
            GraphicsEnvironment.getLocalGraphicsEnvironment()
                               .getDefaultScreenDevice()
                               .getDefaultConfiguration();
        BufferedImage sprite = ImageIO.read(
                getClass().getResourceAsStream(IMAGE_PATH));
        mWidth = sprite.getWidth();
        mHeight = sprite.getHeight();
        
        mImage = gfxConfig.createCompatibleImage(
                mWidth, mHeight, sprite.getTransparency());
        Graphics2D g = (Graphics2D)mImage.getGraphics();
        g.drawImage(sprite, 0, 0, null);
        g.dispose();

        mPosX = 350;
        mPosY = 250;
    }

    public Image getImage() {
        return mImage;
    }

    public int getPosX() {
        return mPosX;
    }

    public int getPosY() {
        return mPosY;
    }

    public void moveLeft() {
        if (mPosX > 0) {
            mPosX -= 5;
        }
    }

    public void moveRight() {
        if (mPosX + mWidth < 800) {
            mPosX += 5;
        }
    }

    public void moveUp() {
        if (mPosY > 0) {
            mPosY -= 5;
        }
    }

    public void moveDown() {
        if (mPosY + mHeight < 600) {
            mPosY += 5;
        }
    }
}

/* eof */
