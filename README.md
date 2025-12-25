#include <stdio.h>
#include <string.h>

// Max sizes according to instructions
#define MAX_GRID 20
#define SUDOKU_SIZE 9

// Forward declarations for helpers
void readBoard(int board[SUDOKU_SIZE][SUDOKU_SIZE], int r, int c);
void printSudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE], int r, int c);
int canPlace(int board[9][9], int row, int col, int num, int i);

/* --- Task 1: Reverse Phrase --- */
// Just calling a recursive function to read and print back
void doReverse() {
    char c;
    if (scanf("%c", &c) == 1 && c != '\n') {
        doReverse(); // Go to next char
        printf("%c", c); // Print on the way back
    }
}

void task1ReversePhrase() {
    doReverse();
    printf("\n");
}

/* --- Task 2: Palindrome Check --- */
// Recursive way to read n chars into an array
void fillArray(char arr[], int n, int i) {
    if (i == n) return;
    scanf(" %c", &arr[i]);
    fillArray(arr, n, i + 1);
}

// Comparing edges using recursion
int checkPal(char str[], int start, int end) {
    if (start >= end) return 1;
    if (str[start] != str[end]) return 0;
    return checkPal(str, start + 1, end - 1);
}

void task2CheckPalindrome() {
    int len;
    printf("Enter phrase length:\n");
    scanf("%d", &len);
    char myStr[100];
    fillArray(myStr, len, 0);
    if (checkPal(myStr, 0, len - 1)) {
        printf("Is a palindrome!!\n");
    } else {
        printf("Is not a palindrome!!\n");
    }
}

/* --- Task 4: Zip Puzzle --- */
// Recursive reader for the grid
void readZipGrid(int grid[MAX_GRID][MAX_GRID], int rows, int cols, int r, int c) {
    if (r == rows) return;
    scanf("%d", &grid[r][c]);
    if (c == cols - 1) readZipGrid(grid, rows, cols, r + 1, 0);
    else readZipGrid(grid, rows, cols, r, c + 1);
}

int solveZip(int grid[MAX_GRID][MAX_GRID], int r, int c, int rows, int cols, int visited, int target) {
    // Base case: all cells visited
    if (visited == rows * cols) return 1;
    
    // Bounds check and visited check
    if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == -1) return 0;
    
    // Check if cell matches the number sequence
    if (grid[r][c] != 0 && grid[r][c] != target) return 0;

    int currentVal = grid[r][c];
    int nextTarget = (currentVal == target) ? target + 1 : target;
    
    grid[r][c] = -1; // Mark as visited

    // Try all 4 directions recursively
    if (solveZip(grid, r + 1, c, rows, cols, visited + 1, nextTarget) ||
        solveZip(grid, r - 1, c, rows, cols, visited + 1, nextTarget) ||
        solveZip(grid, r, c + 1, rows, cols, visited + 1, nextTarget) ||
        solveZip(grid, r, c - 1, rows, cols, visited + 1, nextTarget)) {
        return 1;
    }

    grid[r][c] = currentVal; // Undo (Backtrack)
    return 0;
}

void task4ZipPuzzle() {
    int r, c;
    printf("Enter dimensions (rows cols):\n");
    scanf("%d %d", &r, &c);
    int grid[MAX_GRID][MAX_GRID];
    readZipGrid(grid, r, c, 0, 0);
    
    if (solveZip(grid, 0, 0, r, c, 1, 1)) printf("Success!!\n");
    else printf("Failure!!\n");
}

/* --- Task 5: Sudoku Solver --- */
// Using simple recursion to check if number is safe
int canPlace(int board[9][9], int row, int col, int num, int i) {
    if (i == 9) return 1;
    if (board[row][i] == num || board[i][col] == num) return 0;
    // Check 3x3 box
    int startR = (row / 3) * 3, startC = (col / 3) * 3;
    if (board[startR + i / 3][startC + i % 3] == num) return 0;
    return canPlace(board, row, col, num, i + 1);
}

// Try digits 1-9 without using a loop
int tryNumbers(int board[9][9], int r, int c, int n) {
    if (n > 9) return 0;
    if (canPlace(board, r, c, n, 0)) {
        board[r][c] = n;
        int nextC = (c == 8) ? 0 : c + 1;
        int nextR = (c == 8) ? r + 1 : r;
        if (runSudoku(board, nextR, nextC)) return 1;
        board[r][c] = 0; // Backtrack
    }
    return tryNumbers(board, r, c, n + 1);
}

int runSudoku(int board[9][9], int r, int c) {
    if (r == 9) return 1; // Solved!
    
    int nextC = (c == 8) ? 0 : c + 1;
    int nextR = (c == 8) ? r + 1 : r;

    if (board[r][c] != 0) return runSudoku(board, nextR, nextC);
    return tryNumbers(board, r, c, 1);
}

void task5Sudoku() {
    int board[9][9];
    readBoard(board, 0, 0);
    if (runSudoku(board, 0, 0)) printSudoku(board, 0, 0);
    else printf("No solution!!\n");
}

// Helper: recursive printing (no for loops)
void printSudoku(int board[9][9], int r, int c) {
    if (r == 9) return;
    printf("%d%s", board[r][c], (c == 8 ? "\n" : " "));
    if (c == 8) printSudoku(board, r + 1, 0);
    else printSudoku(board, r, c + 1);
}

// Helper: recursive reading
void readBoard(int board[9][9], int r, int c) {
    if (r == 9) return;
    scanf("%d", &board[r][c]);
    if (c == 8) readBoard(board, r + 1, 0);
    else readBoard(board, r, c + 1);
}

/* --- Main Menu --- */
int main() {
    int option;
    do {
        printf("Choose task (1-5, 0 to exit):\n");
        scanf("%d", &option);
        if (option == 1) task1ReversePhrase();
        else if (option == 2) task2CheckPalindrome();
        else if (option == 4) task4ZipPuzzle();
        else if (option == 5) task5Sudoku();
    } while (option != 0);
    return 0;
}
