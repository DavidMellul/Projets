import java.util.ArrayList;
import java.util.Random;

/**
 * Created by David on 01/11/2016.
 */
public class Snake {
    private SnakeNode head;
    private ArrayList<SnakeNode> listNodes;
    private char direction;
    private static int VX = SnakeNode.getW(), VY = SnakeNode.getH();

    public Snake()
    {
        this.head = new SnakeNode();
        this.listNodes = new ArrayList<SnakeNode>();
        int n = new Random().nextInt(3);
        this.direction = (n == 0) ? 'U':(n == 1) ? 'D':(n == 2) ? 'L':'R';
        this.addNode();this.addNode();this.addNode();
    }

    public SnakeNode getHead() {
        return head;
    }

    public void setHead(SnakeNode head) {
        this.head = head;
    }

    public ArrayList<SnakeNode> getListNodes() {
        return listNodes;
    }

    public void addNode()
    {
        SnakeNode lastNode = (this.listNodes.size() == 0) ? this.head:this.listNodes.get(this.listNodes.size()-1);
        int x = 0, y = 0;
        switch(this.direction)
        {
            case 'U':
                x = lastNode.getX();
                y = lastNode.getY()+SnakeNode.getH();
                break;
            case 'D':
                x = lastNode.getX();
                y = lastNode.getY()-SnakeNode.getH();
                break;
            case 'L':
                x = lastNode.getX()-SnakeNode.getW();
                y = lastNode.getY();
                break;
            case 'R':
                x = lastNode.getX()+SnakeNode.getW();
                y = lastNode.getY();
                break;

        }
        this.listNodes.add(new SnakeNode(x,y));
    }

    public void setDirection(char direction) {
        this.direction = (direction != this.direction && direction != this.getOppositeDirection()) ? direction:this.direction;
    }

    private char getOppositeDirection()
    {
        if(this.direction == 'U')
            return 'D';
        else if(this.direction == 'D')
            return 'U';
        else if(this.direction == 'L')
            return 'R';
        else if(this.direction == 'R')
            return 'L';

        return ' ';
    }

    public void update()
    {

        ArrayList<SnakeNode> listTemp = (ArrayList<SnakeNode>) listNodes.clone();
        for(int i = this.listNodes.size()-1; i > 0; i--)
        {
            SnakeNode sn1 = listTemp.get(i-1);
            SnakeNode sn2 = this.listNodes.get(i);
            sn2.setPosition(sn1.getX(),sn1.getY());
        }
        this.listNodes.get(0).setPosition(this.head.getX(), this.head.getY());

        switch(direction)
        {
            case 'U':
                this.head.setY(this.head.getY()-VY);
                break;
            case 'D':
                this.head.setY(this.head.getY()+VY);
                break;
            case 'L':
                this.head.setX(this.head.getX()-VX);
                break;
            case 'R':
                this.head.setX(this.head.getX()+VX);
                break;
        }
    }

}
