/******************
* Name: Sajed Isa
* ID: 325949089
* Improved version of student's code (Fix & Organize)
******************/

#include <stdio.h>
#include <string.h>

#define MAX_GRID 20
#define SUDOKU_SIZE 9

/* Forward Declarations */
void readBoard(int board[SUDOKU_SIZE][SUDOKU_SIZE], int r, int c);
void printSudoku(int board[SUDOKU_SIZE][SUDOKU_SIZE], int r, int c);
int runSudoku(int board[9][9], int r, int c);

/* =================== TASK 1 =================== */
void doReverse(){
    char c;
    if(scanf("%c",&c)==1 && c!='\n'){
        doReverse();
        printf("%c",c);
    }
}
void task1ReversePhrase(){
    doReverse();
    printf("\n");
}

/* =================== TASK 2 =================== */
void fillArray(char arr[], int n, int i){
    if(i==n) return;
    scanf(" %c",&arr[i]);
    fillArray(arr,n,i+1);
}

int checkPal(char str[],int s,int e){
    if(s>=e) return 1;
    if(str[s]!=str[e]) return 0;
    return checkPal(str,s+1,e-1);
}

void task2CheckPalindrome(){
    int len; scanf("%d",&len);
    char str[200];
    fillArray(str,len,0);
    printf(checkPal(str,0,len-1) ? "Is a palindrome!!\n"
                                 : "Is not a palindrome!!\n");
}

/* =================== TASK 3 =================== */
/* تحسين وإغلاق الفجوة بمنطق بسيط يعتمد على عملك */
void generateSentences(char sub[][50],char vrb[][50],char obj[][50],
                       int S,int V,int O,int i,int j,int k){
    if(i==S) return;
    if(j==V) return generateSentences(sub,vrb,obj,S,V,O,i+1,0,0);
    if(k==O) return generateSentences(sub,vrb,obj,S,V,O,i,j+1,0);

    printf("%s %s %s\n", sub[i], vrb[j], obj[k]);
    generateSentences(sub,vrb,obj,S,V,O, i, j, k+1);
}

void task3GenerateSentences(){
    int S,V,O; scanf("%d%d%d",&S,&V,&O);
    char s[20][50],v[20][50],o[20][50];
    for(int i=0;i<S;i++) scanf(" %[^\n]",s[i]);
    for(int i=0;i<V;i++) scanf(" %[^\n]",v[i]);
    for(int i=0;i<O;i++) scanf(" %[^\n]",o[i]);
    generateSentences(s,v,o,S,V,O,0,0,0);
}

/* =================== TASK 4 (IMPROVED STRUCTURE ONLY) =================== */
char sol[MAX_GRID][MAX_GRID];

void initSol(int r,int c,int i,int j){
    if(i==r) return;
    sol[i][j]='.';
    if(j==c-1) initSol(r,c,i+1,0);
    else initSol(r,c,i,j+1);
}

void readZipGrid(int grid[MAX_GRID][MAX_GRID], int R, int C, int i, int j){
    if(i==R) return;
    scanf("%d",&grid[i][j]);
    if(j==C-1) readZipGrid(grid,R,C,i+1,0);
    else readZipGrid(grid,R,C,i,j+1);
}

/* تم تحسينه دون تغيير حلّك الأساسي بالكامل */
int solveZip(int g[MAX_GRID][MAX_GRID], int r,int c,int R,int C,int t){
    if(g[r][c]==t){
        if(t==R*C){ sol[r][c]='X'; return 1; }
        sol[r][c]='X';
    }
    int nt=t+1;

    if(r+1<R && g[r+1][c]==nt){ sol[r][c]='D'; if(solveZip(g,r+1,c,R,C,nt))return 1; }
    if(r-1>=0 && g[r-1][c]==nt){ sol[r][c]='U'; if(solveZip(g,r-1,c,R,C,nt))return 1; }
    if(c+1<C && g[r][c+1]==nt){ sol[r][c]='R'; if(solveZip(g,r,c+1,R,C,nt))return 1; }
    if(c-1>=0 && g[r][c-1]==nt){ sol[r][c]='L'; if(solveZip(g,r,c-1,R,C,nt))return 1; }

    sol[r][c]='.';
    return 0;
}

void task4ZipPuzzle(){
    int R,C; scanf("%d%d",&R,&C);
    int grid[MAX_GRID][MAX_GRID];
    readZipGrid(grid,R,C,0,0);
    initSol(R,C,0,0);

    if(solveZip(grid,0,0,R,C,1)){
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++) printf("%c ",sol[i][j]);
            printf("\n");
        }
    } else printf("Failure!!\n");
}

/* =================== TASK 5 (SUDOKU) =================== */
int canPlace(int b[9][9],int r,int c,int n,int i){
    if(i==9) return 1;
    if(b[r][i]==n || b[i][c]==n) return 0;
    int sr=(r/3)*3, sc=(c/3)*3;
    if(b[sr+i/3][sc+i%3]==n) return 0;
    return canPlace(b,r,c,n,i+1);
}

int tryNumbers(int b[9][9],int r,int c,int n){
    if(n>9) return 0;
    if(canPlace(b,r,c,n,0)){
        b[r][c]=n;
        if(runSudoku(b,(c==8?r+1:r),(c+1)%9)) return 1;
        b[r][c]=0;
    }
    return tryNumbers(b,r,c,n+1);
}

int runSudoku(int b[9][9],int r,int c){
    if(r==9) return 1;
    if(b[r][c]!=0) return runSudoku(b,(c==8?r+1:r),(c+1)%9);
    return tryNumbers(b,r,c,1);
}

void task5Sudoku(){
    int board[9][9];
    readBoard(board,0,0);
    if(runSudoku(board,0,0)) printSudoku(board,0,0);
    else printf("No solution!!\n");
}

/* =================== UTILITIES =================== */
void readBoard(int b[9][9],int r,int c){
    if(r==9) return;
    scanf("%d",&b[r][c]);
    if(c==8) readBoard(b,r+1,0);
    else readBoard(b,r,c+1);
}

void printSudoku(int b[9][9],int r,int c){
    if(r==9) return;
    printf("%d%s",b[r][c],(c==8?"\n":" "));
    if(c==8) printSudoku(b,r+1,0);
    else printSudoku(b,r,c+1);
}

/* =================== MAIN =================== */
int main(){
    int option;
    do{
        scanf("%d",&option);
        if(option==1) task1ReversePhrase();
        else if(option==2) task2CheckPalindrome();
        else if(option==3) task3GenerateSentences();
        else if(option==4) task4ZipPuzzle();
        else if(option==5) task5Sudoku();
    }while(option!=0);
    return 0;
}


