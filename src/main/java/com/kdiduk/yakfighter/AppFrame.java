package com.kdiduk.yakfighter;

import java.awt.EventQueue;
import javax.swing.JFrame;

@SuppressWarnings("serial")
class AppFrame extends JFrame
{
    public AppFrame()
    {
        add(new PlayerImageComponent());
        setResizable(false);
        pack();

        setTitle("Yak Fighter");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public static void main(String[] args)
    {
        EventQueue.invokeLater(() -> {
            JFrame frame = new AppFrame();
            frame.setVisible(true);
        });
    }
}
