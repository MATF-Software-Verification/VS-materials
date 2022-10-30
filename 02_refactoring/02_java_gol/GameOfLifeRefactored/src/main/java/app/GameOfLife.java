package app;

import model.Grid;
import model.conf.Configuration;
import model.conf.RandomConfiguration;
import model.conf.predefined.GliderConfiguration;
import view.ConsoleView;
import view.View;

public class GameOfLife {
    private  static  final int dim = 10;

    public static void main(String[] args) throws InterruptedException {
        Configuration c = new GliderConfiguration();
//        Configuration c = new RandomConfiguration();
        View v = new ConsoleView();
        Grid g = new Grid(c, dim);
        runGame(g, v);
    }

    private static void runGame(Grid g, View v) throws InterruptedException {
        while (true) {
            g.advance();
            v.drawGrid(g);
            Thread.sleep(500);
        }
    }
}
