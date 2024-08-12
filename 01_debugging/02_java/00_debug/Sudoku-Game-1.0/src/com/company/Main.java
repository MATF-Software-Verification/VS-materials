package com.company;

import java.util.ArrayList;
import java.util.Scanner;

import static com.company.UserChoosingDifficulty.difficulty;
import static com.company.UserTypeInField.parseAdd;
public class Main {
    public static void main(String[] args) {
        play();
    }

    private static void displayMenu() {
        System.out.println("\n1. Fill in a value...\n2. Undo last move...\n3. I give up. Show me the solution!\n4. Quit");
    }

    private static void play() {
        SudokuWrapper usrSudokuWrapper = new SudokuWrapper(null);
        Scanner scanner = new Scanner(System.in);
        boolean endGame;
        int diffReturn;
        String location = "";
        boolean parseAddReturn;
        ArrayList<String> undoList = new ArrayList<String>();
        while ((diffReturn = difficulty(usrSudokuWrapper)) != 0) {
            endGame = false;
            if (diffReturn == 1) {
                while (!endGame) {
                    displayMenu();
                    String usrChoice = scanner.next();
                    if (usrChoice.equals("1")) {
                        System.out.println("\nType in the location to fill in...");
                        location = scanner.next().toUpperCase();
                        parseAddReturn = parseAdd(usrSudokuWrapper,location);
                        boolean solvedStatus = usrSudokuWrapper.sudoku.isSolved();
                        if (solvedStatus) {
                            System.out.println("\nYou Won!");
                            endGame = true;
                        }
                        if (!parseAddReturn) {
                            System.out.println("Can't fill this value in this place, try again...");
                            SudokuDisplay display=new SudokuDisplay(usrSudokuWrapper.sudoku);
                            System.out.println(display.output());
                        }
                        else {
                            undoList.add(location);
                        }
                    }
                    else if (usrChoice.equals("2")) {
                        int index = undoList.size() - 1;
                        if (index >= 0) {
                            String obj = undoList.get(index);
                            if (obj.matches("[A-I][1-9]")) {
                                usrSudokuWrapper.sudoku.remove((int)obj.charAt(0) - 65, (int)obj.charAt(1) - 49);
                                SudokuDisplay display=new SudokuDisplay(usrSudokuWrapper.sudoku);
                                System.out.println(display.output());
                                undoList.remove(index);
                            }
                        }
                        else {
                            System.out.println("Can't undo...");
                        }
                    }
                    else if (usrChoice.equals("3")) {
                        usrSudokuWrapper.sudoku.solve();
                        SudokuDisplay display=new SudokuDisplay(usrSudokuWrapper.sudoku);
                        System.out.println(display.toString());
                        endGame = true;
                    }
                    else if (usrChoice.equals("4")) {
                        System.out.println("Quitting to difficulty selection...");
                        endGame = true;
                    }
                    else {
                        System.out.println("Invalid input, try again...");
                        endGame = false;
                    }
                }
            }
        }
    }
}
