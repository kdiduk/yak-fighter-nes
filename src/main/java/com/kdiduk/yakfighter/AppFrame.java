package com.kdiduk.yakfighter;

import java.awt.EventQueue;
import javax.swing.JFrame;

class AppFrame extends JFrame
{
    public AppFrame()
    {
        add(new PlayerImageComponent());
        setSize(640, 480);
    }

    public static void main( String[] args )
    {
        EventQueue.invokeLater(
            () ->
            {
                AppFrame frame = new AppFrame();
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.setVisible(true);
            }
        );
    }
}
