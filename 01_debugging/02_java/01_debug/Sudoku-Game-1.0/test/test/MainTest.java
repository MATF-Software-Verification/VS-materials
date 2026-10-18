package test;

import com.company.Main;
import com.company.SudokuWrapper;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.PrintStream;

import static com.company.UserChoosingDifficulty.difficulty;
import static org.junit.jupiter.api.Assertions.*;

class MainTest {
    private final InputStream originalSystemIn = System.in;
    private final PrintStream originalSystemOut = System.out;
    private ByteArrayInputStream testIn;
    private ByteArrayOutputStream testOut;

    @BeforeEach
    public void setUp() {
        testOut = new ByteArrayOutputStream();
        System.setOut(new PrintStream(testOut));
    }

    @AfterEach
    public void restoreSystem() {
        System.setIn(originalSystemIn);
        System.setOut(originalSystemOut);
    }

    public void setUpInput(String input) {
        testIn = new ByteArrayInputStream(input.getBytes());
        System.setIn(testIn);
    }

    @Test
    public void testDifficultyEasy() {
        // Setup fake input
        setUpInput("1\n");

        // Act
        int result = difficulty(new SudokuWrapper(null));

        // Assert
        assertEquals(1, result);
    }

    @Test
    public void testPlay(){
        // Setup fake input
        String simulatedInput="1\r\n1\r\nA9\r\n7\r\n";
        setUpInput(simulatedInput);

        // Act
        Main.main(null);

        // Assert
        assertTrue(testOut.toString().contains("Successfully added 7 to A9"));
    }

}