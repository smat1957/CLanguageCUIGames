#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定数
#define ROW 4
#define COLUMN 4
// 構造体
struct Tile{
    int num;
    int row;
    int clm;
};
enum BOOLEAN{
  false, /* false = 0, true = 1 */
  true
};
// function prototypes
/*
int findTileNum(int);
void swapTile(int,int);
void swapTileR(int,int,int);
void swapTileC(int,int,int);
void moveTile(int);
void shuffle(int);
enum BOOLEAN check();
void disp();
void init();
*/

static struct Tile tiles[16];   /* 16 = ROW * COLUMN */

// サブプログラム
int findTileNum(int num){
    int i;
    for (i = 0; i < ROW * COLUMN; i++){
        if (tiles[i].num == num){
            return i;
        }
    }
    return -1;
}
/* ============================================================ */
void swapTile(int n1, int n2){
    int tmp = tiles[n1].num; 
    tiles[n1].num = tiles[n2].num;
    tiles[n2].num = tmp;
}
/* ============================================================ */
void swapTileR(int c, int r1, int r2){
    int n1 = r1 * COLUMN + c;
    int n2 = r2 * COLUMN + c;
    swapTile(n1, n2);
}
/* ============================================================ */
void swapTileC(int r, int c1, int c2){
    int n1 = r * COLUMN + c1;
    int n2 = r * COLUMN + c2;
    swapTile(n1, n2);
}
/* ============================================================ */
void moveTile(int sel){
    int j;
    int s = findTileNum(sel);
    int sr = tiles[s].row;
    int sc = tiles[s].clm;
    int z = findTileNum(0);
    int zr = tiles[z].row;
    int zc = tiles[z].clm;
    if (sr == zr){
        if (sc < zc){
            for (j = zc; j > sc; j--){
                if (0 <= j - 1){
                    swapTileC(sr, j, j - 1);
                }
            }
        } else if (zc < sc) {
            for (j = zc; j < sc; j++){
                if (j + 1 < COLUMN){
                    swapTileC(sr, j, j + 1);
                }
            }
        }
    }
    if (sc == zc){
        if (sr < zr){
            for (j = zr; j > sr; j--){
                if (0 <= j - 1){
                    swapTileR(sc, j, j - 1);
                }
            }
        } else if (zr < sr){
            for (j = zr; j < sr; j++){
                if (j + 1 < ROW){
                    swapTileR(sc, j, j + 1);
                }
            }
        }
    }
}
/* ============================================================ */
void shuffle(int n){
    int sel, min = 0, max = ROW*COLUMN;
    do{
        sel = (rand() % (max - min + 1)) + min;
        moveTile(sel);
        n--;
    } while (0 < n);
}
/* ============================================================ */
enum BOOLEAN check(){
  int i, j, n;
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COLUMN; j++){
            n = i * COLUMN + j;
            if (tiles[n].num != n){
                return true;
            }
        }
    }
    return false;
}
/* ============================================================ */
void disp(){
  int i, j, n;
    printf("\n");
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COLUMN; j++){
            n = i * COLUMN + j;
            if (tiles[n].num == 0){
                printf("[  ]");
            } else {
                printf("[%2d]", tiles[i * COLUMN + j].num);
            }
        }
        printf("\n");
    }
}
/* ============================================================ */
void init(){
    srand((unsigned)time(NULL));
    int i, j, n;
    for (i = 0; i < ROW; i++){
        for (j = 0; j < COLUMN; j++){
            n = i * COLUMN + j;
            tiles[n].num = n;
            tiles[n].row = i;
            tiles[n].clm = j;
        }
    }
    shuffle(1000);
}
// メイン
int main(void) {
    int sel;
    init();
    do {
        disp();
        do {
            printf("\nSelect number:");
            scanf("%d", &sel);
        } while( sel>ROW*COLUMN );
        moveTile(sel);
    } while( check() );

    return 0;
}
