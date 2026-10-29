package com.company;
public class SudokuDisplay { //class extracted from primary Sudoku class
    private int[][] board = new int[9][9];
    private int[][] usrBoard = new int[9][9];

    public SudokuDisplay(Sudoku sudoku){
        this.board= sudoku.getBoard();
        this.usrBoard=sudoku.getUsrBoard();
    }
    @Override
    public String toString() { //formats the board based on the board array directly, replacing zeros with dashes.
        StringBuilder result = new StringBuilder();
        result.append("    A B C   D E F   G H I\n");
        for (int i = 0; i < board.length; i++) {
            if (i == 0 || i == 3 || i == 6) {
                result.append("  " + repeat("-", 25) + "\n");
            }
            for (int j = 0; j < board[i].length; j++) {
                if (j == 3 || j == 6) {
                    result.append("| " + board[i][j] + " ");
                }
                else if (j == 0) {
                    result.append((i + 1) + " | " + board[i][j] + " ");
                }
                else if (j == board[i].length - 1) {
                    result.append(board[i][j] + " |\n");
                }
                else {
                    result.append(board[i][j] + " ");
                }
            }
        }
        result.append("  " + repeat("-", 25));
        String finalResult = result.toString().replaceAll("0", "-");
        return finalResult;
    }
    public String output() { //formats the board by checking both board and usrBoard, prioritizing values from board but falling back on usrBoard if board has a zero. It also replaces zeros with dashes.
        StringBuilder result = new StringBuilder();
        int blockValue;
        result.append("    A B C   D E F   G H I\n");
        for (int i = 0; i < board.length; i++) {
            if (i == 0 || i == 3 || i == 6) {
                result.append("  " + repeat("-", 25) + "\n");
            }
            for (int j = 0; j < board[i].length; j++) {
                if (board[i][j] > 0) {
                    blockValue = board[i][j];
                }
                else {
                    if (usrBoard[i][j] > 0) {
                        blockValue = usrBoard[i][j];
                    }
                    else {
                        blockValue = 0;
                    }
                }
                if (j == 3 || j == 6) {
                    result.append("| " + blockValue + " ");
                }
                else if (j == 0) {
                    result.append((i + 1) + " | " + blockValue + " ");
                }
                else if (j == board[i].length - 1) {
                    result.append(blockValue + " |\n");
                }
                else {
                    result.append(blockValue + " ");
                }
            }
        }
        result.append("  " + repeat("-", 25));
        String finalResult = result.toString().replaceAll("0", "-");
        return finalResult;
    }
    private String repeat(String s, int n) {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < n; i++) {
            builder.append(s);
        }
        return builder.toString();
    }
    public String getBoardAsString() {
        int counter = 0;
        String result = "";
        for (int i = 0; i < this.board.length; i++) {
            for (int j = 0; j < this.board[i].length; j++) {
                counter++;
                result += board[i][j];
                if (counter % 3 == 0 && counter != 81) {
                    result += " ";
                }
            }
        }
        return result;
    }

}
