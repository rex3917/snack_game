# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <windows.h>			// sleep函數
# include <conio.h>				// 鍵盤輸入讀取 kbhit()  getch()
# include <time.h>				// 時間相關函數

# define MAPX 17
# define MAPY 17

# define SNAKE 1
# define FOOD 2
# define WALL 3

# define UP 72
# define DOWN 80
# define LEFT 75
# define RIGHT 77


char map[MAPX][MAPY] = {0}; // map[0][0] = 0
unsigned char snake[50] = {77}; // snake star(4, 13)
unsigned char food = 68;        // 初始位置(4, 4)
int len = 1;					// 蛇長
bool Alive = true;              // 是否活著

void print_game()
{
	for(int i = 0; i < MAPX; i ++){
		for(int j = 0; j < MAPY; j++){
			if(map[i][j] == 0){
				putchar(' ');
			}
			else if(map[i][j] == SNAKE){
				putchar('o');
			}
			else if(map[i][j] == FOOD){
				putchar('@');
			}
			else if(map[i][j] == WALL){
				putchar('#');
			}
		}
		printf("\n");
	}
	Sleep(10);     // 延遲300毫秒
	system("cls");  // 清除畫面 (刷新率)
}

 int get_dir(int old_dir)             // 讀取鍵盤操作
 {
 	int new_dir;
 	if(_kbhit()){
 		getch();           // 第一個省略
 		new_dir = getch();
		if(abs(new_dir - old_dir) != 8 && abs(new_dir - old_dir) != 2){  // 不能轉180度
			old_dir = new_dir;
		}
 	}
 	return old_dir;
 }

unsigned char generate_food(){
	unsigned char new_food, fx, fy;
	bool in_snack = false;
	srand((unsigned int)time(NULL));    //種子時間點
	do{
		new_food = (unsigned char)(rand()%255);  //亂數產生0~255
		fx = new_food >> 4;
		fy = new_food & 0x0F;
		for (int i = 0;i < len; i++)
			if(new_food == snake[i]){
				in_snack = true;
			}
	}
	while(fx == 0 || fx == MAPX-1 || fy == 0 || fy == MAPY-1 || in_snack);

	return new_food;
}

void move_snake(int dir)    	 	// 更改地圖物件
{
	int last = snake[0], item; 		// 增加蛇的長度
	unsigned char fx, fy, x, y; 	// 解碼food位置(x ,y)
	fx = food >> 4;
	fy = food & 0x0F;

	x = snake[0] >> 4;  			// snake 初始位置
	y = snake[0] & 0x0F;
	switch(dir){
		case UP:
			y--;
		break;

		case DOWN:
			y++;
		break;

		case LEFT:
			x--;
		break;

		case RIGHT:
			x++;
		break;
	}
	snake[0] = (x << 4) | y;

	if (snake[0] == food)  		// 吃到food
	{
	    food = generate_food();
		snake[len] = last;
		len++;
	}

	for (int i = 0; i < len; i++)
	{
		if (i == 0)
		{
			continue; 			// 只有一顆頭
		}
		item = snake[i];  		// swap snake[i] and last
		snake[i] = last;
		last = item;
	}

	for(int i = 0; i < MAPX; i++){
		for(int j = 0;j < MAPY;j++){
			if(i == 0 || i == MAPX-1 || j == 0 || j == MAPY-1){
				map[i][j] = WALL;
			}
			else if(i == fy && j == fx){
				map[i][j] = FOOD;
			}
			else{
                map[i][j] = 0;
			}
		}
	}

	for(int i = 0; i < len; i++)
	{
		x = snake[i] >> 4;
		y = snake[i] & 0x0F;
		if (snake[i] > 0)
		{
			if(map[y][x] == WALL || map[y][x] == SNAKE){
				Alive = false;
			}
			else{
				map[y][x] = SNAKE;
			}
		}
	}

}

int isAlive(){
	if(Alive){
		return 1;
	}
	else{
		return 0;
	}
}

void game()
{
	len = 1;					// 蛇長
	Alive = true;              // 是否活著
	unsigned char fx, fy, x, y;
	do{
		food = (unsigned char)(rand()%255);  //亂數產生0~255
		fx = food >> 4;
		fy = food & 0x0F;
	}
	while(fx == 0 || fx == MAPX-1 || fy == 0 || fy == MAPY-1);

	do{
		snake[0] = (unsigned char)(rand()%255);  //亂數產生0~255
		x = snake[0] >> 4;
		y = snake[0] & 0x0F;
	}
	while(fx == 0 || fx == MAPX-1 || fy == 0 || fy == MAPY-1 ||snake[0] ==food);


	for(int i = 0; i < MAPX; i++){
		for(int j = 0; j < MAPY; j++){
			map[i][j] = 0;           // 初始化map
		}
	}
	for(int i = 1; i < 50 ; i++){
		snake[i] = 0;                // 初始化snake
	}

	int dir = UP;
	while(1)
    {
		print_game();
		dir = get_dir(dir);
		move_snake(dir);
		if(!isAlive())
			break;
	}
	printf("Game Over!\n");
}

int main()
{
	int check;
	printf("輸入 1 開始遊戲\n 輸入 0 結束遊戲");
	while(scanf("%d", &check) != EOF){
		if(check == 1){
			game();
		printf("輸入 1 重新開始遊戲\n 輸入 0 結束遊戲");
		}
		if(check == 0){
			break;
		}
	}
	return 0;
}
