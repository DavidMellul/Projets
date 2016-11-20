import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferInt;
import java.util.ArrayList;
import java.util.Observable;
import java.util.Observer;
import java.util.Random;


/**
 * Created by David on 12/11/2016.
 */
public class Window extends JFrame implements Observer{
    private ArrayList<Ball> listBalls = new ArrayList<Ball>();
    private static int WIDTH = 640;
    private static int HEIGHT= 320;
    private BufferedImage screen = new BufferedImage(WIDTH,HEIGHT, BufferedImage.TYPE_INT_RGB);
    int[] screenPixels = ((DataBufferInt)screen.getRaster().getDataBuffer()).getData();
    private boolean started;

    public Window()  {
        super();
        this.setUndecorated(true);
        this.initializeComponents();
        new MyThread().start();
        this.started = true;
        try {
            Robot r = new Robot();
            for(int i = 0; i < 5; i++) {
                r.keyPress(KeyEvent.VK_SPACE);
                r.keyRelease(KeyEvent.VK_SPACE);
            }
        } catch (AWTException e) {
            e.printStackTrace();
        }

    }

    private void initializeComponents() {
        this.setTitle("MetaBalls - David Mellul");
        this.setSize(new Dimension(WIDTH,HEIGHT));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch(e.getKeyCode()) {
                    case KeyEvent.VK_SPACE:
                        int randX = new Random().nextInt(WIDTH);
                        int randY = new Random().nextInt(HEIGHT);
                        listBalls.add(new Ball(randX,randY));
                        listBalls.get(listBalls.size()-1).addObserver(Window.this);
                        break;
                    case KeyEvent.VK_ESCAPE:
                        started = false;
                        Window.this.dispose();
                        break;
                    case KeyEvent.VK_R:
                        listBalls.clear();
                        break;
                    case KeyEvent.VK_D:
                        if(listBalls.size() > 0)
                            listBalls.remove(listBalls.size()-1);
                        break;
                }
            }
        });
        this.setVisible(true);
    }

    @Override
    public void paint(Graphics g) {
        if (this.listBalls.size() > 0) {
            for (int i = 0; i < WIDTH; i++) {
                for (int j = 0; j < HEIGHT; j++) {
                    int sum = 0;
                    for(Ball b : listBalls) {
                        double d = distance(i, j, b.getX(), b.getY());
                        sum += 1000*b.getRadius() / d;
                    }
                    if(sum > 255) sum = 255;
                    if(sum == 255 || sum < 150)
                        screenPixels[i+j*WIDTH] = (sum<<16) | (sum<<8) | (sum) ;
                    else if(sum < 255 && sum >= 150)
                        screenPixels[i+j*WIDTH] = (sum<<16) | (sum<<8) | (255) ;

                }
            }
            g.drawImage(screen, 0, 0, null);
        }
        else {
            g.setColor(Color.BLACK);
            g.fillRect(0,0,WIDTH,HEIGHT);
        }
    }

    @Override
    public void update(Observable o, Object arg) {
        collidesWithBorders((Ball)o);
    }

    class MyThread extends Thread {
        @Override
        public void run() {
            while (started) {
                try {
                    sleep(5);
                    for (Ball b : listBalls) {
                        b.update();
                    }
                    repaint();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    private double distance(int x1, int y1, int x2, int y2) {
        double d =  ((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)) ;
        return d; //We don't make use of sqrt, since it costs a lot of CPU time
    }

    private void collidesWithBorders(Ball b) {
        if(b.getX() >= WIDTH) b.invertVx();
        if(b.getY() >= HEIGHT) b.invertVy();
        if(b.getX() <= 0) b.invertVx();
        if(b.getY() <= 0) b.invertVy();
    }
}
