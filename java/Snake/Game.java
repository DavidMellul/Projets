import sun.awt.FontDescriptor;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.Iterator;
import java.util.Random;

/**
 * Created by David on 01/11/2016.
 */
public class Game extends JFrame {
    Snake snake;
    FoodNode food;

    private static int width = 1240, height = 720;
    public Game()
    {
        super();

        this.snake = new Snake();
        this.snake.setHead(new SnakeNode(width/2,height/2));
        this.food = new FoodNode(new Random().nextInt(width-FoodNode.getW()), new Random().nextInt(height- FoodNode.getH()));
        this.initializeComponents();
    }

    private void initializeComponents()
    {
        this.setTitle("Snake - David Mellul");
        this.setSize(new Dimension(width,height));
        this.setLocationRelativeTo(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.addKeyListener(new KeyAdapter() {
            public void keyPressed(KeyEvent e) {
                switch(e.getKeyCode())
                {
                    case KeyEvent.VK_UP:
                        snake.setDirection('U');
                        break;
                    case KeyEvent.VK_DOWN:
                        snake.setDirection('D');
                        break;
                    case KeyEvent.VK_LEFT:
                        snake.setDirection('L');
                        break;
                    case KeyEvent.VK_RIGHT:
                        snake.setDirection('R');
                        break;
                    case KeyEvent.VK_R:
                        food.setPosition(new Random().nextInt(width-FoodNode.getW()), new Random().nextInt(height- FoodNode.getH()));
                        break;
                    case KeyEvent.VK_T:
                        snake = new Snake();
                        snake.setHead(new SnakeNode(width/2,height/2));
                        food.setPosition(new Random().nextInt(width-FoodNode.getW()), new Random().nextInt(height- FoodNode.getH()));
                        break;
                }
            }
        });

        getRootPane().getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(
                KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0), "Quit");
        getRootPane().getActionMap().put("Quit", new AbstractAction()
        {
            public void actionPerformed(ActionEvent e)
            {
                System.exit(0);
            }
        });

        this.setVisible(true);
        new Thread(new Updater()).start();
    }

    public void paint(Graphics g)
    {
        g.setColor(Color.black);
        g.fillRect(0,0,width,height);

        g.setColor(Color.white);
            g.fillRect(this.snake.getHead().getX(),this.snake.getHead().getY(),this.snake.getHead().getW(),this.snake.getHead().getH());
        g.setColor(Color.red);
            for(SnakeNode sn : this.snake.getListNodes())
                g.fillRect(sn.getX(),sn.getY(),sn.getW(),sn.getH());

        g.setColor(Color.green);
            g.fillRect(food.getX(),food.getY(),FoodNode.getW(), FoodNode.getH());

        g.setColor(Color.white);
            g.drawString("Score "+(snake.getListNodes().size()-3)*10,100,100);
    }

    public synchronized void checkCollisions()
    {
        if(this.snake.getHead().intersects(food))
        {
            food.setPosition(new Random().nextInt(width-FoodNode.getW()), new Random().nextInt(height- FoodNode.getH()));
            this.snake.addNode();
        }

        if(snake.getListNodes().size() > 3)
            for(int i = 3; i < snake.getListNodes().size(); i++)
            {
                if(snake.getHead().intersects(snake.getListNodes().get(i)))
                {
                    snake = new Snake();
                    this.snake.setHead(new SnakeNode(width/2,height/2));
                    food.setPosition(new Random().nextInt(width-FoodNode.getW()), new Random().nextInt(height- FoodNode.getH()));
                }
            }
    }

    public class Updater implements Runnable {
        public Updater() {}
        public void run() {
            while(true)
            {
                try {
                    repaint();
                    checkCollisions();
                    snake.update();
                    Thread.sleep(15);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

}
