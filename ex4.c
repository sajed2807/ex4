/******************
* Name: Sajed Isa
* ID: 325949089
******************/

#include <stdio.h>

#define MAX_GRID 20

void clearBuffer() {
    while (getchar() != '\n' && !feof(stdin));
}

/* --- Task 1: Reverse Phrase --- */
void task1ReversePhrase() {
    char str[300];
    printf("Please insert the phrase to reverse:\n");
    fgets(str, 300, stdin);

    int len = 0;
    while (str[len] != '\0' && str[len] != '\n') len++;

    printf("The reversed phrase is: ");
    for (int i = len - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}

/* --- Task 2: Palindrome --- */
void task2CheckPalindrome() {
    int len;
    printf("Please insert the phrase length:\n");
    scanf("%d", &len);
    clearBuffer();

    char str[300];
    printf("Please insert the phrase to check:\n");
    fgets(str, 300, stdin);

    int L = 0, R = len - 1;
    int ok = 1;
    while (L < R) {
        if (str[L] != str[R]) ok = 0;
        L++; R--;
    }

    if (ok) printf("The phrase is a palindrome.\n");
    else   printf("The phrase is not a palindrome.\n");
}

/* --- Task 3: Generate Sentences --- */
void task3GenerateSentences() {
    int S, V, O;
    printf("Please insert number of subjects:\n");
    scanf("%d", &S);
    char subjects[20][50];

    printf("Please insert the list of subjects:\n");
    for (int i = 0; i < S; i++)
        scanf("%s", subjects[i]);

    printf("Please insert number of verbs:\n");
    scanf("%d", &V);
    char verbs[20][50];

    printf("Please insert the list of verbs:\n");
    for (int i = 0; i < V; i++)
        scanf("%s", verbs[i]);

    printf("Please insert number of objects:\n");
    scanf("%d", &O);
    char objects[20][50];

    printf("Please insert the list of objects:\n");
    for (int i = 0; i < O; i++)
        scanf("%s", objects[i]);

    printf("List of Sentences:\n");
    int count = 1;
    for (int i = 0; i < S; i++)
        for (int j = 0; j < V; j++)
            for (int k = 0; k < O; k++)
                printf("%d. %s %s %s\n", count++, subjects[i], verbs[j], objects[k]);
}

/* --- Task 4: Zip Puzzle --- */
char zipSol[MAX_GRID][MAX_GRID];

int solveZip(int g[MAX_GRID][MAX_GRID], int r, int c, int R, int C, int t) {
    if (t == R * C) {
        zipSol[r][c] = 'X';
        return 1;
    }
    int val = t + 1;
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    char move[] = {'D', 'U', 'R', 'L'};

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && g[nr][nc] == val) {
            zipSol[r][c] = move[i];
            if (solveZip(g, nr, nc, R, C, val)) return 1;
        }
    }
    return 0;
}

void task4ZipPuzzle() {
    int R, C;
    printf("Please enter the board size:\n");
    scanf("%d %d", &R, &C);

    for(int i = 0; i < R; i++)
        for(int j = 0; j < C; j++)
            zipSol[i][j] = 'X';

    int grid[MAX_GRID][MAX_GRID];
    printf("Please enter the grid:\n");
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &grid[i][j]);

    if (solveZip(grid, 0, 0, R, C, 1)) {
        printf("Solution:\n");
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++)
                printf("%c%s", zipSol[i][j], j == C - 1 ? "" : " ");
            printf("\n");
        }
    } else printf("No solution exists.\n");
}

/* --- Task 5: Sudoku --- */
int canPlace(int b[9][9], int r, int c, int n) {
    for (int i = 0; i < 9; i++)
        if (b[r][i] == n || b[i][c] == n) return 0;

    int sr = (r / 3) * 3, sc = (c / 3) * 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[sr + i][sc + j] == n) return 0;

    return 1;
}

int solveSudoku(int b[9][9], int r, int c) {
    if (r == 9) return 1;
    if (c == 9) return solveSudoku(b, r + 1, 0);
    if (b[r][c] != 0) return solveSudoku(b, r, c + 1);

    for (int n = 1; n <= 9; n++)
        if (canPlace(b, r, c, n)) {
            b[r][c] = n;
            if (solveSudoku(b, r, c + 1)) return 1;
            b[r][c] = 0;
        }
    return 0;
}

void task5Sudoku() {
    int board[9][9];
    printf("Please enter the sudoku board:\n");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            scanf("%d", &board[i][j]);

    if (solveSudoku(board, 0, 0)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++)
                printf("%d%s", board[i][j], j == 8 ? "" : " ");
            printf("\n");
        }
    } else printf("No solution exists.\n");
}

/* --- MAIN --- */
int main() {
    int option;
    while (1) {
        printf("Please choose a task (1-5) or 6 to exit:\n");

        if (scanf("%d", &option) != 1) {
            clearBuffer();
            continue;
        }

        clearBuffer();

        if (option == 6) {
            printf("Goodbye!\n");
            break;
        }

        switch (option) {
            case 1: task1ReversePhrase(); break;
            case 2: task2CheckPalindrome(); break;
            case 3: task3GenerateSentences(); break;
            case 4: task4ZipPuzzle(); break;
            case 5: task5Sudoku(); break;
            default: break;
        }
        printf("=================================\n");
    }
    return 0;
}

