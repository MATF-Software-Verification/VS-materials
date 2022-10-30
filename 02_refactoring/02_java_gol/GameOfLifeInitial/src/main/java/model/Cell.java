package model;

public class Cell {
    private final int x, y;
    private boolean isAlive;
    private int numOfNeighbours;

    public Cell(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void kill(){
        isAlive = false;
    }

    public void resurrect(){
        isAlive = true;
    }

    public boolean isAlive() {
        return isAlive;
    }

    public int getNumOfNeighbours() {
        return numOfNeighbours;
    }

    public void incrementNumOfNeigbours() {
        this.numOfNeighbours++;
    }

    public void decrementNumOfNeigbours() {
        this.numOfNeighbours--;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
