#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// 定数
#define ROW 4
#define COLUMN 5
// 構造体
enum BOOLEAN {
  false, /* false = 0, true = 1 */
  true
};
struct Card {
    int num;
    int row;
    int clm;
    enum BOOLEAN opn;
};
// function prototypes
/*
void openCard(int);
void closeCard(int);
void switchTurn(enum BOOLEAN);
void disp();
int getNum(char*);
enum BOOLEAN match(int, int);
void wasteTime(int);
void swapCards(int,int);
void shuffle();
void init();
*/

static struct Card cards[20]; /* 20 = ROW * COLUMN */

enum BOOLEAN Turn = true;

// サブプログラム
void openCard(int n){
    cards[n].opn = true;
}
/* ============================================================ */
void closeCard(int n){
    cards[n].opn = false;
}
/* ============================================================ */
void disp(){
    int i, j;
    printf("\n");
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COLUMN; j++){
            int n = i * COLUMN + j;
            if ( !cards[n].opn )
                printf("[ %c ]", 'a' + i * COLUMN + j );
            else
                printf("[ %d ]", cards[i * COLUMN + j].num );
        }
        printf("\n");
    }
    printf("\n");
}
/* ============================================================ */
int getNum(char* s){
    int cnum;
    char str[24], work[24];
    do {
        sprintf(work, "%s%s%s", "\tSelect ", s, " card : ");
        printf("%s", work);
        scanf("%s", str);
        cnum = str[0] - 'a';
    } while (cnum > ROW * COLUMN);
    openCard(cnum);
    disp();
    return cnum;
}
/* ============================================================ */
enum BOOLEAN match(int n1, int n2){
    if ( cards[n1].num == cards[n2].num )
        return true;
    return false;
}
/* ============================================================ */
void swapCards(int n1, int n2){
    struct Card temp;
    temp = cards[n2];
    cards[n2] = cards[n1];
    cards[n1] = temp;
}
/* ============================================================ */
void shuffle(){
    int min = 0;
    int max = ROW*COLUMN;
    while (0 < max){
        int sel = (rand() % (max - min + 1)) + min;
        swapCards(sel, max--);
    }
}
/* ============================================================ */
void init(){
    srand((unsigned)time(NULL));
    int i, j;
    for (i = 0; i < ROW/2; i++){
        for (j = 0; j < COLUMN; j++){
            int num = i * COLUMN + j;
            cards[num].num = cards[ROW * COLUMN - num].num = num;
            cards[num].row = cards[ROW * COLUMN - num].row = i;
            cards[num].clm = cards[ROW * COLUMN - num].clm = j;
            cards[num].opn = cards[ROW * COLUMN - num].opn = false;
        }
    }
    shuffle();
}
// メイン
int main( void ){
    int cnum1, cnum2, Closed=ROW*COLUMN;
    int pointA=0, pointB=0;
    init();
    disp();
    do{
        printf("Aさん：%d 点\tBさん：%d 点\n", pointA, pointB);
        if (Turn)
            printf("= Aさんの番です =\n");
        else
            printf("= Bさんの番です =\n");
        cnum1 = getNum("1st");
        cnum2 = getNum("2nd");
        if ( match(cnum1, cnum2) ){
            printf("当たり\n");
            Closed -= 2;
            if (Turn)
                pointA++;
            else
                pointB++;
        } else {
            printf("ハズレ\n");
            closeCard(cnum1);
            closeCard(cnum2);
            Turn = !Turn;
        }
        sleep(4);
        disp();
    } while ( 0 < Closed );
    return 0;
}
