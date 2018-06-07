#include "game.h"
#include "LCD.h"
#include "joystick.h"
static int direction=RIGHT;
static char scorenum[20];
int Table[80][80];
int gameover=0;
int score=0;
int speed=0;
int flag=1;
struct
{
	int queuex[MaxSize];   //ºá×ø±ê
    int queuey[MaxSize];   //×Ý×ø±ê
	int rear;              //Î²Ö¸Õë
	int front;             //Í·Ö¸Õë
	int count;
}snakeNode;
void gameInitial()
{
    int i=0;
    int j=0;
    DrawBoundary();          //»¨±ß¿ò
    QueueInitiate(&snakeNode);
    for(i=0;i<80;i++)
    {
        for(j=0;j<80;j++)
        {
            Table[i][j]=0;
        }
    }
    QueueAppend(40, 40);   //Èë¶ÓÁÐ
	QueueAppend(41, 40);
    QueueAppend(42, 40);
    QueueAppend(43, 40);
	Table[40][40] = 1;
	Table[41][40] = 1;
    Table[42][40] = 1;
    Table[43][40] = 1;
    DrawFood();
}
void drawLoading()   //¼ÓÔØ¿ò
{
    int i,j;
    for(i=0;i<160;i++)
        LCD_DrawPixel(80+i,200,LCD_COLOR_BLACK);
    for(i=0;i<160;i++)
        LCD_DrawPixel(80+i,200+5,LCD_COLOR_BLACK);
    for(i=0;i<5;i++)
        LCD_DrawPixel(80,200+i,LCD_COLOR_BLACK);
    for(i=0;i<5;i++)
        LCD_DrawPixel(80+160,200+i,LCD_COLOR_BLACK);
    for(i=0;i<160;i++)
    {
        for(j=0;j<5;j++)
        {
            LCD_DrawPixel(80+i,200+j,LCD_COLOR_BLACK);
        }
        DelayMs(10);
    }
}
void move()   //ÔË¶¯
{
    int FrontX=QueueGetX();
    int FrontY=QueueGetY();
    int RearX=QueueGetLastX();
    int RearY=QueueGetLastY();
    switch (direction)
	{
	case UP:
		{
            if(Table[FrontX+1][FrontY]==1||FrontX+1==80)
            {
                gameover=1;
                break;
            }
            if(Table[FrontX+1][FrontY]!=-1)
            {
                QueueAppend(FrontX+1,FrontY);
                Table[FrontX+1][FrontY] = 1;
                Table[RearX][RearY] = 0;
                QueueDelete();
                DrawSnake();
            }
            else
            {
                QueueAppend(FrontX+1,FrontY);
                Table[FrontX+1][FrontY] = 1;
                score=score+10;
                DrawSnake();
                DrawFood();
            }                
			break;
		}
	case DOWN:
		{
            if(Table[FrontX-1][FrontY]==1||FrontX-1==-1)
            {
                gameover=1;
                break;
            }
            if(Table[FrontX-1][FrontY]!=-1)
            {
                QueueAppend(FrontX-1,FrontY);
                Table[FrontX-1][FrontY] = 1;
                Table[RearX][RearY] = 0;
                QueueDelete();
                DrawSnake();
                DrawScore();
            }
            else
            {
                QueueAppend(FrontX-1,FrontY);
                Table[FrontX-1][FrontY] = 1;
                score=score+10;
                DrawSnake();
                DrawFood();
                DrawScore();
            }  
			break;
		}
	case LEFT:
		{
            if(Table[FrontX][FrontY-1]==1||FrontY-1==0)
            {
                gameover=1;
                break;
            }
            if(Table[FrontX][FrontY-1]!=-1)
            {
                QueueAppend(FrontX,FrontY-1);
                Table[FrontX][FrontY-1] = 1;
                Table[RearX][RearY] = 0;
                QueueDelete();
                DrawSnake();
                DrawScore();
            }
            else
            {
                QueueAppend(FrontX,FrontY-1);
                Table[FrontX][FrontY-1] = 1;
                score=score+10;
                DrawSnake();
                DrawFood();
                DrawScore();
            }
			break;
		}
	case RIGHT:
		{
            if(Table[FrontX][FrontY+1]==1||FrontY+1==80)
            {
                gameover=1;
                break;
            }
            if(Table[FrontX][FrontY+1]!=-1)
            {
                QueueAppend(FrontX,FrontY+1);
                Table[FrontX][FrontY+1] = 1;
                Table[RearX][RearY] = 0;
                QueueDelete();
                DrawSnake();
                DrawScore();
            }
            else
            {
                QueueAppend(FrontX,FrontY+1);
                Table[FrontX][FrontY+1] = 1;
                score=score+10;
                DrawSnake();
                DrawFood();
                DrawScore();
            }
			break;
		}
	}
}
void DrawBoundary()
{
    int i;
    for(i=0;i<BOUNDARYHEIGHT+1;i++)
    {
        LCD_DrawPixel(19,29+i,LCD_COLOR_WHITE);
        LCD_DrawPixel(19+BOUNDARYWIDTH+1,29+i+1,LCD_COLOR_WHITE);
    }for(i=0;i<BOUNDARYWIDTH+1;i++)
    {
        LCD_DrawPixel(20+i,29,LCD_COLOR_WHITE);
        LCD_DrawPixel(19+i,29+BOUNDARYHEIGHT+1,LCD_COLOR_WHITE);
    }
}
void DrawSnake()    //»­Éß
{
	int i,j;
	for ( i= 0; i < 80; i++)
	{
		for (j = 0; j < 80; j++)
		{
			if (Table[i][j] == 1)
				LCD_DrawPixel(20 + i, 30 + j, LCD_COLOR_WHITE);
            if (Table[i][j] == 0)
				LCD_DrawPixel(20 + i, 30 + j, LCD_COLOR_BLACK);
		}
	}
}
void DrawScore()   //»­·ÖÊý
{
    sprintf(scorenum,"%d",score);
    LCD_DisplayString(40,150,"Score:");
    LCD_DisplayString(40,250,scorenum);
}
void DrawFood()   //»­Ê³Îïï
{
	int x,y;
	//do {
		x = rand() % 80;
		y = rand() % 80;
	//} while (Table[x][y] != 1);
	Table[x][y] = -1;     //Ê³ÎïÔÚtableÖÐÎª-1£»
	LCD_DrawPixel(20 + x, 30 + y, LCD_COLOR_RED);
}
void DrawName()  //Ãû×Ö
{
    if(flag) 
    {
        LCD_DisplayString(200,speed++,"Made By zmh");
        if(speed==140) flag=0;
    }
    else 
    {
        LCD_DisplayString(200,speed--,"Made By zmh");
        if(speed==0) flag=1;
    }
}
void gameOn()
{
    KEY_TypeDef key;
	uint32_t i;
	Joystick_Config();
	while(1)
	{
		i=1000000;
		while(i--);
		key = GetKey();
	
		if(key.KeyValue && key.Pressed)
		{
			switch (key.KeyValue)
			{
			case KEY_VALUE_UP:
            {
                if(direction!=DOWN) direction = UP;
				break;
            }
			case KEY_VALUE_DOWN: 
            {
                if(direction!=UP) direction = DOWN;
				break;
            }
			case KEY_VALUE_LEFT: 
            {              
                if(direction!=RIGHT) direction  = LEFT;
				break;
            }
			case KEY_VALUE_RIGHT:
            {                
                if(direction!=LEFT) direction = RIGHT;
				break;
            }
			default:
				break;
			}
        }
    }
}
void QueueInitiate()
{
	snakeNode.rear = 0;
	snakeNode.front = 0;
	snakeNode.count = 0;
}
void QueueAppend(int x,int y)
{
	snakeNode.queuex[snakeNode.front] = x;
    snakeNode.queuey[snakeNode.front] = y;
	snakeNode.front = (snakeNode.front + 1) % MaxSize;
	snakeNode.count++;
}
void QueueDelete()
{
	if (snakeNode.count == 0)
	{
		return ;
	}
	else
	{
		snakeNode.rear = (snakeNode.rear + 1) % MaxSize;
		snakeNode.count--;
	}
}
int QueueGetX()
{
	if(snakeNode.front==0) return snakeNode.queuex[MaxSize-1];
    return snakeNode.queuex[snakeNode.front-1];
}
int QueueGetY()
{
	if(snakeNode.front==0) return snakeNode.queuey[MaxSize-1];
    return snakeNode.queuey[snakeNode.front-1];
}
int QueueGetLastX()
{
    return snakeNode.queuex[snakeNode.rear];
}
int QueueGetLastY()
{

    return snakeNode.queuey[snakeNode.rear];
}