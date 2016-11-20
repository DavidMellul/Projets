import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

/**
 * Created by David on 19/11/2016.
 */
public class Fenetre extends JFrame {
    public Fenetre() {
        super();
        this.initializeComponents();
    }

    private void initializeComponents() {
        this.setTitle("Triangle de Sierpinski - David Mellul");
        this.setSize(new Dimension(650,560));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch(e.getKeyCode()) {
                    case KeyEvent.VK_ESCAPE:
                        Fenetre.this.dispose();
                        break;
                    default: break;
                }
            }
        });
        this.setVisible(true);
    }

    private void Sierpinski(Graphics g, Point p1, Point p2, Point p3, int taille) {
        if(taille <= 1) {
            Polygon p = new Polygon();
            p.addPoint(p1.x,p1.y);
            p.addPoint(p2.x,p2.y);
            p.addPoint(p3.x,p3.y);
            g.fillPolygon(p);
        }
        else {
            Point P1 = Milieu(p1,p2);
            Point P2 = Milieu(p2,p3);
            Point P3 = Milieu(p3,p1);

            Sierpinski(g,p1,P1,P3,taille-1);
            Sierpinski(g,P1,p2,P2,taille-1);
            Sierpinski(g,P3,P2,p3,taille-1);
        }
    }

    private Point Milieu(Point p1, Point p2) {
        return new Point((p1.x+p2.x)/2,(p1.y+p2.y)/2);
    }

    public void paint(Graphics g) {
        Point p1 = new Point(10, (int) (640*Math.sqrt(3.0)/2.0));
        Point p2 = new Point(320, 30);
        Point p3 = new Point(640, (int)(640*Math.sqrt(3.0)/2.0));
        Sierpinski(g,p1,p2,p3,5);
    }
}
