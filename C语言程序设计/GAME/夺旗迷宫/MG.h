
/*******************

 感谢DM_LongLone提供的灵感
  By DM_Gray 2018.11.21
           v1.10

	 ********************/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define M_UP 72  //获取方向键ASCII码
#define M_DN 80
#define M_LT 75
#define M_RT 77
#define M_L 31  //定义地图尺寸
#define M_TIME 0  //刷新频率
int M_n=0;  //记录点数
int M_c=0;  //记录访问点数
int M_xt[(M_L/2*M_L/2)+1];  //记录可访问点数坐标
int M_yt[(M_L/2*M_L/2)+1];
int M_xy[4][4];  //记录正在访问点四周坐标以及之间连线的坐标
int M_xa,M_xb; //记录你所在位置坐标以及出口所在坐标
int M_ya,M_yb;
int M_flags=0;  //旗子数量
int M_gk=0;  //关卡
int M_win=1;  //判断是否完成关卡
int M_t=1; //中途是否退出
struct {
	char c;
	int p;
}M_g[L][L];

int createmap(){ //创建地图
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
int showmap(){  //显示地图
	register int i,j;
	for(i=0;i<L;i++){
		for(j=0;j<M_L;j++)
			printf("%c",M_g[i][j].c);
		putchar('\n');}
	//
	return 1;
}
int setmap(){  //设置迷宫（类似连通图原理，保证各个点之间必有一条连线）
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
int createflags(int c){  //创建旗子
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
int moveo(int f){  //移动你自己
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
int showgame(){  //运行游戏
	printf("关卡：%d %剩余旗子:%d\n",M_gk,M_flags - <按下 X 键结束游戏>);
    showmap();
	return M_win;
}