/******************
* Name: Sajed Isa
* ID: 325949089
******************/

#include <stdio.h>

#define MAX_GRID 20

/* --- Task 1: Reverse Phrase --- */
void doReverse() {
    char c;
    if (scanf("%c", &c) == 1 && c != '\n') {
        doReverse();
        printf("%c", c);
    }
}

void task1ReversePhrase() {
    printf("Please insert the phrase to reverse:\n");
    // تنظيف المخزن المؤقت لقراءة الجملة بعد رقم الخيار
    scanf(" "); 
    doReverse();
    printf("\n");
}

/* --- Task 2: Palindrome --- */
void fillArray(char arr[], int n, int i) {
    if (i == n) return;
    scanf(" %c", &arr[i]);
    fillArray(arr, n, i + 1);
}

int checkPal(char str[], int s, int e) {
    if (s >= e) return 1;
    if (str[s] != str[e]) return 0;
    return checkPal(str, s + 1, e - 1);
}

void task2CheckPalindrome() {
    int len;
    printf("Please enter the length:\n");
    scanf("%d", &len);
    char str[200];
    printf("Please enter the characters:\n");
    fillArray(str, len, 0);
    if (checkPal(str, 0, len - 1))
        printf("The phrase is a palindrome!!\n");
    else
        printf("The phrase is not a palindrome!!\n");
}

/* --- Task 3: Sentences --- */
void generateSentences(char sub[][50], char vrb[][50], char obj[][50],
                       int S, int V, int O, int i, int j, int k) {
    if (i == S) return;
    if (j == V) {
        generateSentences(sub, vrb, obj, S, V, O, i + 1, 0, 0);
        return;
    }
    if (k == O) {
        generateSentences(sub, vrb, obj, S, V, O, i, j + 1, 0);
        return;
    }
    printf("%s %s %s\n", sub[i], vrb[j], obj[k]);
    generateSentences(sub, vrb, obj, S, V, O, i, j, k + 1);
}

void task3GenerateSentences() {
    int S, V, O;
    // لا يوجد نص توضيحي هنا حسب لقطات الشاشة
    if (scanf("%d %d %d", &S, &V, &O) != 3) return;
    char s[20][50], v[20][50], o[20][50];
    for (int i = 0; i < S; i++) scanf("%s", s[i]);
    for (int i = 0; i < V; i++) scanf("%s", v[i]);
    for (int i = 0; i < O; i++) scanf("%s", o[i]);
    generateSentences(s, v, o, S, V, O, 0, 0, 0);
}

/* --- Task 4: Zip Puzzle --- */
char sol[MAX_GRID][MAX_GRID];

void initSol(int r, int c, int i, int j) {
    if (i == r) return;
    sol[i][j] = '.';
    if (j == c - 1) initSol(r, c, i + 1, 0);
    else initSol(r, c, i, j + 1);
}

int solveZip(int g[MAX_GRID][MAX_GRID], int r, int c, int R, int C, int t) {
    if (t == R * C) {
        sol[r][c] = 'X';
        return 1;
    }
    int val = t + 1;
    // الترتيب: أسفل، أعلى، يمين، يسار
    if (r + 1 < R && g[r + 1][c] == val) {
        sol[r][c] = 'D';
        if (solveZip(g, r + 1, c, R, C, val)) return 1;
    }
    if (r - 1 >= 0 && g[r - 1][c] == val) {
        sol[r][c] = 'U';
        if (solveZip(g, r - 1, c, R, C, val)) return 1;
    }
    if (c + 1 < C && g[r][c + 1] == val) {
        sol[r][c] = 'R';
        if (solveZip(g, r, c + 1, R, C, val)) return 1;
    }
    if (c - 1 >= 0 && g[r][c - 1] == val) {
        sol[r][c] = 'L';
        if (solveZip(g, r, c - 1, R, C, val)) return 1;
    }
    sol[r][c] = '.';
    return 0;
}

void task4ZipPuzzle() {
    int R, C;
    printf("Please enter the board size:\n");
    scanf("%d %d", &R, &C);
    int grid[MAX_GRID][MAX_GRID];
    printf("Please enter the grid:\n");
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &grid[i][j]);
    initSol(R, C, 0, 0);
    if (solveZip(grid, 0, 0, R, C, 1)) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                printf("%c%s", sol[i][j], (j == C - 1 ? "" : " "));
            }
            printf("\n");
        }
    } else printf("Failure!!\n");
}

/* --- Task 5: Sudoku --- */
int canPlace(int b[9][9], int r, int c, int n, int i) {
    if (i == 9) return 1;
    if (b[r][i] == n || b[i][c] == n) return 0;
    int sr = (r / 3) * 3, sc = (c / 3) * 3;
    if (b[sr + (i / 3)][sc + (i % 3)] == n) return 0;
    return canPlace(b, r, c, n, i + 1);
}

int runSudoku(int b[9][9], int r, int c);

int tryNumbers(int b[9][9], int r, int c, int n) {
    if (n > 9) return 0;
    if (canPlace(b, r, c, n, 0)) {
        b[r][c] = n;
        if (runSudoku(b, (c == 8 ? r + 1 : r), (c + 1) % 9)) return 1;
        b[r][c] = 0;
    }
    return tryNumbers(b, r, c, n + 1);
}

int runSudoku(int b[9][9], int r, int c) {
    if (r == 9) return 1;
    if (b[r][c] != 0) return runSudoku(b, (c == 8 ? r + 1 : r), (c + 1) % 9);
    return tryNumbers(b, r, c, 1);
}

void task5Sudoku() {
    int board[9][9];
    printf("Please enter the sudoku board:\n");
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            scanf("%d", &board[i][j]);
    if (runSudoku(board, 0, 0)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d%s", board[i][j], (j == 8 ? "" : " "));
            }
            printf("\n");
        }
    } else printf("No solution!!\n");
}

/* --- MAIN --- */
int main() {
    int option;
    while (1) {
        printf("Choose an option:\n");
        if (scanf("%d", &option) != 1 || option <= 0) break;
        switch (option) {
            case 1: task1ReversePhrase(); break;
            case 2: task2CheckPalindrome(); break;
            case 3: task3GenerateSentences(); break;
            case 4: task4ZipPuzzle(); break;
            case 5: task5Sudoku(); break;
            default: break; 
        }
    }
    return 0;
}


