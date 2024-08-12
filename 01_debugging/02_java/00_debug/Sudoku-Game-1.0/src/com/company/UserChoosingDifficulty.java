package com.company;

import java.util.Scanner;
public class UserChoosingDifficulty { //class extracted from primary Main class
    private static Sudoku easy = new Sudoku("165 794 038 407 002 050 930 006 004 810 405 002 576 239 400 200 601 075 301 507 849 690 000 527 050 028 103");
    private static Sudoku medium = new Sudoku("980 254 000 640 073 200 020 000 900 030 000 006 060 000 090 700 642 803 400 026 010 390 008 402 172 000 000");
    private static Sudoku hard = new Sudoku("600 500 073 500 002 004 001 003 580 903 080 705 850 037 020 076 050 000 087 300 250 010 470 006 360 821 000");
    private static Sudoku expert = new Sudoku("000 970 800 300 005 640 000 060 031 035 040 000 209 007 310 070 030 490 420 006 000 051 304 009 003 000 500");

    public static int difficulty(SudokuWrapper usrSudokuWrapper) { //if-else is refactored because of the class SudokuDisplay (which is refactored/extracted from Sudoku class)
        Scanner scanner = new Scanner(System.in);
        int result = 1;
        System.out.println("\n1. Easy...\n2. Medium... \n3. Hard... \n4. Expert... \n5. Exit game...");
        String usrChoice = scanner.next().toLowerCase();
        SudokuDisplay display=null;
        if (usrChoice.equals("1")) {
            display=new SudokuDisplay(easy);
        } else if (usrChoice.equals("2")) {
            display=new SudokuDisplay(medium);
        } else if (usrChoice.equals("3")) {
            display=new SudokuDisplay(hard);
        } else if (usrChoice.equals("4")) {
            display=new SudokuDisplay(expert);
        } else if (usrChoice.equals("5")) {
            System.out.println("Exiting the game......");
            result = 0;
        } else {
            System.out.println("Invalid difficulty selection, try again...");
            result = -1;
        }
        if (result==1){ //this if is added because of the variable result logic
            System.out.println(display.toString());
            usrSudokuWrapper.sudoku = new Sudoku(display.getBoardAsString());
        }
        return result;
    }

}
