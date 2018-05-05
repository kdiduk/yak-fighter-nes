package com.kdiduk.yakfighter;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.EventQueue;
import java.util.concurrent.TimeUnit;
import javax.swing.JComponent;
import javax.swing.JFrame;

public class Game  {
    public static final short FRAMES_PER_SECOND = 60;
    public static final long MSECS_PER_FRAME = 1000 / FRAMES_PER_SECOND;
    public static final long NANOSECS_PER_FRAME = MSECS_PER_FRAME * 1000000;

    private JFrame mAppFrame = null;
    private ViewComponent mViewComponent = null;
    private Controller mController = new Controller();
    private Sprite mPlayer = null;
    private boolean mGameExit = false;
    private Thread mRunThread = null;

    public Game(String[] args) {
        mViewComponent = new ViewComponent(mController);
        mAppFrame = new JFrame("Yak Fighter");
        mAppFrame.add(mViewComponent);
        mAppFrame.setSize(800, 600);
        mAppFrame.setResizable(false);
        mAppFrame.setFocusable(true);
        mAppFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        mAppFrame.setIgnoreRepaint(true);
        mAppFrame.addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e) {
                onWindowClose();
            }
        });
        mAppFrame.setLocationRelativeTo(null);
        mAppFrame.setVisible(true);
        mRunThread = new Thread(() -> {
            mainLoop();
        });
        
        try {
            mPlayer = new Sprite();
            mViewComponent.addSprite(mPlayer);
        }
        catch (Exception e) {
        }
    }

    public void run() {
        mViewComponent.requestFocus();
        mRunThread.start();
    }

    public synchronized boolean isGameExit() {
        return mGameExit;
    }

    public synchronized void setGameExit() {
        mGameExit = true;
    }

    public void mainLoop() {
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

    public void join() {
        try {
            mRunThread.join();
        }
        catch (InterruptedException e) {
            System.out.println("FATAL: failed to terminate game main loop.");
        }
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

        mViewComponent.scrollBackground(1);
    }

    private void render() {
        mViewComponent.render();
    }

    private void syncFrame(long startTime) {
        try {
            long endTime = startTime + NANOSECS_PER_FRAME;
            long now = System.nanoTime();
            if (endTime > now) {
                TimeUnit.NANOSECONDS.sleep(endTime - now);
            }
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
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {

                Game game = new Game(args);
                game.run();
            }
        });
    }
}

/* eof */
