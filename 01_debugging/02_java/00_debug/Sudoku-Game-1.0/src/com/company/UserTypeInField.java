package com.company;

import jdk.swing.interop.SwingInterOpUtils;

import java.util.Scanner;

public class UserTypeInField { //class extracted from primary Main class

    public static boolean parseAdd(SudokuWrapper usrSudokuWrapper,String str) {
        Scanner scanner = new Scanner(System.in);
        if (str.matches("[A-I][1-9]")) {
            int colASCII = (int)str.charAt(0);
            int rowASCII = (int)str.charAt(1);
            System.out.println("\nNow type in the value...");
            int usrValue = scanner.nextInt();
            if (usrValue <= 9 && usrValue >= 1) {
                if (usrSudokuWrapper.sudoku.add(colASCII - 65, rowASCII - 49, usrValue)) {
                    System.out.println("Successfully added " + usrValue + " to " + str + "\n");
                    SudokuDisplay display=new SudokuDisplay(usrSudokuWrapper.sudoku);
                    System.out.println(display.output());
                    return true;
                }
            }
        }
        else {   //why is this else here? It's going to return false either way :)
            return false;
        }
        return false;
    }
}
