#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define Max 100 	//最大蛇长度
#define False 0		//假值
#define True 1		//真值
#define height 20	//游戏高度
#define width 40	//游戏宽度

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'


void gotoxy(int x,int y);	//设置控制台的光标位置.
void init_map();		//初始化地图
void update_food();		//更新食物
void snake_move();		//蛇移动位置
int  is_alive();		//蛇是否存活
void is_food();			//判断食物是否被吃

struct Snake{
	int status;	//蛇的状态生死
	int len;	//蛇的长度
	int x[Max];	//蛇的x坐标
	int y[Max];	//蛇的y坐标
	char direction;	//蛇的方向
}snake;
struct Food
{
	int status;
	int x;		//食物的x坐标
	int y;		//食物的y坐标
}food;


int main()
{
	init_map();
	while(True)
	{
		update_food();
		snake_move();
		if(!is_alive())
			break;
		Sleep(800);
	}
	printf("\nGame Over!");
	getchar();
	return 0;
}


void gotoxy(int x, int y)
{
    COORD coord = {x, y};

    /*COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。其定义为：
  
    typedef struct _COORD {

    SHORT X; // horizontal coordinate

    SHORT Y; // vertical coordinate

    } COORD;*/

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    
    /*	GetStdHandle(DWORD nStdHandle)  返回标准的输入、输出或错误的设备的句柄，也就是获得输入、输出/错误的屏幕缓冲区的句柄。
    
	SetConsoleCursorPosition()是API中定位光标位置的函数.  */
}

void init_map()
{
	srand(time(NULL));
	food.y=rand()%(height+2)-1;
	food.x=rand()%(width+2)-1;
	food.status=0;
	gotoxy(food.x,food.y);
	printf("!");

	for(int i=0;i<Max;i++)
	{
		snake.x[i]=0;
		snake.y[i]=0;
	}
	snake.x[0]=width/2;
	snake.y[0]=height/2;
	snake.len=1;
	snake.status=True;
	snake.direction=UP;

	for(int i=0;i<snake.len;i++)
	{
		gotoxy(snake.x[i],snake.y[i]);
		printf("#");
	}				//初始化蛇并显示蛇

	for(int i=0;i<=width;i++)
	{
		gotoxy(i,0);
		printf("@");
		gotoxy(i,height);
		printf("@");
	}

	for(int i=0;i<=height;i++)
	{
		gotoxy(0,i);
		printf("@");
		gotoxy(width,i);
		printf("@");
	}				//打印两个墙
}

void update_food()			//更新食物
{
	if(snake.x[snake.len-1]==food.x&&snake.y[snake.len-1]==food.y)
	{
		srand(time(NULL));
		food.y=rand()%(height-2)+1;
		food.x=rand()%(width-2)+1;
		gotoxy(food.x,food.y);
		printf("*");
		snake.len++;
		food.status=1;
		snake.x[snake.len-1]=snake.x[snake.len-2];
		snake.y[snake.len-1]=snake.y[snake.len-2];
	}
}

int is_alive()				//判读蛇的存活状态
{
	if(snake.x[snake.len-1]==0||snake.x[snake.len-1]==width||snake.y[snake.len-1]==0||snake.y[snake.len-1]==height)
	{
		snake.status=False;
	}

	for(int i=0;i<snake.len-3;i++)
	{
		if(snake.x[snake.len-1]==snake.x[i]&&snake.y[snake.len-1]==snake.y[i])
		{
			snake.status=False;
		}
	}

	return snake.status;
}

void snake_move()
{
	if(kbhit())	snake.direction=getch();
		gotoxy(snake.x[0],snake.y[0]);
		printf(" ");
		food.status=0;
	for(int i=0;i<snake.len-1;i++)
	{
		snake.x[i]=snake.x[i+1];
		snake.y[i]=snake.y[i+1];
	}
	switch(snake.direction)
	{
		case UP:snake.y[snake.len-1]--;break;
		case DOWN:snake.y[snake.len-1]++;break;
		case RIGHT:snake.x[snake.len-1]++;break;
		case LEFT:snake.x[snake.len-1]--;break;
		default: break;
	}
	
	gotoxy(snake.x[snake.len-1],snake.y[snake.len-1]);
	printf("#");
}
