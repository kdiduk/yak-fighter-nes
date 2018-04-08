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
    
    public Sprite() throws Exception {
        java.net.URL imgURL = getClass().getResource(IMAGE_PATH);
        mImage = ImageIO.read(imgURL);

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
            mPosX--;
        }
    }

    public void moveRight() {
        if (mPosX + mImage.getWidth() < 800) {
            mPosX++;
        }
    }

    public void moveUp() {
        if (mPosY > 0) {
            mPosY--;
        }
    }

    public void moveDown() {
        if (mPosY + mImage.getHeight() < 600) {
            mPosY++;
        }
    }
}

/* eof */
