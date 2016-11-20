import java.util.Observable;

/**
 * Created by David on 12/11/2016.
 */
public class Ball extends Observable {
    private int x,y;
    private int vx,vy;
    private int r;

    public Ball(int x, int y) {
        this.x = x;
        this.y = y;
        this.vx = 1;
        this.vy = 1;
        this.r = 500;
    }

    public void update() {
        this.x += vx;
        this.y += vy;
        setChanged();
        notifyObservers(this);
    }

    public void invertVx() { this.vx *= -1; }
    public void invertVy() { this.vy *= -1; }

    public int getX() { return this.x; }
    public int getY() { return this.y; }
    public int getRadius() { return this.r; }



}
