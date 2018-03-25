package com.kdiduk.yakfighter;

import java.awt.EventQueue;
import javax.swing.JFrame;


/**
 * Hello world!
 *
 */
public class App 
{
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
