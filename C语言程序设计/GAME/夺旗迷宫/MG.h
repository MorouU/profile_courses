
/*******************

 ��лDM_LongLone�ṩ�����
  By DM_Gray 2018.11.21
           v1.10

	 ********************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define M_UP 72  //��ȡ�����ASCII��
#define M_DN 80
#define M_LT 75
#define M_RT 77
#define M_L 31  //�����ͼ�ߴ�
#define M_TIME 0  //ˢ��Ƶ��
int M_n=0;  //��¼����
int M_c=0;  //��¼���ʵ���
int M_xt[(M_L/2*M_L/2)+1];  //��¼�ɷ��ʵ�������
int M_yt[(M_L/2*M_L/2)+1];
int M_xy[4][4];  //��¼���ڷ��ʵ����������Լ�֮�����ߵ�����
int M_xa,M_xb; //��¼������λ�������Լ�������������
int M_ya,M_yb;
int M_flags=0;  //��������
int M_gk=0;  //�ؿ�
int M_win=1;  //�ж��Ƿ���ɹؿ�
int M_t=1; //��;�Ƿ��˳�
struct {
	char c;
	int p;
}M_g[L][L];

int createmap(){ //������ͼ
	register int i,j;
	for(i=0;i<M_L;i++)
		for(j=0;j<M_L;j++)
			if(i!=0&&i!=M_L-1&&i%2!=0)
				if(j%2)
				{M_g[i][j].c=32;
				M_g[i][j].p=2;
				n++;}
				else {M_g[i][j].c='*';
				M_g[i][j].p=1;}
				else{
					M_g[i][j].c='*';
					M_g[i][j].p=1;
				}
				return 1;
}
int showmap(){  //��ʾ��ͼ
	register int i,j;
	for(i=0;i<L;i++){
		for(j=0;j<M_L;j++)
			printf("%c",M_g[i][j].c);
		putchar('\n');}
	//
	return 1;
}
int setmap(){  //�����Թ���������ͨͼԭ����֤������֮�����һ�����ߣ�
	int x,y,b=0,r,w;
	register int j;
	srand((int)time(0));
	while(M_g[y=(rand()%((M_L-1)/2)*2+1)][x=(rand()%((M_L-1)/2)*2+1)].p!=2);
    M_g[y][x].p=0;
    M_xa=M_xt[M_c]=x;
	M_ya=M_yt[M_c]=y;
	M_c++;
	M_n--;
	M_g[y][x].c='o';
	while(M_n>0){
		b=0;
		if(y-2>0&&M_g[y-2][x].p>0){
			M_xy[b][0]=y-2;
			M_xy[b][1]=x;
			M_xy[b][2]=y-1;
			M_xy[b][3]=x;
			b++;
		} 
		if(y+2<M_L-1&&M_g[y+2][x].p>0){
			M_xy[b][0]=y+2;
			M_xy[b][1]=x;
			M_xy[b][2]=y+1;
			M_xy[b][3]=x;
			b++;
		} 
		if(x-2>0&&M_g[y][x-2].p>0){
			M_xy[b][0]=y;
			M_xy[b][1]=x-2;
			M_xy[b][2]=y;
			M_xy[b][3]=x-1;
			b++;
		} 
		if(x+2<M_L-1&&M_g[y][x+2].p>0){
			M_xy[b][0]=y;
			M_xy[b][1]=x+2;
			M_xy[b][2]=y;
			M_xy[b][3]=x+1;
			b++;
		}
		if(b){
			r=rand()%b;
			M_g[M_xy[r][0]][M_xy[r][1]].p=0;
			//g[xy[r][0]][xy[r][1]].c=32;
			M_g[M_xy[r][2]][M_xy[r][3]].c=32;
			M_g[M_xy[r][2]][M_xy[r][3]].p=-1;
			x=M_xt[c]=M_xy[r][1];
			y=M_yt[c]=M_xy[r][0];
			M_c++;
			M_n--;
		}else{
			if(M_g[y][x].p==0){
				M_g[y][x].p=-1;
				for(j=0;j<c&&(x!=M_xt[j]||y!=M_yt[j]);j++);
				for(;j<c-1;j++){
					M_xt[j]=M_xt[j+1];
					M_yt[j]=M_yt[j+1];
				}
				c--;
			}
			w=rand()%M_c;
			y=M_yt[w];
			x=M_xt[w];
			
		}
		//system("cls");
		//showmap();
	}
	return 1;
}
int createflags(int c){  //��������
	int y,x;
	for(register int i=0;i<c;i++){
		while(M_g[y=(rand()%(M_L-2)+1)][x=(rand()%(M_L-2)+1)].p<-1||M_g[y][x].p>0);
		M_g[y][x].c='#';
		M_g[y][x].p=-2;	}
	while(M_g[M_yb=(rand()%(M_L-2)+1)][M_xb=(rand()%(M_L-2)+1)].p<-1||M_g[y][x].p>0);
	M_g[M_yb][M_xb].c='@';
	M_g[M_yb][M_xb].p=-3;
	return 1;
}
int moveo(int f){  //�ƶ����Լ�
	if(f=='X'){M_t=0;
			system("cls");
	}
	if(f==M_UP&&M_ya-1>0&&M_g[M_ya-1][M_xa].p<=0){
		M_g[M_ya][M_xa].c=32;
        if(M_g[M_ya-1][M_xa].c=='#') flags--;
		if(M_g[M_ya-1][M_xa].c=='@'&&!M_flags) M_win=0;
		else g[yb][xb].c='@';
		M_g[--M_ya][M_xa].c='o';
	}
	if(f==M_DN&&M_ya+1<M_L-1&&M_g[M_ya+1][M_xa].p<=0){
		M_g[M_ya][M_xa].c=32;
		if(M_g[M_ya+1][M_xa].c=='#') M_flags--;
		if(M_g[M_ya+1][M_xa].c=='@'&&!M_flags) M_win=0;
		else M_g[M_yb][M_xb].c='@';
		M_g[++M_ya][M_xa].c='o';
	}
	if(f==M_RT&&M_xa<M_L-1&&M_g[M_ya][M_xa+1].p<=0){
		M_g[M_ya][M_xa].c=32;
		if(M_g[M_ya][M_xa+1].c=='#') M_flags--;
		if(M_g[M_ya][M_xa+1].c=='@'&&!M_flags) M_win=0;
		else M_g[M_yb][M_xb].c='@';
		M_g[M_ya][++M_xa].c='o';
	}
	if(f==M_LT&&M_xa-1>0&&M_g[M_ya][M_xa-1].p<=0){
		M_g[M_ya][M_xa].c=32;
		if(M_g[M_ya][M_xa-1].c=='#') M_flags--;
		if(M_g[M_ya][M_xa-1].c=='@'&&!M_flags) M_win=0;
		else M_g[M_yb][M_xb].c='@';
		M_g[M_ya][--M_xa].c='o';
	}
	return 1;
}
int showgame(){  //������Ϸ
	printf("�ؿ���%d %ʣ������:%d\n",M_gk,M_flags - <���� X ��������Ϸ>);
    showmap();
	return M_win;
}