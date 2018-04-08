package com.kdiduk.yakfighter;

import java.awt.*;
import javax.swing.*;

@SuppressWarnings("serial")
class ViewComponent extends JComponent
{
    private static final int    WINDOW_WIDTH = 800;
    private static final int    WINDOW_HEIGHT = 600;
    private static final String IMAGE_PATH = "/images/yak-main.png";
    private Image mImage = null;

    public ViewComponent()
    {
        java.net.URL imgURL = getClass().getResource(IMAGE_PATH);
        ImageIcon imgIcon = new ImageIcon(imgURL);
        mImage = imgIcon.getImage();
    }

    public void paintComponent(Graphics g)
    {
        g.drawImage(mImage, 350, 250, null);
    }

    public Dimension getPreferredSize()
    {
        return new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT);
    }
}

/* eof */
