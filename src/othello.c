#include <stdio.h>
#include <stdlib.h>

enum BOOLEAN{
  false,    /* false=0, true=1 */
  true
};

#define BOARDW (8) // 4, 6, 8, ....
#define BLACK (0)
#define WHITE (1)
#define NONE (2)

int UNITV[][2] = {{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1}};
int turn = BLACK;
int passcount = 0;
int endflag = false;
int board[BOARDW * BOARDW];

const char* TILE[] = {
  "●",  //TILE_BLACK
  "◯",  //TILE_WHITE
  "."   //TILE_NONE
};

typedef struct {
  int x, y;
}POS;

/* ======================================================================= */
void setstone(POS pos, int num){
  int index = (pos.y * BOARDW) + pos.x;
  board[index] = num;
}
/* ======================================================================= */
int getstone(POS pos){
  int index = (pos.y * BOARDW) + pos.x;
  return board[index];
}
/* ======================================================================= */
int count(int color){
  int num=0;
  for(int i=0; i<(BOARDW * BOARDW); i++)
    if(board[i]==color)
      num++;
  return num;
}
/* ======================================================================= */
void drawboard(){
  for(int x=0; x<BOARDW; x++){
    if(x==0){
      printf("    ");
      char a='a';
      for(int i=0; i<BOARDW; i++)
        printf("%c ", a+i);
      printf("\n");
    }
    printf("%2d  ", x+1);
    for(int y=0; y<BOARDW; y++){
      int index = y * BOARDW + x;
      switch(board[index]){
      case BLACK:printf("%s ", TILE[BLACK]);break;
      case WHITE:printf("%s ", TILE[WHITE]);break;
      case NONE: printf("%s ", TILE[NONE]); break;
      }
    }
    printf("\n");
  }
  printf("\n%s(%2d), %s(%2d)", TILE[BLACK],count(BLACK),TILE[WHITE],count(WHITE));
  if(!endflag)
    printf(" : turn(%s)\n", TILE[turn]);
  else
    printf("\n");
}
/* ======================================================================= */
enum BOOLEAN initboard(){
  if((BOARDW%2)||(BOARDW<4)||(8<BOARDW))
    return false;
  int x, y;
  POS pos;
  for(y=0; y<BOARDW; y++)
    for(x=0; x<BOARDW; x++){
      pos.x = x; pos.y = y;
      setstone(pos, NONE);
    }
  pos.x = pos.y = BOARDW/2-1;
  setstone(pos, BLACK);
  pos.x = BOARDW/2; pos.y = pos.x-1;
  setstone(pos, WHITE);
  pos.y = BOARDW/2; pos.x = pos.y-1;
  setstone(pos, WHITE);
  pos.x = pos.y = BOARDW/2;
  setstone(pos, BLACK);
  turn = BLACK;
  passcount = 0;
  endflag = false;
  drawboard();
  return true;
}
/* ======================================================================= */
POS movepos(POS pos, int v){
  POS p;
  p.x = pos.x + UNITV[v][0];
  p.y = pos.y + UNITV[v][1];
  return p;
}
/* ======================================================================= */
enum BOOLEAN isinside(POS pos){
  if( (pos.x<0) || (BOARDW<=pos.x) )
    return false;
  if( (pos.y<0) || (BOARDW<=pos.y) )
    return false;
  return true;
}
/* ======================================================================= */
int search(POS pos, int v, int num){
  int piece = 0;
  while(true){
    pos = movepos(pos, v);
    if(!isinside(pos))
      return 0;
    if(getstone(pos)==NONE)
      return 0;
    if(getstone(pos)==num)
      break;
    piece++;
  }
  return piece;
}
/* ======================================================================= */
int flippable(POS pos, int num){
  if(getstone(pos)!=NONE)
    return 0;
  int total = 0;
  int vec[]={0,0};
  for(int i=0; i<8; i++)
    total += search(pos, i, num);
  return total;
}
/* ======================================================================= */
void nextturn(){
  turn ^= 1;
  int empty = 0;
  for(int y=0; y<BOARDW; y++)
    for(int x=0; x<BOARDW; x++){
      POS pos; pos.x=x; pos.y=y;
      if(getstone(pos)==NONE)
        empty++;
      if(0<flippable(pos,turn)){
        passcount = 0;
        return;
      }
    }
  if(empty==0){
    endflag = true;
    return;
  }
  passcount++;
  if(2<=passcount)
    endflag = true;
}
/* ======================================================================= */
POS decode(char* str){
  POS pos;
  pos.x = atoi(str)-1;
  pos.y = *(str+1) - 'a';
  return pos;
}
/* ======================================================================= */
void event(POS pos){
  if(endflag){
    initboard();
    return;
  }
  if(0<passcount){
    nextturn();
    drawboard();
    return;
  }
  if(!isinside(pos))
    return;
  if(0==flippable(pos, turn))
    return;
  for(int i=0; i<8; i++){
    int loop = search(pos, i, turn);
    POS temp = pos;
    for(int j=0; j<loop; j++){
      temp = movepos(temp, i);
      setstone(temp, turn);
    }
  }
  setstone(pos, turn);
  nextturn();
  drawboard();
}
/* ======================================================================= */
int main(void){
  if(!initboard())
    return 8;
  char inpt[]="   ";
  while(!endflag){
    printf("=>");
    scanf("%s", inpt);
    POS pos = decode(inpt);
    printf("\n");
    event(pos);
  }
  return 0;
}
