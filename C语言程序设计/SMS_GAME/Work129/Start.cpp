
/*******************

 感谢DM_LongLone的CMDER解释
  By DM_Gray 2018.12.10
           v0.14

	 ********************/

#include <stdio.h>
#include <conio.h>
#include "Set.h"
#include "GSH.H"
#include "C.H"
#include "MG.h"
#include <windows.h>


//********globals//

bool CSHLoop=1;
char adminuser[100]="admin";
char adminpwd[64]="123";
hd *table=(hd*)malloc(sizeof(hd));
int table_cont=0;

//endglobals*********//

//administior setting
bool selectas(char);
bool inita();
bool inserta();
bool dela();
bool checka();
bool xga();
bool sorta();
bool showa();
bool inputa();
bool outputa();
bool xgadminuser();
bool xgadminpwd();
bool alogin();
bool aset(){
	system("cls");
	  setbuf(stdin,NULL);
    char c;
	bool loop=1;
	while(loop){
		system("cls");
		setbuf(stdin,NULL);
	printf("<!--        管理员 <%s> 欢迎您!          --!>\n",adminuser);
	 puts("--------------------------------------------");
	 puts("| ( A )  <操作> 学生数据表; ");
     puts("| ( B ) 向 <某个位置插入> 学生数据; ");
	 puts("| ( C )  <删除> 某个学生数据;");
	 puts("| ( D )  <查询> 某个学生数据;");
	 puts("| ( E )  <修改> 某个学生数据;");
	 puts("| ( F ) 对所有数据进行 <排序> ;");
	 puts("| ( G ) 一次性 <历出> 所有学生数据; ");
	 puts("| ( H )  <导入> 学生数据;");
	 puts("| ( I )  <导出> 学生数据;");
	 puts("| ( J ) !-- <修改> 管理员用户名;");
     puts("| ( K ) !-- <修改> 管理员密码;"); 
	 puts("| ( L ) 退出登陆;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
	  printf("%c\n",c=getch());
	  if(!selectas(c))
		  return false;
		   else continue;
	}
	 return true;

}
   //A{ 

bool inita(){
	setbuf(stdin,NULL);
	system("cls");
   char c;
   char k;
   register int i,j;
   int index;
   bool loop=1;
   hd *tp;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--   <操作> 学生数据表[已有表数:%d]    --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 初始化新数据表; ");
	 puts("| ( B ) 显示当前所有表; ");
	 puts("| ( C ) 删除数据表; ");
	 puts("| ( D ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 char *name;
			 printf("请输入新建的第[%d]个表名称:",table_cont+1);
			 name=g_input();
		   if(table_cont>0){
			   hd *tmp=(hd*)malloc(sizeof(hd)*table_cont);
			  for(i=0;i<table_cont;i++)
				  *(tmp+i)=*(table+i);
			   table=(hd*)malloc(sizeof(hd)*(table_cont+1));
			   for(i=0;i<table_cont;i++)
				 *(table+i)=*(tmp+i);
			  initlist(*(table+table_cont),name);
		   }else
              initlist(*table,name);
		   printf("新建表 <%s> 完毕[已有表数%d]\n",name,++table_cont);
		 }
		 if(c=='B'){
			 printf("显示当前所有表[已有表数%d]\n",table_cont);
			  for(i=0;i<table_cont;i++)
				  printf("[Count %d]: <%s> -> {Length %d}\n",i+1,(*(table+i)).name,lenlist(*(table+i)));
		 }
		 if(c=='C'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
			 printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要删除数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
	
             printf("是否开始对 <[Count %d]:%s -> {Length %d}> 进行删除操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			  printf("请输入 (Y/N) ");
			  setbuf(stdin,NULL);
			  if((k=getchar())!='Y')
				  break;
			  if(table_cont-1==0){
				  tp=&*table;
			  printf("删除 <%s> 完成!\n",(*tp).name);
			  table=NULL;
			  table_cont--;
			  free(tp);
			   continue;
			  }
			    tp=(hd*)malloc(sizeof(hd)*table_cont);
				 for(i=0;i<table_cont;i++)
                   *(tp+i)=*(table+i);
				 table=(hd*)malloc(sizeof(hd)*(table_cont-1));
				  for(i=0,j=0;i<table_cont;i++)
					  if(i!=index-1)
						  *(table+j++)=*(tp+i);
					  printf("删除 <%s> 完成!\n",(*(tp+index-1)).name);
					  table_cont--;
		   }else
			    printf("输入的索引错误!\n");
		 }
		 if(c=='D'){
           loop=0;
		   puts("返回!");
		 }
		 }
	return true;
}
   //B{
