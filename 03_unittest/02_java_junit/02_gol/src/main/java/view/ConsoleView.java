package view;

import model.Cell;
import model.Grid;
import utils.Console;

import java.io.PrintStream;
import java.util.Arrays;

public class ConsoleView implements PrintStreamView {
    @Override
    public void drawGrid(Grid grid, PrintStream out) {
        int w = grid.getWidth();
        int h = grid.getHeight();

        clear();
        char[] str = new char[w];
        Arrays.fill(str, '_');
        out.println(new String(str));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                Cell c = grid.cellAt(i, j);
                if (c.isAlive())
                    out.print("O");
                else
                    out.print(" ");
            }
            out.println();
        }
        out.println(new String(str));
    }

    @Override
    public void clear() {
        Console.clear();
    }
}
