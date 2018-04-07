package com.kdiduk.yakfighter;

import javax.swing.JFrame;

class AppFrame extends JFrame
{
    public AppFrame()
    {
        add(new PlayerImageComponent());
        setSize(640, 480);
    }
}