bool inserta(){
	setbuf(stdin,NULL);
	system("cls");
  char c;
   register int i;
   int index,location;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--向 <某个位置插入> 学生数据[已有表数:%d]--!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 插入数据; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要插入数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			   while(1){
             printf("开始对 <[Count %d]:%s -> {Length %d}> 进行插入操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("请输入需要插入的[位置]:");
              if(!scanf("%d",&location)) continue;
			 if(insertlist(*(table+index-1),location))
				 printf("成功插入数据 -> [Location %d] 0 error(s), 0 warning(s)\n",location);
				 
               puts("请选择当前操作:");
			   puts("| ( A ) 继续插入数据;");
	           puts("| ( B ) 停止插入数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					break;
			 }

		   }else
			   printf("输入的索引错误!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
	return true;
}
   //C{
     bool dela(){
		 setbuf(stdin,NULL);
		 system("cls");
  char c;
   register int i;
   int index,location;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--  <删除> 某个学生数据[已有表数:%d]  --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 删除数据; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要删除数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			   while(true){
             printf("开始对 <[Count %d]:%s -> {Length %d}> 进行删除操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("请输入需要删除的[位置]:");
              if(!scanf("%d",&location)) continue;
				  if(delelist(*(table+index-1),location))
					  printf("删除 <%d> 位置数据成功!\n",location);
				  else
					printf("输入的位置不正确![1 -> %d]\n",lenlist(*(table+index-1)));
               puts("请选择当前操作:");
			   puts("| ( A ) 继续删除数据;");
	           puts("| ( B ) 停止删除数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				 if(c!='A')
				break;
			 }

		   }else
			   printf("输入的索引错误!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
   return true;}
   //D{
bool checka(){
	setbuf(stdin,NULL);
	system("cls");
	char c,msg[][12]={"<序号>","<姓名>","<性别>","<用户名>","<索引>"},*in;
   register int i;
   int index;
   long f;
   bool loop=1,np=1;
    list *p;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!--  <查询> 某个学生数据[已有表数:%d]  --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 查询数据; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要查询数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			 while(np){
		     printf("开始对 <[Count %d]:%s -> {Length %d}> 进行查询操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("请选择需要查询的内容[检索]:\n");
			 for(i=0;i<5;i++)
				 printf("| ( %c ) 按照 %s ; \n",65+i,msg[i]);
			 printf("你的选择:");
			 printf("%c\n",c=getch());
			 if(c=='A'){
				 printf("请输入 %s :",msg[0]);
				 scanf("%ld",&f);
				 p=checklistint(*(table+index-1),f);
				  if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
					 p=checklistint(p,f);
				 }
				 printf("[<--------------END--------------->]\n");
			 }else if(c!='E'){
				 printf("请输入 %s :",msg[c-'A']);
				 setbuf(stdin,NULL);
                in=g_input();
				p=checkliststr(*(table+index-1),c-'B',in);
				if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
					 p=checkliststr(p,c-'B',in);
				 }
				 printf("[<--------------END--------------->]\n");
			 }
			 else{
				 printf("请输入 %s :",msg[4]);
				 scanf("%ld",&f);
                  p=relist(*(table+index-1),f);
				   if(p==NULL) printf("[<-------------------------------->]\n");
				  if(p!=NULL){
                    printf("[<-------------------------------->]\n");
					printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
				  }
				  printf("[<--------------END--------------->]\n");
			 }
			 
               puts("请选择当前操作:");
			   puts("| ( A ) 继续查询数据;");
	           puts("| ( B ) 停止查询数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
				break;
			 }
		   }else
			   printf("输入的索引错误!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
	return true;
}


   //E{

   bool xga(){
	   setbuf(stdin,NULL);
	   system("cls");
	char c,k,msg[][12]={"<序号>","<姓名>","<性别>","<用户名>","<索引>"},*in;
	char msg1[][12]={"<序号>","<姓名>","<性别>","<成绩>","<信息>","<用户名>","<密码>"};
   register int i;
   int index;
   long f;
   bool loop=1,np=1;
    list *p;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!--  <修改> 某个学生数据[已有表数:%d]  --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 修改数据; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要修改数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			 while(np){
				 k='N';
		     printf("开始对 <[Count %d]:%s -> {Length %d}> 进行修改操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("请选择需修改的表的位置[检索]:\n");
			 for(i=0;i<5;i++)
				 printf("| ( %c ) 按照 %s 检索; \n",65+i,msg[i]);
			 printf("你的选择:");
			 printf("%c\n",c=getch());
			 if(c=='A'){
				 printf("请输入 %s :",msg[0]);
				 scanf("%ld",&f);
				 p=checklistint(*(table+index-1),f);
				  if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
					 puts("是否选择修改这个表内容? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
					p=checklistint(p,f);
				 }
				 printf("[<--------------END--------------->]\n");
				 if(k=='Y'){
					 while(1){
                    printf("请选择需要修改的内容[类型]:\n");
						for(i=0;i<7;i++)
							printf("| ( %c ) 修改 %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) 返回; \n",65+i);
						printf("你的选择:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("修改 %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
				 }
			 }else if(c!='E'){
				 printf("请输入 %s :",msg[c-'A']);
				 setbuf(stdin,NULL);
                in=g_input();
				p=checkliststr(*(table+index-1),c-'B',in);
				if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
					 puts("是否选择修改这个表内容? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
				     p=checkliststr(p,c-'B',in);
				 }
				 printf("[<--------------END--------------->]\n");
				  if(k=='Y'){
					 while(1){
                    printf("请选择需要修改的内容[类型]:\n");
						for(i=0;i<7;i++)
							printf("| ( %c ) 修改 %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) 返回; \n",65+i);
						printf("你的选择:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("修改 %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
				 }
			 }
			 else{
				 printf("请输入 %s :",msg[4]);
				 scanf("%ld",&f);
                  p=relist(*(table+index-1),f);
				   if(p==NULL) printf("[<-------------------------------->]\n");
				  if(p!=NULL){
                    printf("[<-------------------------------->]\n");
					printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
					 puts("是否选择修改这个表内容? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
				  }
				  printf("[<--------------END--------------->]\n");
				   if(k=='Y'){
					 while(1){
                    printf("请选择需要修改的内容[类型]:\n");
						for(i=0;i<7;i++)
							printf("| ( %c ) 修改 %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) 返回; \n",65+i);
						printf("你的选择:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("修改 %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
				 }
			 }
			 
               puts("请选择当前操作:");
			   puts("| ( A ) 继续查询并修改数据;");
	           puts("| ( B ) 停止查询并修改数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
				break;
			 }
		   }else
			   printf("输入的索引错误!\n");
		   }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
	return true;
}
   //F{

  bool sorta(){
	  setbuf(stdin,NULL);
	  system("cls");
	char c,msg[][12]={"<序号>","<姓名>","<性别>","<成绩>","<信息>","<用户名>"};
   register int i;
   int index;
   bool loop=1,np=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!-- 对所有数据进行 <排序> [已有表数:%d] --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 进行排序; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要查询数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			 while(np){
		     printf("开始对 <[Count %d]:%s -> {Length %d}> 进行排序操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("请选择需要进行排序的内容[类型]:\n");
			 for(i=0;i<12;i+=2){
				 printf("| ( %c ) 按照 %s [升序 -> 从小到大]; \n",65+i,msg[i/2]);
				 printf("| ( %c ) 按照 %s [降序 -> 从大到小]; \n",65+i+1,msg[i/2]);
			 }
			 printf("你的选择:");
			 printf("%c\n",c=getch());
			  if(sort(*(table+index-1),c-'A'))
			     printf("排序完成!\n");
               puts("请选择当前操作:");
			   puts("| ( A ) 继续进行排序数据;");
	           puts("| ( B ) 停止进行排序数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				 if(c!='A')
					 break;
			 }
		   }else
			   printf("输入的索引错误!\n");
		 }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
	return true;
}

  //G{

  bool showa(){
	  setbuf(stdin,NULL);
	  system("cls");
  char c;
   register int i,j;
   int index;
   bool loop=1;
   list *p;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--一次性 <历出> 所有学生数据[已有表数:%d]--!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 历出数据; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要历出数据的表[索引]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
             printf("开始对 <[Count %d]:%s -> {Length %d}> 进行历出操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 j=1;
			 p=relist(*(table+index-1),j);
             if(p==NULL)
				 printf("[<-------------------------------->]\n");
			 while(p!=NULL){
				 printf("[<-------------------------------->]\n");
				 printf(" <索引号> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <序号> : %ld\n",p->num);
					 printf(" <姓名> : %s\n",p->name);
					 printf(" <性别> : %s\n",p->sex);
					 printf(" <信息> : %s\n",p->text);
					 printf(" <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <用户名> : %s\n",p->user);
					 printf(" <密码> : %s\n",p->password);
					 p=relist(*(table+index-1),++j);}
				  
				 printf("[<--------------END--------------->]\n");
               puts("请选择当前操作:");
			   puts("| ( A ) 继续历出数据;");
	           puts("| ( B ) 停止历出数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		   }else
			   printf("输入的索引错误!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
  return true;}

  //H{

  bool inputa(){
	  system("cls");
	  setbuf(stdin,NULL);
  char c,*in,*out;
   register int i;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--    <导入> 学生数据[已有表数:%d]    --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 覆盖导入数据; ");
	 puts("| ( B ) 默认导入数据;");
	 puts("| ( C ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'||c=='B'){
			 table_cont>0?printf("当前所有表:\n"):printf("当前没有表!\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要导入数据的表的位置[绝对路径]:");
		    in=g_input();
             printf("开始对 <%s.dat> 进行导入操作:\n",in);
			   if((out=listinput(in,c-'A',table,table_cont))!=NULL)
				   printf("已成功导入表 <%s> \n",out);
               puts("请选择当前操作:");
			   puts("| ( A ) 继续导入数据;");
	           puts("| ( B ) 停止导入数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }	 
		 if(c=='C'){
			 loop=0;
                puts("返回!");
		 }
		 }
   return true;}


   //I{

	bool outputa(){
		system("cls");
	  setbuf(stdin,NULL);
  char c,*in;
   register int i;
   int index;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--    <导出> 学生数据[已有表数:%d]    --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 覆盖导出数据; ");
	 puts("| ( B ) 默认导出数据;");
	 puts("| ( C ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'||c=='B'){
			 if(!table_cont) {printf("目前表数为0,无法进行操作!\n");
			 continue;}
		   printf("当前所有表:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("请选择要导出数据的表[索引]:");
		   scanf("%d",&index);
		   setbuf(stdin,NULL);
		   if(index<=table_cont&&index>0){
             printf("开始对 <[Count %d]:%s -> {Length %d}> 进行导出操作:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("请输入需要导出的位置[绝对路径]:");
              in=g_input();
			   if(listoutput(*(table+index-1),in,c-'A'))
				   printf("已成功输出到 <%s.txt> | <%s.dat> \n",in,in);
               puts("请选择当前操作:");
			   puts("| ( A ) 继续导出数据;");
	           puts("| ( B ) 停止导出数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		   }else
			   printf("输入的索引错误!\n");
		 }	 
		 if(c=='C'){
			 loop=0;
                puts("返回!");
		 }
		 }
   return true;}
   //J{

	bool xgadminuser(){
		system("cls");
	  setbuf(stdin,NULL);
  char c,*in,*inf;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--         <修改> 管理员用户名        --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 修改用户名; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("请输入 <旧的用户名> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,adminuser))
              { puts("用户名不正确!终止!");
                    continue;
			  }
			  printf("请输入 <新的用户名> -> ");
			  in=g_input();
			   g_scp(adminuser,in);
			   printf("<Username> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,adminuser);
               puts("请选择当前操作:");
			   puts("| ( A ) 继续修改用户名;");
	           puts("| ( B ) 停止修改用户名;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
   return true;}

   //K{

   bool xgadminpwd(){
	   system("cls");
	  setbuf(stdin,NULL);
  char c,*in[2],*inf;
   bool loop=1,bt=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   bt=1;
    printf("<!--          <修改> 管理员密码         --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 修改密码; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("请输入 <旧的密码> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,adminpwd))
              { puts("密码不正确!终止!");
                    continue;
			  }
			  while(bt){
			  printf("请输入 <新的密码> -> ");
			  *in=g_input();
			  printf("请再次输入 <新的密码> -> ");
			  *(in+1)=g_input();
			   if(!g_strbj(*in,*(in+1)))
                  { puts("两次密码不相同!请重新输入!");
                    continue;
			  }
			   g_scp(adminpwd,*in);
			   printf("<Password> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,adminpwd);
			  bt=0;
			  }puts("请选择当前操作:");
			   puts("| ( A ) 继续修改密码;");
	           puts("| ( B ) 停止修改密码;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
			 }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
   }
   return true;}


   

//--- end ---

//user set
bool selectus(char,list *);
bool xgu(list *);
bool outputu(list *);
bool xguser(list*);
bool xgpwd(list*);

bool uset(list *p){
	system("cls");
	  setbuf(stdin,NULL);
    char c;
	bool loop=1;
	register int i;
	while(loop){
		system("cls");
		setbuf(stdin,NULL);
	printf("<!--        学生 <%s> 欢迎您!          --!>\n",p->name);
	 puts("--------------------------------------------");
	printf(" <序号> : %ld\n",p->num);
	printf(" <姓名> : %s\n",p->name);
	printf(" <性别> : %s\n",p->sex);
    printf(" <信息> : %s\n",p->text);
	printf(" <成绩> : {\n");
	for(i=0;i<MAX_CON-1;i++)
	printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
       printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
		printf(" <用户名> : %s\n",p->user);
	printf(" <密码> : %s\n",p->password);
	puts("--------------------------------------------");
	 puts("| ( A )  <修改> 某个数据;");
	 puts("| ( B )  <导出> 学生数据;");
	 puts("| ( C ) !-- <修改> 用户名;");
     puts("| ( D ) !-- <修改> 密码;"); 
	 puts("| ( E ) 退出登陆;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
	  printf("%c\n",c=getch());
	  if(!selectus(c,p))
		  return false;
		   else continue;
	}
	 return true;

}

   //{A

bool xgu(list *p){
	system("cls");
	  setbuf(stdin,NULL);
	char c;
	char msg1[][12]={"<序号>","<姓名>","<性别>","<成绩>","<信息>"};
   register int i;
   bool loop=1,np=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!--          <修改> 某个数据           --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 修改数据; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
					 while(np){
                    printf("请选择需要修改的内容[类型]:\n");
						for(i=0;i<5;i++)
							printf("| ( %c ) 修改 %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) 返回; \n",65+i);
						printf("你的选择:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("修改 %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
			 }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
	return true;
}

   //B{
bool outputu(list *p){
	system("cls");
	  setbuf(stdin,NULL);
  char c,*in;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--          <导出> 数据[%s]          --!>\n",p->name);
	 puts("--------------------------------------------");
	 puts("| ( A ) 覆盖导出数据; ");
	 puts("| ( B ) 默认导出数据;");
	 puts("| ( C ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'||c=='B'){
			 printf("请输入需要导出的位置[绝对路径]:");
              in=g_input();
			   if(listoutputu(p,in,c-'A'))
				   printf("已成功输出到 <%s.txt> \n",in);
               puts("请选择当前操作:");
			   puts("| ( A ) 继续导出数据;");
	           puts("| ( B ) 停止导出数据;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }
		 if(c=='C'){
			 loop=0;
                puts("返回!");
		 }
		 }
   return true;}

   //C{

bool xguser(list *p){
	system("cls");
	  setbuf(stdin,NULL);
  char c,*in,*inf;
   bool loop=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
    printf("<!--           <修改> 用户名          --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 修改用户名; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("请输入 <旧的用户名> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,p->user))
              { puts("用户名不正确!终止!");
                    continue;
			  }
			  printf("请输入 <新的用户名> -> ");
			  in=g_input();
			   g_scp(p->user,in);
			   printf("<Username> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,p->user);
               puts("请选择当前操作:");
			   puts("| ( A ) 继续修改用户名;");
	           puts("| ( B ) 停止修改用户名;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
		 }
   return true;}

   //D{

bool xgpwd(list *p){
	system("cls");
	  setbuf(stdin,NULL);
  char c,*in[2],*inf;
   bool loop=1,bt=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   bt=1;
    printf("<!--            <修改> 密码           --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) 修改密码; ");
	 puts("| ( B ) 返回");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("请输入 <旧的密码> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,p->password))
              { puts("密码不正确!终止!");
                    continue;
			  }
			  while(bt){
			  printf("请输入 <新的密码> -> ");
			  *in=g_input();
			  printf("请再次输入 <新的密码> -> ");
			  *(in+1)=g_input();
			   if(!g_strbj(*in,*(in+1)))
                  { puts("两次密码不相同!请重新输入!");
                    continue;
			  }
			   g_scp(p->password,*in);
			   printf("<Password> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,p->password);
			  bt=0;
			  }puts("请选择当前操作:");
			   puts("| ( A ) 继续修改密码;");
	           puts("| ( B ) 停止修改密码;");
			   printf("你的选择:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
			 }
		 if(c=='B'){
			 loop=0;
                puts("返回!");
		 }
   }
   return true;}



//--- end ---

//administior login

bool alogin(){
	setbuf(stdin,NULL);
	system("cls");
	char *in[2];
	bool loop=1;
	char c;
	while(loop){
		system("cls");
		setbuf(stdin,NULL);
     puts("<!--            管理员登陆              --!>");
	 puts("--------------------------------------------");
	 printf("| ( 1 ) 请输入用户名: ");
	 *in=g_input();
	 printf("| ( 2 ) 请输入密码: ");
	 *(in+1)=g_input();
	 printf("| ( press any key ) 登陆系统\n");
	 getch();
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	if(g_strbj(*in,adminuser)&&g_strbj(*(in+1),adminpwd))
		return aset();
	else {printf("用户名或密码错误!!!\n{ 是否重新登陆? }\n| ( A ) 重新登陆;\n| ( B ) 退出登陆\n");
	   printf("你的选择:");
	    printf("%c\n",c=getch());
		  if(c=='A')
			 continue;
		   else return true;
	}
	}
 return true;
}

//--- end ---

//user login

bool ulogin(){
	char *in[2];
	bool loop=1;
	char c;
	long num;
	system("cls");
	list *p;
	setbuf(stdin,NULL);
	if(!table_cont) {
        printf("( press any key ) 目前没有任何数据表做参考!无法进行登陆操作!\n");
		getch();
		return false;
	 }
	while(loop){
		system("cls");
		setbuf(stdin,NULL);
     puts("<!--             学生登陆              --!>");
	 puts("--------------------------------------------");
	 printf("| ( 1 ) 请输入序号: ");
	 scanf("%ld",&num);
	 setbuf(stdin,NULL);
	 printf("| ( 2 ) 请输入用户名: ");
	 *in=g_input();
	 printf("| ( 3 ) 请输入密码: ");
	 *(in+1)=g_input();
	 printf("| ( press any key ) 登陆系统\n");
	 getch();
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 
	if((p=pdlogin(num,*in,*(in+1),table,table_cont))!=NULL)
		return uset(p);
	else {printf("登陆出错!!!\n{ 是否重新登陆? }\n| ( A ) 重新登陆;\n| ( B ) 退出登陆\n");
	   printf("你的选择:");
	    printf("%c\n",c=getch());
		  if(c=='A')
			 continue;
		   else return true;
	}
	}
	return true;
}

//--- end ---

//game model
bool selectgs(char);
bool C_game();
bool M_game();

bool gamem(){
	system("cls");
 char c;
	bool loop=1;
	setbuf(stdin,NULL);
	while(loop){
		system("cls");
		setbuf(stdin,NULL);
     puts("<!--             游戏模式              --!>");
	 puts("--------------------------------------------");
	 puts("| ( A ) 贪吃虫虫; ");
	 puts("| ( B ) 迷宫夺旗; ");
	 puts("| ( C ) 退出游戏模式;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
	 printf("%c\n",c=getch());
          if( !selectgs(c) )
			  return false;
	}
	return true;
}

   //{A
bool C_game(){
 int c=1;
 int t=1;
 C_t=1;
  register int x;
  C_S.LONG=1;
  while(t){
	  puts("按下任意键开始初始化游戏!~~");
	  getch();
  CreateMap();
  Sleep(500);
     puts("地图初始化完毕!~~");
	 Sleep(500);
	  if(C_S.LONG!=1)
	  CreateS(C_W/2,C_H/2,C_S.LONG,4);
	  else
       CreateS(C_W/2,C_H/2,C_LENGTH,4);
	  puts("创建虫虫完毕!~~");
	  Sleep(500);
	  Create0();
	  C_C=1;
	  puts("创建奶酪完毕!~~");
	  Sleep(500);
       RefreshS();
	   puts("地图生成完毕!~~");
	  Sleep(1500);
	  puts("按下任意键开始!~~");
	  getch();
  while(RefreshS()&&C_t){
  //getch();
	  if(kbhit())
		  MoveS(c=getch());
	  	   Sleep(C_TIMEROUT);
  }
  
  printf("GAME OVER!\n");
  for(x=C_S.LONG-1;x>=0;x--)
	  C_S.XY[0][x]=C_S.XY[1][x]=0;
  C_S.X=C_S.Y=C_S.LX=C_S.LY=0;
  C_S.LONG=C_S.LONG/2+1;
  puts("你输了，是否选择重新继续进行游戏？\n| ( 1 ) 继续\n| ( 2 ) 退出");
  scanf("%d",&t);
  t=2-t;}
  system("cls");
	return true;
}

   //B{

bool M_game(){
   int x=1,t=1;
   M_t=1;
	while(t){
		M_gk++;
		M_win=1;
		M_c=0;
		puts("正在创建迷宫地图~~~");
		createmap();
		Sleep(300);
		puts("正在初始化迷宫~~~");
		setmap();
		Sleep(500);
		puts("正在初始化旗子和出口~~~");
		createflags(M_flags=M_gk+rand()%M_gk+1);
		puts("创建迷宫完毕~~~");
		Sleep(500);
		showmap();
		puts("按任意键开始游戏!~~~");
		getch();
		while(showgame()&&M_t){
			system("cls");
			if(kbhit())
				moveo(getch());
			Sleep(M_TIME);
		} 
		if(!M_t){
			M_gk--;
             system("cls");
			 return true;
		}
		puts("成功进入下一关~~~");
		puts("请按任意键继续~~~");
		system("pause");
	}
	system("cls");
	return true;
}

//--- end ---

//selection function Admin_setting

/*

   puts("--------------------------------------------");
	 puts("| ( A )  <初始化> 学生数据表; ");
     puts("| ( B ) 向 <某个位置插入> 学生数据; ");
	 puts("| ( C )  <删除> 某个学生数据;");
	 puts("| ( D )  <查询> 某个学生数据;");
	 puts("| ( E )  <修改> 某个学生数据;");
	 puts("| ( F ) 对所有数据进行 <排序> ;");
	 puts("| ( G ) 一次性 <历出> 所有学生数据; ");
	 puts("| ( H )  <导入> 学生数据;");
	 puts("| ( I )  <导出> 学生数据;");
	 puts("| ( J ) !-- <修改> 管理员用户名;");
     puts("| ( K ) !-- <修改> 管理员密码;"); 
	 puts("| ( L ) 退出登陆;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");

bool selectas();
bool inita();
bool inserta();
bool dela();
bool checka();
bool xga();
bool sorta();
bool showa();
bool inputa();
bool outputa();
bool xgadminuser();
bool xgadminpwd();
bool alogin();

  */

bool selectas(char c){                        
	switch(c){
	case 'A': 
		return inita();
		 break;
	case 'B': return inserta();
		break;
	case 'C': return dela(); 
		break;
	case 'D': return checka();
		break;
	case 'E': xga();
		break;
		case 'F':return sorta();
		break;
		case 'G':return showa();
		break;
     case 'H':return inputa();
		break;
		case 'I':return outputa();
		break;
		case 'J':return xgadminuser();
		break;
		case 'K':return xgadminpwd();
		break;
	case 'L': return false;
		break;
	}
	return true;
}

//--- end  ---

//selection function user_setting

/*puts("--------------------------------------------");
	 puts("| ( A )  <修改> 某个数据;");
	 puts("| ( B )  <导出> 学生数据;");
	 puts("| ( C ) !-- <修改> 用户名;");
     puts("| ( D ) !-- <修改> 密码;"); 
	 puts("| ( E ) 退出登陆;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	
 */

bool selectus(char c,list *p){                        
	switch(c){
	case 'A': 
		return xgu(p);
		break;
	case 'B' :return outputu(p);
		 break;
	case 'C' :return xguser(p);
		 break;
	case 'D': return xgpwd(p);
		 break;
	case 'E': return false;

	}
	return true;
}

//--- end ---

//selection function game_model

bool selectgs(char c){                        
	switch(c){
	case 'A': 
		return C_game();
		break;
	case 'B' :return M_game();
		 break;
	case 'C': return false;

	}
	return true;
}

//--- end ---

//selection function First

bool selectf(char c){
	switch(c){
	case 'A': ulogin();
		 break;
	case 'B': return alogin();
		break;
	case 'C':  gamem();
		break;
	case 'D':
		CSHLoop=0;
		break;
	default: return false;
	}
	return true;
}

//--- end  ---

int main(){
	char c;
    
	while(CSHLoop){
		system("cls");
     puts("<!--        学生信息管理超级系统        --!>");
	 puts("--------------------------------------------");
	 puts("| ( A ) 学生登陆; ");
	 puts("| ( B ) 管理员登陆; ");
	 puts("| ( C ) 小游戏");
     puts("| ( D ) 退出系统");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("你的选择:");
	 
		 printf("%c\n",c=getch());
          if( !selectf(c) )
	        continue;
	}

	return 0;
}