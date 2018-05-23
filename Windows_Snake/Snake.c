#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>

#define Max 100 	//最大蛇长度
#define False 0		//假值
#define True 1		//真值
#define height 20	//游戏高度
#define width 40	//游戏宽度
#define abs(x) (((x)>0)?(-x):(x))

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'


void gotoxy(int x,int y);	//设置控制台的光标位置.
void init_map();		//初始化地图
void rand_fplace();		//随机生成食物的位置
void update_food();		//更新食物
void snake_move();		//蛇移动位置
int  is_alive();		//蛇是否存活
void is_food();			//判断食物是否被吃
void snake_direction(char ch);	//改变蛇的方向
void show_data();

struct Snake{
	int status;	//蛇的状态生死
	int len;	//蛇的长度
	int x[Max];	//蛇的x坐标
	int y[Max];	//蛇的y坐标
	char direction;	//蛇的方向
	int speed;	//蛇的速度
}snake;
struct Food
{
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
		Sleep(300);
		show_data();

	}
	gotoxy(width/2-5,height/2);
	printf("Game Over!");
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
	food.y=rand()%(height-2)+1;
	food.x=rand()%(width-2)+1;
	gotoxy(food.x,food.y);
	printf("*");

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
		rand_fplace();
		gotoxy(food.x,food.y);
		printf("*");
		snake.len++;
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
	char ch;
	if(kbhit())
		ch=getch();
	else
		ch=snake.direction;

	gotoxy(snake.x[0],snake.y[0]);
	printf(" ");
	
	for(int i=0;i<snake.len-1;i++)	//移动蛇的位置
	{
		snake.x[i]=snake.x[i+1];
		snake.y[i]=snake.y[i+1];
	}

	switch(ch)		//当蛇的长度小于2的时候可以任意改变蛇的方向，其他时候不能向后走;
	{
		case UP:if(snake.direction!=DOWN||snake.len<=1){snake_direction(UP);snake.direction=UP;}else snake_direction(DOWN);break;
		case DOWN:if(snake.direction!=UP||snake.len<=1){snake_direction(DOWN);snake.direction=DOWN;}else snake_direction(UP);break;
		case RIGHT:if(snake.direction!=LEFT||snake.len<=1){snake_direction(RIGHT);snake.direction=RIGHT;}else snake_direction(LEFT);break;
		case LEFT:if(snake.direction!=RIGHT||snake.len<=1){snake_direction(LEFT);snake.direction=LEFT;}else snake_direction(RIGHT);break;
		default:snake_direction(snake.direction);break;
	}
	
	gotoxy(snake.x[snake.len-1],snake.y[snake.len-1]);
	printf("#");
}

void snake_direction(char ch)	//改变蛇的方向
{
	switch(ch)
	{
		case UP:snake.y[snake.len-1]--;break;
		case DOWN:snake.y[snake.len-1]++;break;
		case RIGHT:snake.x[snake.len-1]++;break;
		case LEFT:snake.x[snake.len-1]--;break;
	}
}

void rand_fplace()		//随机食物地址生成函数
{
	int flag=1;
	while(flag)
	{
		srand(time(NULL));
		food.y=rand()%(height-2)+1;
		food.x=rand()%(width-2)+1;
		for(int i=0;i<snake.len;i++)
		{
			if(food.x==snake.x[i]&&food.y==snake.y[i])
			{
				flag=1;
				break;
			}
			else
				flag=0;
		}
	}
}

void show_data()
{
	gotoxy(width+5,height/2-1);
	printf("snake len=%d",snake.len);
	gotoxy(width+5,height/2+1);
	printf("snake speed=%d",snake.speed);
}
