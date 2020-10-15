
/*******************

 感谢DM_LongLong的思路指导
  By DM_Gray 2018.10.28
           v1.14

	 ********************/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#define C_H 16 //定义高度
#define C_W 32 //定义宽度
#define C_UP 72  //获取方向键ASCII码
#define C_DN 80
#define C_LT 75
#define C_RT 77
#define C_MAX 200 //定义虫虫最大长度
#define C_TIMEROUT 0 //刷新频率(ms)
#define C_LENGTH 3 //初始长度
int C_p[C_H][C_W]; //定义战场范围
int C_F; //判断目前方向
int C_FT; //判断尾部方向
int C_G=0; //分数
int C_C=0; //奶酪个数
int C_t=1; //中途是否退出
struct C_M{  //定义虫虫 
    long X; //X Y为虫头相对坐标
	long Y;
	long LONG; //长度
	long LX; //尾部相对坐标
	long LY;
	long XY[2][C_MAX]; //虫虫各个节的长度以及坐标
}C_S;
void CreateMap(){ //生成地图
   register	int i,j;
	for(i=0;i<C_H;i++)
		for(j=0;j<C_W;j++)
			if(i==0||i==C_H-1||j==0||j==C_W-1)
				C_p[i][j]=37;
			else
				C_p[i][j]=32;

}
void Create0(){ //创建奶酪
    register long h,w; 
	while(C_p[h=rand()%C_H][w=rand()%C_W]!=32);
	C_p[h][w]=35;
}
void CreateS(long x,long y,long l,int u){ //生成相对坐标X Y,长度为l,方向系数为u的虫虫
  register int i;
   C_S.X=x;
   C_S.Y=y;
   C_S.LONG=l;
   C_p[C_S.Y][C_S.X]=64;
   C_S.XY[0][0]=C_S.Y;
   C_S.XY[1][0]=C_S.X;
   switch(u){
   case 1:
	   for(i=1;i<l;i++){
		    if(C_S.Y+i<C_H-1)
		   C_p[C_S.Y+i][C_S.X]=42;
	   C_S.XY[0][i]=C_S.Y+i;
	   C_S.XY[1][i]=C_S.X;}
	   C_F=C_FT=C_UP;
	   break;
	   case 2:
	   for(i=1;i<l;i++){
		   if(C_S.Y-i>0)
		   C_p[C_S.Y-i][C_S.X]=42;
	   C_S.XY[0][i]=C_S.Y-i;
	   C_S.XY[1][i]=C_S.X;}
	   C_F=C_FT=C_DN;
	   break;
	   case 3:
	   for(i=1;i<l;i++){
		   if(C_S.X+i<C_W-1)
		   C_p[C_S.Y][C_S.X+i]=42;
	   C_S.XY[0][i]=C_S.Y;
	   C_S.XY[1][i]=C_S.X+i;}
	   C_F=C_FT=C_LT;
	   break;
	   case 4:
	   for(i=1;i<l;i++){
		   if(C_S.X-i>0)
		   C_p[C_S.Y][C_S.X-i]=42;
	   C_S.XY[0][i]=C_S.Y;
	   C_S.XY[1][i]=C_S.X-i;}
	   C_F=C_FT=C_RT;
	   break;
   }
   C_S.LY=C_S.XY[0][l-1];
   C_S.LX=C_S.XY[1][l-1];
}
void MoveS(int c){ //方向键转向,同时避免自交
	switch(c){
	case C_UP:if(C_F!=C_DN) C_F=C_UP;
		break;
		case C_DN:if(C_F!=C_UP) C_F=C_DN;
		break;
		case C_LT:if(C_F!=C_RT) C_F=C_LT;
		break;
		case C_RT:if(C_F!=C_LT) C_F=C_RT;
		break;
		case 'X': 
			C_t=0;
			system("cls");
			break;
	}
}
void AddS(){ //吃奶酪长身体
  register int i;
	C_S.LONG+=1;
  C_G+=rand()%(C_S.LONG/3)+1;
  switch(C_FT){
  case C_UP:C_S.XY[0][C_S.LONG-1]=C_S.LY;
	   C_S.XY[1][C_S.LONG-1]=C_S.LX;
	   C_p[C_S.LY][C_S.LX]=42;
	  break;
  case C_DN:C_S.XY[0][C_S.LONG-1]=C_S.LY;
	  C_S.XY[1][C_S.LONG-1]=C_S.LX;
	  C_p[C_S.LY][C_S.LX]=42;
	  break;
	  case C_LT:C_S.XY[0][C_S.LONG-1]=C_S.LY;
	  C_S.XY[1][C_S.LONG-1]=C_S.LX=C_S.LX;
	  C_p[C_S.LY][C_S.LX]=42;
	  break;
	  case C_RT:C_S.XY[0][C_S.LONG-1]=C_S.LY;
	  C_S.XY[1][C_S.LONG-1]=C_S.LX;
	  C_p[C_S.LY][C_S.LX]=42;
	  break;
  }
   if(!(--C_C))
  for(i=0;i<(long)sqrt(C_S.LONG);i++,C_C++)
  Create0();
}
int Set(){ //尾部放到前头，然后从后往前逐个将数组对应，实现移动
  register int i;
 C_S.LX=C_S.XY[1][C_S.LONG-1];
  C_S.LY=C_S.XY[0][C_S.LONG-1];
  if(C_S.LY>0&&C_S.LY<C_H-1&&C_S.LX>0&&C_S.LX<C_W-1)
  C_p[C_S.LY][C_S.LX]=32;
  for(i=C_S.LONG-1;i>0;i--){
      C_S.XY[0][i]=C_S.XY[0][i-1];
	  C_S.XY[1][i]=C_S.XY[1][i-1];
  }
  C_p[C_S.Y][C_S.X]=42;
  switch(C_F){
  case C_UP:
	  if(C_p[C_S.Y-1][C_S.X]!=42){
		  if(C_S.Y-1==0) C_S.Y=C_H-1;
		if(C_p[C_S.Y-1][C_S.X]==35)
			AddS();
		  C_p[C_S.Y-1][C_S.X]=64;
	  C_S.Y-=1;
	  C_S.XY[0][0]=C_S.Y;
	  C_S.XY[1][0]=C_S.X;
	  C_FT=C_F;}
	  else return 0;
	  break;
	  case C_DN:
	  if(C_p[C_S.Y+1][C_S.X]!=42){
		  if(C_S.Y+1==C_H-1) C_S.Y=0;
		  if(C_p[C_S.Y+1][C_S.X]==35)
			AddS();
		  C_p[C_S.Y+1][C_S.X]=64;
	  C_S.Y+=1;
	  C_S.XY[0][0]=C_S.Y;
	  C_S.XY[1][0]=C_S.X;
	  C_FT=C_F;}
	  else return 0;
	  break;
	  case C_LT:
	  if(C_p[C_S.Y][C_S.X-1]!=42){
		  if(C_S.X-1==0) C_S.X=C_W-1;
		  if(C_p[C_S.Y][C_S.X-1]==35)
			AddS();
		  C_p[C_S.Y][C_S.X-1]=64;
	  C_S.X-=1;
	  C_S.XY[1][0]=C_S.X;
	  C_S.XY[0][0]=C_S.Y;
	  C_FT=C_F;}
	  else return 0;
	  break;
	  case C_RT:
	  if(C_p[C_S.Y][C_S.X+1]!=42){
		  if(C_S.X+1==C_W-1) C_S.X=0;
		  if(C_p[C_S.Y][C_S.X+1]==35)
			AddS();
		  C_p[C_S.Y][C_S.X+1]=64;
	  C_S.X+=1;
	  C_S.XY[1][0]=C_S.X;
	  C_S.XY[0][0]=C_S.Y;
	  C_FT=C_F;}
	  else return 0;
	  break;
  }
 return 1;
}
void ShowS(){ //得分显示
  printf("得分:%ld 长度:%ld - <按下 X 键结束游戏>\n",C_G,C_S.LONG);
}
int RefreshS(){ //刷新
 register int i,j;
  system("cls");
  ShowS();
  if(Set()){
  for(i=0;i<C_H;i++){
		for(j=0;j<C_W;j++)
			putchar(C_p[i][j]);
  putchar('\n');}
  return 1;}else
	  return 0;
}
