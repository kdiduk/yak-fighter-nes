package com.kdiduk.yakfighter;

import java.awt.event.*;
import java.awt.EventQueue;
import java.util.concurrent.TimeUnit;
import javax.swing.JComponent;
import javax.swing.JFrame;

public class Game  {
    public static final long MSECS_PER_FRAME = 50;
    public static final long NANOSECS_PER_FRAME = MSECS_PER_FRAME * 1000000;

    private JFrame mAppFrame = null;
    private ViewComponent mViewComponent = null;
    private Controller mController = new Controller();
    private Sprite mPlayer = null;
    private boolean mGameExit = false;
    private Thread mRunThread = null;

    public Game(String[] args) {
        mViewComponent = new ViewComponent(mController);
        mAppFrame = new AppFrame(mViewComponent);
        render();
        mAppFrame.setVisible(true);
        mAppFrame.addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e) {
                onWindowClose();
            }
        });
        mRunThread = new Thread(() -> {
            mainLoop();
        });
        mRunThread.setPriority(Thread.MAX_PRIORITY);
        
        try {
            mPlayer = new Sprite();
            mViewComponent.addSprite(mPlayer);
        }
        catch (Exception e) {
        }
    }

    public void run() {
        mRunThread.start();
    }

    public synchronized boolean isGameExit() {
        return mGameExit;
    }

    public synchronized void setGameExit() {
        mGameExit = true;
    }

    private void mainLoop() {
        while (true) {
            long tStart = System.nanoTime();
            if (isGameExit()) {
                break;
            }

            update();
            render();

            syncFrame(tStart);
        }

        System.out.println("DEBUG: game loop terminated successfully");
    }

    private void update() {
        if (mController.isKeyPressed(Controller.Key.LEFT)) {
            mPlayer.moveLeft();
        }
        else if (mController.isKeyPressed(Controller.Key.RIGHT)) {
            mPlayer.moveRight();
        }

        if (mController.isKeyPressed(Controller.Key.UP)) {
            mPlayer.moveUp();
        }
        else if (mController.isKeyPressed(Controller.Key.DOWN)) {
            mPlayer.moveDown();
        }

        mViewComponent.scrollBackground(4);
    }

    private void render() {
        /* TODO */
        mViewComponent.render();
        mViewComponent.repaint();
    }

    private void syncFrame(long startTime) {
        long endTime = startTime + NANOSECS_PER_FRAME;
        try {
            TimeUnit.NANOSECONDS.sleep(endTime - System.nanoTime());
        }
        catch (InterruptedException e) {
            System.out.println("WARNING: frame sync failed");
        }
    }

    private void onWindowClose() {
        setGameExit();
        try {
            mRunThread.join();
        }
        catch (InterruptedException e) {
            System.out.println("FATAL: failed to terminate game main loop.");
        }
    }

    public static void main(String[] args)
    {
        EventQueue.invokeLater(() -> {
            Game game = new Game(args);
            game.run();
        });
    }
}

/* eof */
