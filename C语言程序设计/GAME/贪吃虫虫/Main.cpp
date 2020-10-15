#include "C.H"
int main(){
  int c=1,t=1;
  register int x;
  S.LONG=1;
  while(t){
	  puts("按下任意键开始初始化游戏!~~");
	  getch();
  CreateMap();
  Sleep(500);
     puts("地图初始化完毕!~~");
	 Sleep(500);
	  if(S.LONG!=1)
	  CreateS(W/2,H/2,S.LONG,4);
	  else
       CreateS(W/2,H/2,LENGTH,4);
	  puts("创建虫虫完毕!~~");
	  Sleep(500);
	  Create0();
	  C=1;
	  puts("创建奶酪完毕!~~");
	  Sleep(500);
       RefreshS();
	   puts("地图生成完毕!~~");
	  Sleep(1500);
	  puts("按下任意键开始!~~");
	  getch();
  while(RefreshS()){
  //getch();
	  if(kbhit())
		  MoveS(c=getch());
	  	   Sleep(TIMEROUT);
  }
  
  printf("GAME OVER!\n");
  for(x=S.LONG-1;x>=0;x--)
	  S.XY[0][x]=S.XY[1][x]=0;
  S.X=S.Y=S.LX=S.LY=0;
  S.LONG=S.LONG/2+1;
  puts("你输了，是否选择重新继续进行游戏？\n1 继续\n2 退出");
  scanf("%d",&t);
  t=2-t;}
  return 0;
}