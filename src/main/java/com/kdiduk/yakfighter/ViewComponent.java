package com.kdiduk.yakfighter;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

@SuppressWarnings("serial")
class ViewComponent extends JComponent
{
    private static final int    WINDOW_WIDTH = 800;
    private static final int    WINDOW_HEIGHT = 600;
    private static final String IMAGE_PATH = "/images/yak-main.png";
    private Controller mController = null;
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
        addKeyListener(new ComponentKeyAdapter());
        setFocusable(true);
    }

    public void addSprite(Sprite s) {
        mSprites.add(s);
    }

    @Override
    public void paintComponent(Graphics g)
    {
        for (Sprite s: mSprites) {
            g.drawImage(s.getImage(), s.getPosX(), s.getPosY(), null);
        }
    }

    public Dimension getPreferredSize()
    {
        return new Dimension(WINDOW_WIDTH, WINDOW_HEIGHT);
    }

}

/* eof */
