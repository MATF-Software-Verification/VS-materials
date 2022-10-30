package app;

import model.Cell;
import model.Grid;
import model.conf.Configuration;
import model.conf.GliderConfiguration;
import utils.Console;

import java.util.Arrays;

public class GameOfLife {
    private  static  final int dim = 10;

    public static void main(String[] args) throws InterruptedException {
        Configuration c = new GliderConfiguration();
//        Configuration c = new RandomConfiguration();
        Grid g = new Grid(c, dim);
        runGame(g);
    }

    private static void runGame(Grid g) throws InterruptedException {
        while (true){
            g.advance();
            drawGrid(g);
            Thread.sleep(500);
        }
    }

    private static void drawGrid(Grid grid) {
        int w = grid.getWidth();
        int h = grid.getHeight();

        Console.clear();
        char[] str = new char[w];
        Arrays.fill(str, '_');
        System.out.println(new String(str));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                Cell c = grid.cellAt(i, j);
                if (c.isAlive())
                    System.out.print("O");
                else
                    System.out.print(" ");
            }
            System.out.println();
        }
        System.out.println(new String(str));
    }
}
