#ifndef GAME_H
#define GAME_H
#define BOUNDARYWIDTH 80
#define BOUNDARYHEIGHT 80
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define MaxSize 600
extern gameover;
void QueueInitiate();
void QueueAppend(int x,int y);
void QueueDelete();
int QueueGetX();
int QueueGetY();
int QueueGetLastX();
int QueueGetLastY();
void gameInitial();
void gameOn();
void move();
void DrawBoundary();
void DrawSnake();
void DrawFood();
void DrawScore();
void DrawName();
#endif GAME_H