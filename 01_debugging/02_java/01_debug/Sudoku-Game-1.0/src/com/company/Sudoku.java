package com.company;

public class Sudoku{
    private int[][] board = new int[9][9];
    private int[][] usrBoard = new int[9][9];
    private boolean[][] analyzedRow = new boolean[9][9];
    private boolean[][] analyzedCol = new boolean[9][9];
    private boolean[][][] analyzedCell = new boolean[3][3][9];
    private boolean[][] solvedCell = new boolean[3][3];
    private boolean[] solvedRow = new boolean[9];
    private boolean[] solvedCol = new boolean[9];

    //konstruktor
    public Sudoku(String values) {
        board = parseString(values);
    }

    private int[][] parseString(String string) {
        int counter = -1;
        String replacedString = string.replaceAll("\\W", "");
        for (int i = 0; i < this.board.length; i++) {
            for (int j = 0; j < this.board[i].length; j++) {
                counter++;
                this.board[i][j] = replacedString.charAt(counter) - '0';
            }
        }
        return this.board;
    }

    public int[][] getBoard() {
        return this.board;
    }
    public int[][] getUsrBoard() {
        return this.usrBoard;
    } //added because of refactoring --> SudokuDisplay


    private boolean presentInRow(int value, int row) {
        int[] rowArray = this.board[row];
        for (int i = 0; i < rowArray.length; i++) {
            if (value == rowArray[i]) {
                return true;
            }
        }
        return false;
    }

    private boolean presentInCol(int value, int col) {
        int[] columnArray = new int[9];
        for (int i = 0; i < 9; i++) {
            columnArray[i] = this.board[i][col];
        }
        for (int i = 0; i < 9; i++) {
            if (value == columnArray[i]) {
                return true;
            }
        }
        return false;
    }

