#include <stdio.h>
#include "MG.h"
int main(){
	int t=1,x=1;
	while(t){
		gk++;
		win=1;
		c=0;
		puts("���ڴ����Թ���ͼ~~~");
		createmap();
		Sleep(300);
		puts("���ڳ�ʼ���Թ�~~~");
		setmap();
		Sleep(500);
		puts("���ڳ�ʼ�����Ӻͳ���~~~");
		createflags(flags=gk+rand()%gk+1);
		puts("�����Թ����~~~");
		Sleep(500);
		showmap();
		puts("���������ʼ��Ϸ!~~~");
		getch();
		while(showgame()){
			system("cls");
			if(kbhit())
				moveo(getch());
			Sleep(TIME);
		}
		puts("�ɹ�������һ��~~~");
		puts("�밴���������~~~");
		system("pause");
	}
	return 0;
}