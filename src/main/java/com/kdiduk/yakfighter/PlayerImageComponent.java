package com.kdiduk.yakfighter;

import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class PlayerImageComponent extends JComponent
{
    private static final String IMAGE_PATH = "/images/yak-main.png";
    private Image mImage = null;

    public PlayerImageComponent()
    {
        java.net.URL imgURL = App.class.getResource(IMAGE_PATH);
        ImageIcon imgIcon = new ImageIcon(imgURL);
        mImage = imgIcon.getImage();
    }

    public void paintComponent(Graphics g)
    {
        g.drawImage(mImage, 280, 200, null);
    }

    public Dimension getPreferredSize()
    {
        return new Dimension(94, 80);
    }
}

/* eof */
