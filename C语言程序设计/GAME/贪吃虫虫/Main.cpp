#include "C.H"
int main(){
  int c=1,t=1;
  register int x;
  S.LONG=1;
  while(t){
	  puts("�����������ʼ��ʼ����Ϸ!~~");
	  getch();
  CreateMap();
  Sleep(500);
     puts("��ͼ��ʼ�����!~~");
	 Sleep(500);
	  if(S.LONG!=1)
	  CreateS(W/2,H/2,S.LONG,4);
	  else
       CreateS(W/2,H/2,LENGTH,4);
	  puts("����������!~~");
	  Sleep(500);
	  Create0();
	  C=1;
	  puts("�����������!~~");
	  Sleep(500);
       RefreshS();
	   puts("��ͼ�������!~~");
	  Sleep(1500);
	  puts("�����������ʼ!~~");
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
  puts("�����ˣ��Ƿ�ѡ�����¼���������Ϸ��\n1 ����\n2 �˳�");
  scanf("%d",&t);
  t=2-t;}
  return 0;
}