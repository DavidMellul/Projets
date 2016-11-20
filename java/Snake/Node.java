/**
 * Created by David on 01/11/2016.
 */
public abstract  class Node {
    private int x,y;
    private static int w = 15 , h = 15;

    public Node()
    {
        this.x = 0;
        this.y = 0;
    }

    public Node(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public int getX()
    {
        return this.x;
    }

    public void setX(int x)
    {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void setPosition(int x, int y)
    {
        this.x = x;
        this.y = y;
    }

    public static int getW() {
        return w;
    }

    public static int getH() {
        return h;
    }

    public boolean intersects(Node n)
    {
        int x1 = this.getX(), x2 = this.getX()+this.getW();
        int x3 = n.getX(), x4 = n.getX()+n.getW();
        int y1 = this.getY(), y2 = this.getY()+this.getH();
        int y3 = n.getY(), y4 = n.getY()+n.getH();

        if( (x1 >= x4) || (x2 <= x3) || (y1 >= y4) || (y2 <= y3) )
            return false;
        return true;
    }
}
