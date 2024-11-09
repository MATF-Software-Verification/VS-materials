package model.conf;

public abstract class ManualConfiguration implements Configuration {
    private final char[][] field;

    public ManualConfiguration(char[][] field) {
        this.field = field;
    }

    @Override
    public boolean isCellAliveAt(int x, int y) {
        if ((x >= 0 && x < field.length) && (y >= 0 && y < field[0].length))
            return field[x][y] == 'O';
        return false;
    }
}
