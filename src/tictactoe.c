#include <stdio.h>
#include <string.h>

// function prototypes
/*
int lineSum(int, int, int);
int switchTurn(int);
void printBoard();
int slotNum(int);
int checkWinner();
void result(int);
*/

static int board[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
#define MARU 10
#define BATSU -10
#define DRAW 100
#define NEXT 200
/* ============================================================ */
int switchTurn(int turn) {
    if (turn== BATSU)return MARU;
    return BATSU;
}
/* ============================================================ */
void printBoard() {
    char bd[9];
    int i;
    for (i = 0; i < 9; i++) {
        if (board[i] == MARU) bd[i] = 'O';
        else if (board[i] == BATSU) bd[i] = 'X';
        else bd[i] = '0' + i;
    }
    printf("\n/---|---|---\\\n");
    printf("| %c | %c | %c |\n", bd[0], bd[1], bd[2]);
    printf("|---|---|---|\n");
    printf("| %c | %c | %c |\n", bd[3], bd[4], bd[5]);
    printf("|---|---|---|\n");
    printf("| %c | %c | %c |\n", bd[6], bd[7], bd[8]);
    printf("\\---|---|---/\n");
}
/* ============================================================ */
void result(int winner) {
    printf("\n");
    switch (winner) {
    case DRAW: printf("引き分け\t"); break;
    case MARU: printf("'O' の勝ち\t"); break;
    case BATSU: printf("'X' の勝ち\t"); break;
    }
    printf("またね！\n");
}
/* ============================================================ */
int slotNum(int turn) {
    char *fig = "";
    if (turn==MARU) fig = "'O'";
    else if (turn==BATSU) fig = "'X'";
    int num;
    do {
        printf("\n %s さんのturnです\n石を置く場所 0 〜 8 を指定して下さい：", fig);
        //while (getchar() != '\n');  /* 標準入力バッファのクリア */
        scanf("%d", &num);
        if (!(0 <= num && num < 9)) {
            printf("再指定：0 〜 8 を指定して下さい");
            continue;
        }
        if (board[num] != num) {
            printf("再指定：そこには既に石が置かれています\n");
            continue;
        }
        break;
    } while (1);
    return num;
}
/* ============================================================ */
int lineSum(int n1, int n2, int n3) {
    return board[n1] + board[n2] + board[n3];
}
/* ============================================================ */
int checkWinner() {
    int i, line = 0;
    for (i = 0; i < 8; i++) {
        switch (i) {
        case 0: line = lineSum(0, 1, 2); break;
        case 1: line = lineSum(3, 4, 5); break;
        case 2: line = lineSum(6, 7, 8); break;
        case 3: line = lineSum(0, 3, 6); break;
        case 4: line = lineSum(1, 4, 7); break;
        case 5: line = lineSum(2, 5, 8); break;
        case 6: line = lineSum(0, 4, 8); break;
        case 7: line = lineSum(2, 4, 6); break;
        }
        if (line == 3 * MARU) return MARU;
        else if (line == 3 * BATSU) return BATSU;
    }
    for (i = 0; i < 9; i++){
        if (0 <= board[i] && board[i] < 9) return NEXT;
    }
    return DRAW;
}
/* ============================================================ */
int main(int argc, char *argv[]){
    /* 先手後手を決定 */
    int turn = BATSU;
    if (1 < argc){
        if (!strcmp(argv[1], "-r"))
            turn = MARU;
    }
    printf("スタート！ [Tic Tac Toe]\n");
    int winner;
    do{
        printBoard();            /* ①盤面の表示 */
        int num = slotNum(turn); /* ②手を入力 */
        board[num] = turn;       /* ③手を盤面に配置 */
        turn = switchTurn(turn); /* ④手番の交代 */
        winner = checkWinner();  /* ⑤勝敗の判定 */
    } while (winner == NEXT);
    /* 対戦結果の表示 */
    printBoard();
    result(winner);
    return 0;
}