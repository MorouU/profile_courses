#include <stdio.h>
#include "MG.h"
int main(){
	int t=1,x=1;
	while(t){
		gk++;
		win=1;
		c=0;
		puts("正在创建迷宫地图~~~");
		createmap();
		Sleep(300);
		puts("正在初始化迷宫~~~");
		setmap();
		Sleep(500);
		puts("正在初始化旗子和出口~~~");
		createflags(flags=gk+rand()%gk+1);
		puts("创建迷宫完毕~~~");
		Sleep(500);
		showmap();
		puts("按任意键开始游戏!~~~");
		getch();
		while(showgame()){
			system("cls");
			if(kbhit())
				moveo(getch());
			Sleep(TIME);
		}
		puts("成功进入下一关~~~");
		puts("请按任意键继续~~~");
		system("pause");
	}
	return 0;
}