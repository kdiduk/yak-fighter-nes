package com.kdiduk.yakfighter;

import javax.swing.JComponent;
import javax.swing.JFrame;

@SuppressWarnings("serial")
public class AppFrame extends JFrame
{
    public AppFrame(JComponent viewComponent)
    {
        add(viewComponent);
        setResizable(false);
        pack();

        setTitle("Yak Fighter");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

}
