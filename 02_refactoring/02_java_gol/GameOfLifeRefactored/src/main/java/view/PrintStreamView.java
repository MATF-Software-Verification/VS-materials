package view;

import model.Grid;

import java.io.PrintStream;

public interface PrintStreamView extends View {
    void drawGrid(Grid grid, PrintStream out);

    @Override
    default void drawGrid(Grid grid) {
        drawGrid(grid, System.out);
    }
}
