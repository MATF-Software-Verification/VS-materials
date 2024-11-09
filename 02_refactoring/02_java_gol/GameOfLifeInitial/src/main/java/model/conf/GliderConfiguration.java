package model.conf;

public class GliderConfiguration implements Configuration {
    private final char[][] field;

    public GliderConfiguration() {
        field = new char[][] {
            { ' ', ' ', ' ', ' ', ' ' },
            { ' ', ' ', 'O', ' ', ' ' },
            { 'O', ' ', 'O', ' ', ' ' },
            { ' ', 'O', 'O', ' ', ' ' },
            { ' ', ' ', ' ', ' ', ' ' },
        };
    }

    @Override
    public boolean isCellAliveAt(int x, int y) {
        if ((x >= 0 && x < field.length) && (y >= 0 && y < field[0].length))
            return field[x][y] == 'O';
        return false;
    }
}
