package tests;

import model.*;
import model.conf.*;

import org.junit.*;

public class GameOfLifeTests {

  private static class TestConfiguration extends ManualConfiguration {
    public TestConfiguration() {
      super(new char[][] {
      { ' ', ' ', ' ', ' ', ' ' },
      { ' ', 'O', 'O', ' ', 'O' },
      { 'O', ' ', 'O', ' ', ' ' },
      { ' ', 'O', 'O', ' ', ' ' },
      { ' ', ' ', ' ', ' ', ' ' },
      });
    }
  }

  @Test
  public void testConfiguration() {
    var conf = new TestConfiguration();
    Assert.assertTrue(conf.isCellAliveAt(1, 1));
    Assert.assertTrue(conf.isCellAliveAt(1, 2));
    Assert.assertFalse(conf.isCellAliveAt(1, 3));
    // ...
  }

}
