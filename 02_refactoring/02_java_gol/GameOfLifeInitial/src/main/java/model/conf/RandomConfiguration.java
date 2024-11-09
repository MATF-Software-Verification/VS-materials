package model.conf;

import java.util.Random;

public class RandomConfiguration implements Configuration{
    private final Random rng = new Random();

    @Override
    public boolean isCellAliveAt(int x, int y) {
        return rng.nextBoolean();
    }
}
