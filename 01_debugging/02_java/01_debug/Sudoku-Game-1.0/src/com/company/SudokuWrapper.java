package com.company;

public class SudokuWrapper { //this class is a consequence of refactoring. I need usrSudoku to be updated in UserChoosingDifficulty and be passed to Main method
    public Sudoku sudoku;

    public SudokuWrapper(Sudoku sudoku) {
        this.sudoku = sudoku;
    }
}
