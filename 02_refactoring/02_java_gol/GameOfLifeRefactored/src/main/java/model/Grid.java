package model;

import model.conf.Configuration;

import java.util.ArrayList;
import java.util.List;

public class Grid {
    private final Cell[][] field;
    private final Configuration conf;

    public Grid(Configuration conf, int dim) {
        this.conf = conf;
        field = createGrid(dim + 2 , dim + 2);
        initializeGrid();
    }

    public Grid(Configuration conf, int width, int height) {
        this.conf = conf;
        field = createGrid(width + 2, height + 2);
        initializeGrid();
    }

    private Cell[][] createGrid(int width, int height) {
        Cell[][] newGrid = new Cell[height][width];
        for (int i = 1; i < height - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                newGrid[i][j] = new Cell(i - 1, j - 1);
                if (conf.isCellAliveAt(i - 1, j - 1))
                    newGrid[i][j].resurrect();
                else
                    newGrid[i][j].kill();
            }
        }
        return newGrid;
    }

    private void initializeGrid() {
        for (int i = 1; i < getHeight() - 1; i++) {
            for (int j = 1; j < getWidth() - 1; j++) {
                Cell[] neighbours = getNeigboursForCell(field[i][j]);
                for (Cell neighbour : neighbours)
                    neighbour.incrementNumOfNeigbours();
            }
        }
    }

    public int getHeight(){
        return field.length - 2;
    }

    public int getWidth(){
        return field[0].length - 2;
    }

    public Cell cellAt(int x, int y){
        //TODO check range
        return field[x+1][y+1];
    }

    public void advance() {
        /*
         * Any live cell with two or three live neighbours survives.
         * Any dead cell with three live neighbours becomes a live cell.
         * All other live cells die in the next generation. Similarly, all other dead cells stay dead.
         */
        for (int i = 1; i < getHeight() - 1; i++) {
            for (int j = 1; j < getWidth() - 1; j++) {
                Cell current = field[i][j];
                Cell[] neighbours = getNeigboursForCell(current);
                int aliveNeighbours = 0;
                for (Cell neighbour : neighbours) {
                    if (neighbour.isAlive())
                        aliveNeighbours++;
                }
                if (!current.isAlive() && aliveNeighbours == 3) {
                    current.resurrect();
                    for (Cell neighbour : neighbours)
                        neighbour.incrementNumOfNeigbours();
                } else if (current.isAlive() && (aliveNeighbours < 2 || aliveNeighbours > 3)) {
                    current.kill();
                    for (Cell neighbour : neighbours)
                        neighbour.decrementNumOfNeigbours();
                }
            }
        }
    }

    public Cell[] getNeigboursForCell(Cell c){
        List<Cell> neigbours = new ArrayList<>();
        for (int i = c.getX() - 1; i <= c.getX() + 1; i++){
            for (int j = c.getY() - 1; j <= c.getY() + 1; j++){
                Cell neighbour = cellAt(i, j);
                if (neighbour != null && c != neighbour)
                    neigbours.add(neighbour);
            }
        }
        return neigbours.toArray(new Cell[0]);
    }
}