    private boolean presentInCell(int value, int col, int row) {
        int[] cellArray = new int[9];
        int celCol = col / 3;
        int celRow = row / 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cellArray[i * 3 + j] = this.board[celRow * 3 + i][celCol * 3 + j];
            }
        }
        for (int i = 0; i < cellArray.length; i++) {
            if (value == cellArray[i]) {
                return true;
            }
        }
        return false;
    }

    private void analyzeRow() {
        int value;
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                value = this.board[row][col];
                if (value > 0 && value <= 9) {
                    this.analyzedRow[row][value - 1] = true;
                }
            }
        }
    }

    private void analyzeCol() {
        int value;
        for (int col = 0; col < 9; col++) {
            for (int row = 0; row < 9; row++) {
                value = this.board[row][col];
                if (value > 0 && value <= 9) {
                    this.analyzedCol[col][value - 1] = true;
                }
            }
        }
    }

    private void analyzeCell() {
        int value;
        for (int cellRow = 0; cellRow < 3; cellRow++) {
            for (int cellCol = 0; cellCol < 3; cellCol++) {
                for (int i = 0; i < 9; i++) {
                    value = this.board[cellRow * 3 + i / 3][cellCol * 3 + i % 3];
                    if (value > 0 && value <= 9) {
                        this.analyzedCell[cellRow][cellCol][value - 1] = true;
                    }
                }
            }
        }
    }

    private void updateAnalyzed(int value, int row, int col) {
        if (value >= 1 && value <= 9) {
            this.analyzedRow[row][value - 1] = true;
            this.analyzedCol[col][value - 1] = true;
            this.analyzedCell[row / 3][col / 3][value - 1] = true;
        }
    }

    private int findValue(boolean[] arr) {
        int counter = 0;
        int setValue = 0;
        for (int value = 1; value <= 9; value++) {
            if (!arr[value - 1]) {
                counter++;
                setValue = value;
            }
        }
        if (counter == 1) {
            return setValue;
        }
        else {
            return -1;
        }
    }

    private int findBlock(boolean[][] matrix, boolean[] doneBlocks, int value) {
        int counter = 0;
        int setBlock = 0;
        for (int i = 0; i < 9; i++) {
            if (!doneBlocks[i] && !matrix[i][value - 1]) {
                counter++;
                setBlock = i;
            }
        }
        if (counter == 1) {
            return setBlock;
        }
        else {
            return -1;
        }
    }

    private int findOnlyInCell(int cellRow, int cellCol) {
        boolean isUpdate = false;
        int solvedCounter = 0;
        int row;
        int col;
        int i;
        int value;
        int setValue;
        int setBlock;
        boolean[][] tmp = new boolean[9][9];
        boolean[] doneBlocks = new boolean[9];
        // Find the value for a certain block...
        for (i = 0; i < 9; i++) {
            row = cellRow * 3 + i / 3;
            col = cellCol * 3 + i % 3;
            if (this.board[row][col] == 0) {
                for (value = 1; value <= 9; value++) {
                    tmp[i][value - 1] = analyzedRow[row][value - 1] || analyzedCol[col][value - 1] || analyzedCell[cellRow][cellCol][value - 1];
                }
                setValue = findValue(tmp[i]);
                if (setValue != -1) {
                    this.board[row][col] = setValue;
                    updateAnalyzed(setValue, row, col);
                    isUpdate = true;
                }
            }
            else {
                solvedCounter++;
                doneBlocks[i] = true;
            }
        }
        // Find the block for a certain value...
        if (solvedCounter < 9) {
            for (value = 1; value <= 9; value++) {
                setBlock = findBlock(tmp, doneBlocks, value);
                if (setBlock != -1) {
                    row = cellRow * 3 + setBlock / 3;
                    col = cellCol * 3 + setBlock % 3;
                    this.board[row][col] = value;
                    updateAnalyzed(value, row, col);
                    isUpdate = true;
                }
            }
        }
        if (solvedCounter == 9) {
            return 0;
        }
        else {
            if (isUpdate) {
                return 1;
            }
            else {
                return -1;
            }
        }
    }

    private int findOnlyInRow(int row) {
        boolean isUpdate = false;
        int solvedCounter = 0;
        int col;
        int value;
        int setValue;
        int setBlock;
        boolean[][] tmp = new boolean[9][9];
        boolean[] doneBlocks = new boolean[9];
        // Find the value for a certain block...
        for (col = 0; col < 9; col++) {
            if (this.board[row][col] == 0) {
                for (value = 1; value <= 9; value++) {
                    tmp[col][value - 1] = analyzedRow[row][value - 1] || analyzedCol[col][value - 1] || analyzedCell[row / 3][col / 3][value - 1];
                }
                setValue = findValue(tmp[col]);
                if (setValue != -1) {
                    this.board[row][col] = setValue;
                    updateAnalyzed(setValue, row, col);
                    isUpdate = true;
                }
            }
            else {
                solvedCounter++;
                doneBlocks[col] = true;
            }
        }
        // Find the block for a certain value...
        if (solvedCounter < 9) {
            for (value = 1; value <= 9; value++) {
                setBlock = findBlock(tmp, doneBlocks, value);
                if (setBlock != -1) {
                    this.board[row][setBlock] = value;
                    updateAnalyzed(value, row, setBlock);
                    isUpdate = true;
                }
            }
        }
        if (solvedCounter == 9) {
            return 0;
        }
        else {
            if (isUpdate) {
                return 1;
            }
            else {
                return -1;
            }
        }
    }

    private int findOnlyInCol(int col) {
        boolean isUpdate = false;
        int solvedCounter = 0;
        int row;
        int value;
        int setValue;
        int setBlock;
        boolean[][] tmp = new boolean[9][9];
        boolean[] doneBlocks = new boolean[9];
        // Find the value for a certain block...
        for (row = 0; row < 9; row++) {
            if (this.board[row][col] == 0) {
                for (value = 1; value <= 9; value++) {
                    tmp[row][value - 1] = analyzedRow[row][value - 1] || analyzedCol[col][value - 1] || analyzedCell[row / 3][col / 3][value - 1];
                }
                setValue = findValue(tmp[row]);
                if (setValue != -1) {
                    this.board[row][col] = setValue;
                    updateAnalyzed(setValue, row, col);
                    isUpdate = true;
                }
            }
            else {
                solvedCounter++;
                doneBlocks[row] = true;
            }
        }
        // Find the block for a certain value...
        if (solvedCounter < 9) {
            for (value = 1; value <= 9; value++) {
                setBlock = findBlock(tmp, doneBlocks, value);
                if (setBlock != -1) {
                    this.board[setBlock][col] = value;
                    updateAnalyzed(value, setBlock, col);
                    isUpdate = true;
                }
            }
        }
        if (solvedCounter == 9) {
            return 0;
        }
        else {
            if (isUpdate) {
                return 1;
            }
            else {
                return -1;
            }
        }
    }

    public void solve() {
        analyzeRow();
        analyzeCol();
        analyzeCell();
        int result;
        int solvedCount;
        int unProcCell;
        int unProcRow;
        int unProcCol;
        boolean finish = false;
        while (!finish) {
            solvedCount = 0;
            unProcCell = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (!this.solvedCell[i][j]) {
                        result = findOnlyInCell(i, j);
                        if (result == 0) {
                            this.solvedCell[i][j] = true;
                            solvedCount++;
                        }
                        else {
                            if (result == -1) {
                                unProcCell++;
                            }
                        }
                    }
                    else {
                        solvedCount++;
                        unProcCell++;
                    }
                }
            }
            if (solvedCount == 9) {
                finish = true;
            }

            solvedCount = 0;
            unProcRow = 0;
            for (int i = 0; i < 9; i++) {
                if (!this.solvedRow[i]) {
                    result = findOnlyInRow(i);
                    if (result == 0) {
                        this.solvedRow[i] = true;
                        solvedCount++;
                    }
                    else {
                        if (result == -1) {
                            unProcRow++;
                        }
                    }
                }
                else {
                    solvedCount++;
                    unProcRow++;
                }
            }
            if (solvedCount == 9) {
                finish = true;
            }

            solvedCount = 0;
            unProcCol = 0;
            for (int i = 0; i < 9; i++) {
                if (!this.solvedCol[i]) {
                    result = findOnlyInCol(i);
                    if (result == 0) {
                        this.solvedCol[i] = true;
                        solvedCount++;
                    }
                    else {
                        if (result == -1) {
                            unProcCol++;
                        }
                    }
                }
                else {
                    solvedCount++;
                    unProcCol++;
                }
            }
            if (solvedCount == 9) {
                finish = true;
            }
            if (unProcCol == 9 && unProcCell == 9 && unProcRow == 9) {
                finish = true;
            }
        }
    }

    //Solver Ends...
    //------------------------------------------------------------------------------------------------------------------

    public boolean add(int col, int row, int value) {
        if (this.board[row][col] == 0 && value != 0) {
            if (!presentInCol(value, col) && !presentInRow(value, row) && !presentInCell(value, col, row)) {
                this.usrBoard[row][col] = value;
                return true;
            }
        }
        return false;
    }

    public int remove(int col, int row) {
        int result;
        if (this.board[row][col] != 0) {
            return 0;
        }
        result = this.usrBoard[row][col];
        this.usrBoard[row][col] = 0;
        return result;
    }

    public boolean isSolved() {
        int counter = 0;
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (this.board[i][j] != 0) {
                    counter++;
                    this.usrBoard[i][j] = this.board[i][j];
                }
                else {
                    if (this.usrBoard[i][j] != 0) {
                        counter++;
                    }
                }
            }
        }
        if (counter != 81) {
            return false;
        }
        //counter is 81

        //1. rows
        for (int i = 0; i < 9; i++) {
            int[] array = new int[9];
            int value;
            for (int j = 0; j < 9; j++) {
                value = this.usrBoard[i][j];
                array[value - 1] = 1;
            }
            for (int j = 0; j < 9; j++) {
                if (array[j] == 0) {
                    return false;
                }
            }
        }
        //2.columns
        for (int i = 0; i < 9; i++) {
            int[] array = new int[9];
            int value;
            for (int j = 0; j < 9; j++) {
                value = this.usrBoard[j][i];
                array[value - 1] = 1;
            }
            for (int j = 0; j < 9; j++) {
                if (array[j] == 0) {
                    return false;
                }
            }
        }
        //3.boxes
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int[] array = new int[9];
                int value;
                for (int k = 0; k < 9; k++) {
                    value = this.usrBoard[i * 3 + k / 3][j * 3 + k % 3];
                    array[value - 1] = 1;
                }
                for (int k = 0; k < 9; k++) {
                    if (array[k] == 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
}
