import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class Fenetre extends JFrame {

    public Fenetre() {
        super();
        this.initializeComponents();
    }

    private void initializeComponents() {
        this.setTitle("Éponge de Menger - David Mellul");
        this.setSize(new Dimension(750,770));
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                switch (e.getKeyCode()) {
                    case KeyEvent.VK_ESCAPE:
                        Fenetre.this.dispose();
                        break;

                    default: break;
                }
            }
        });
        this.setVisible(true);
        this.repaint();
    }

    public void Menger(Graphics g, int x, int y, int taille) {
        if(taille <= 1)
            g.drawLine(x,y,x,y);
        else {
            Menger(g,x,y,taille/3); //1
            Menger(g,x+taille/3,y,taille/3); //2
            Menger(g,x+2*taille/3,y,taille/3); //3
            Menger(g,x,y+taille/3,taille/3); //4
            Menger(g,x+2*taille/3,y+taille/3,taille/3); //5
            Menger(g,x,y+2*taille/3,taille/3); //6
            Menger(g,x+taille/3,y+2*taille/3,taille/3); //7
            Menger(g,x+2*taille/3,y+2*taille/3,taille/3); //8
        }
    }

    public void paint(Graphics g) {
        Menger(g,10,30, (int) Math.pow(3,6));
    }
}
