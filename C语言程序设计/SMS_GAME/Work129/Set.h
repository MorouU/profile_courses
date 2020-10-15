
#ifndef _Set_h
#define _Set_h
#define MAX_CON 3

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "GSH.H"

typedef struct hdlt{  //定义头表格
    char name[32];
	struct lt *n;
}hd;


typedef struct lt{ //每个学生的表格
  long num;
  char name[30];
  char sex[10];
  float grade[MAX_CON];
  char text[150];
  char user[20];
  char password[64];
  struct lt *n;
}list;

//globals
char Grade_students[][10]={"语文","数学","英语"};
//endglobals


bool initlist(hd &p,char *name){ //初始化表格
  p.n=NULL;
  g_scp(p.name,name);
  return true;
}

bool pdlist(list p){ //判断是否为空表
 return p.n==NULL;
}


int lenlist(hd p){  //表长
  list *w=p.n;
	for(register int i=0;w!=NULL;w=w->n,i++);
  return i;
}

int lenlist(hd *p){  //表长
  list *w=p->n;
	for(register int i=0;w!=NULL;w=w->n,i++);
  return i;
}

/*bool destroylist(hd *&p){  //摧毁表
  list *q=p->n,*w;
  while(q!=NULL){
	  q=q->n;
	  w=q;
	  free(w);
  }
  free(p);
  return true;
}*/

bool insertlist(hd &t,int i){  //插入元素
	 int tmp=i;
	if(i<=0 || i>lenlist(t)+1) {
		puts("位置输入错误!");
		return false;}
	hd *p=&t;
   list *q=p->n,*w;
    while(q!=NULL&&--i>1)
		q=q->n;
   register int x;
   char *in;
    w=(list*)malloc(sizeof(list));
	puts("//*********************************");
	 printf("请输入学生序号:");
	 scanf("%ld",&w->num);
     setbuf(stdin,NULL);
	 printf("请输入学生姓名:");
	 in=g_input();
     g_scp(w->name,in);
	 
	 printf("请输入学生性别:");
	 in=g_input();
     g_scp(w->sex,in);

	 printf("请输入学生成绩:\n");
	 for(x=0;x++<MAX_CON;){
       printf(" <%s> : ",*(Grade_students+x-1));
	    scanf("%f",&w->grade[x-1]);
		setbuf(stdin,NULL);
	 }

	 printf("请输入学生的信息内容:");
	 in=g_input();
	 g_scp(w->text,in);

	 printf("请输入学生用户名:");
	 in=g_input();
     g_scp(w->user,in);

	 printf("请输入学生密码:");
	 in=g_input();
     g_scp(w->password,in);

puts("*********************************//");
if(tmp==1){
  w->n=p->n;
  p->n=w;
  printf("Adress -> %x\n",p->n);
  return true;
}  
  w->n=q->n;
  q->n=w;
  printf("Adress -> %x\n",q->n);
	return true;
}


list* relist(hd w,int c){  //返回地址
  list *p=w.n;
   while(--c&&p!=NULL)
	   p=p->n;
   return p;
}
list* relist(hd *w,int c){  //返回地址
  list *p=w->n;
   while(--c&&p!=NULL)
	   p=p->n;
   return p;
}

list* relist(list* w,int c){  //返回地址
  list *p=w->n;
   while(--c&&p!=NULL)
	   p=p->n;
   return p==NULL?NULL:p;
}


list* checklistint(hd p,long e){  //查找
  list *q=p.n;
  while(q!=NULL){
     if(q->num==e)
		 break;
    q=q->n;
  }
  return q;
}

list* checkliststr(hd p,int e,char *s){
  list *q=p.n;
  while(q!=NULL){
	   if(e==0)
      if(g_strbj(s,q->name))
		  break;
		  if(e==1)
		   if(g_strbj(s,q->sex))
			   break;
		if(e==2)
		   if(g_strbj(s,q->user))
			   break;
	  q=q->n;
  }
  return q;
}
// 查找后续

list* checklistint(list *q,long e){  //查找;
  q=q->n;
	while(q!=NULL){
     if(q->num==e)
		 break;
    q=q->n;
  }
  return q;
}

list* checkliststr(list *q,int e,char *s){
	 q=q->n;
  while(q!=NULL){
	   if(e==0)
      if(g_strbj(s,q->name))
		  break;
		  if(e==1)
		   if(g_strbj(s,q->sex))
			   break;
		if(e==2)
		   if(g_strbj(s,q->user))
			   break;
	  q=q->n;
  }
  return q;
}

//


void sort(int *a,int q,int w){  //快速排序
  if(q>=w) return ;
  int i=q,j=w;
  int k=*(a+q);
  while(i<j){
     while(i<j&&k<=*(a+j)) j--;
	 *(a+i)=*(a+j);
	 while(i<j&&k>=*(a+i)) i++;
	 *(a+j)=*(a+i);
  }
  *(a+i)=k;
  sort(a,q,i-1);
  sort(a,i+1,w);
}

bool listxg(list *&p,int e){  //修改
	char msg[][12]={"<序号>","<姓名>","<性别>","<成绩>","<信息>","<用户名>","<密码>"};
	register int x;
	char *in;
	setbuf(stdin,NULL);
	if(e==0){
      printf(" %s [%ld] -> ",msg[e],p->num);
	   scanf("%ld",&p->num);
	   printf(" %s -> [%ld] - 0 error(s), 0 warning(s) \n",msg[e],p->num);
	}else if(e==3){
		for(x=0;x<MAX_CON;x++){
       printf(" %s [%s #%f] -> ",msg[e],Grade_students[x],p->grade[x]);
		 scanf("%f",&p->grade[x]);
		 setbuf(stdin,NULL);
		 printf(" %s -> [%s #%f] - 0 error(s), 0 warning(s) \n",msg[e],Grade_students[x],p->grade[x]);
		}

	}else{
          printf(" %s ",msg[e]);
		  switch(e){
		  case 1:printf("[%s] -> ",p->name);
			 in=g_input();  
			 g_scp(p->name,in);
			 printf(" %s -> [%s] - 0 error(s), 0 warning(s) \n",msg[e],p->name);
			  break;
		  case 2:printf("[%s] -> ",p->sex);
			 in=g_input();
			 g_scp(p->sex,in);
			 printf(" %s -> [%s] - 0 error(s), 0 warning(s) \n",msg[e],p->sex);
			  break;
		  case 4:printf("[%s] -> ",p->text);
			 in=g_input();
			 g_scp(p->text,in);
			 printf(" %s -> [%s] - 0 error(s), 0 warning(s) \n",msg[e],p->text);
			  break;
		  case 5:printf("[%s] -> ",p->user);
			 in=g_input();
			 g_scp(p->user,in);
			 printf(" %s -> [%s] - 0 error(s), 0 warning(s) \n",msg[e],p->user);
			  break;
		  case 6:printf("[%s] -> ",p->password);
			 in=g_input();
			 g_scp(p->password,in);
			 printf(" %s -> [%s] - 0 error(s), 0 warning(s) \n",msg[e],p->password);
			  break;
		  }
	}
	return true;
     
}

/*bool sort(hd &r, int e){ //排序
   list *q,*w,*t;
    hd *p=&r,*h;
    float sum[2];
	bool pd;
   register int x;
    if(p->n==NULL||p->n->n==NULL)
		return true;
	q=p->n->n;
	p->n->n=NULL;
	printf("e  =  %d\n",e);
	while(q!=NULL){
        t=q->n;
		w=p->n;
		 h=p;
		 pd=false;
		if(e==0)
			while(w->n!=NULL||(h->n!=NULL&&!pd)&&w->num<=q->num){
				if(!pd){
                   pd=true;
				    w=h->n;
				}else
				w=w->n;
			}
			 if(e==1)
			 while(w->n!=NULL||(h->n!=NULL&&!pd)&&w->num>=q->num){
				if(!pd){
                   pd=true;
				    w=h->n;
				}else
				w=w->n;
			}

		 if(e==2)
		  while(w->n!=NULL&&strcmp(w->name,q->name)<=0)
			  w=w->n;
		   if(e==3)
		  while(w->n!=NULL&&strcmp(w->name,q->name)>=0)
			  w=w->n;

		   if(e==4)
			    while(w->n!=NULL&&strcmp(w->sex,q->sex)<=0)
			  w=w->n;
				if(e==5)
			    while(w->n!=NULL&&strcmp(w->sex,q->sex)>=0)
			  w=w->n;

				if(e==6){
                   for(x=0,*sum=0,*(sum+1)=0;x<MAX_CON;x++)
				   {*sum+=w->grade[x];
				   *(sum+1)=w->grade[x];}
				     while(w->n!=NULL&&*sum<=*(sum+1))
			          w=w->n;
			   }
				if(e==7){
                   for(x=0,*sum=0,*(sum+1)=0;x<MAX_CON;x++)
				   {*sum+=w->grade[x];
				   *(sum+1)=w->grade[x];}
				     while(w->n!=NULL&&*sum>=*(sum+1))
			          w=w->n;
			   }

             if(e==8)
				  while(w->n!=NULL&&strcmp(w->text,q->text)<=0)
			  w=w->n;
				  if(e==9)
				  while(w->n!=NULL&&strcmp(w->text,q->text)>=0)
			  w=w->n;

				  if(e==10)
                while(w->n!=NULL&&strcmp(w->user,q->user)<=0)
			  w=w->n;
				if(e==11)
                while(w->n!=NULL&&strcmp(w->user,q->user)>=0)
			  w=w->n;
				
				
				if()
        q->n=w->n;
		w->n=q;
		q=t;
}
	return true;
}*/

bool listoutput(hd pt,char *in,int e){
   FILE *f[2];
	char *path[2];
    int b=0;
	register int i;
	hd *p=&pt;
	*path=(char*)malloc(g_len(in)+5);
    *(path+1)=(char*)malloc(g_len(in)+5);
	g_scp(*path,in);
	g_scp(*(path+1),in);
	*path=g_scat(*path,".txt");
	*(path+1)=g_scat(*(path+1),".dat");
	if(((*f=fopen(*path,"r"))==NULL)&&((*(f+1)=fopen(*(path+1),"rb"))==NULL));
	else{
		if(e==1) {puts("绝对路径存在同名文件,终止输出!");
		return false;}}
	if((*f=fopen(*path,"w"))==NULL) {printf("导出数据表 <%s> 失败!\n",p->name); return false;}
	if((*(f+1)=fopen(*(path+1),"wb"))==NULL) {printf("导出数据表 <%s> 失败!\n",p->name); return false;}
	 if(p->n==NULL)
		fprintf(*f,"[<-------------------------------->]\n");
	 else{

      time_t ts;//将ts声明为时间变量
    struct tm *pf;//struct tm是一个结构体，声明一个结构体指针
    time(&ts);
    pf=localtime(&ts);//获得当地的时间
/*--------------------- 
作者：Baozk-路人甲 
来源：CSDN 
原文：https://blog.csdn.net/qq_37861955/article/details/78070293 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
          fprintf(*f,"<<!------ 数据表 <%s> ------!>>\n",p->name);
		  fprintf(*f,"|  ------ 总长度 <%d> ------\n",lenlist(p));
		  fprintf(*f,"|  ------ 占用总字节 <%d> ------\n",sizeof(hd)+lenlist(p)*sizeof(list));
		  fprintf(*f,"|  ------ 最后修改时间: <%d-%d-%d %d:%d:%d> ------\n",1900+pf->tm_year,1+pf->tm_mon,pf->tm_mday,pf->tm_hour,pf->tm_min,pf->tm_sec);
          fprintf(*f,"<<!------    E N D    ------!>>\n",p->name);
		  fwrite(p,sizeof(hd),1,*(f+1));
	 }
	 fputs("\n\n",*f);
	 list *w=p->n;
		 while(w!=NULL){
			 b++;
                     fprintf(*f,"[<-------------------------------->]\n");
					 fprintf(*f," <索引号> : %d\n",b);
					 fprintf(*f," <序号> : %ld\n",w->num);
					 fprintf(*f," <姓名> : %s\n",w->name);
					 fprintf(*f," <性别> : %s\n",w->sex);
					 fprintf(*f," <信息> : %s\n",w->text);
					 fprintf(*f," <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 fprintf(*f," [%s] : %f\n",Grade_students[i],w->grade[i]);
                     fprintf(*f," [%s] : %f}\n",Grade_students[i],w->grade[i]);
					 fprintf(*f," <用户名> : %s\n",w->user);
					 fprintf(*f," <密码> : %s\n",w->password);
					 fwrite(w,sizeof(list),1,*(f+1));
					 w=w->n;
				 }
		 fprintf(*f,"[<--------------END--------------->]\n");
	fclose(*f);
	fclose(*(f+1));
	return true;
}

char* listinput(char* in,int key,hd *&t,int &con){
	FILE *f;
	char *path;
	register int i;
     hd *tmp=(hd*)malloc(sizeof(hd)*con);
	 hd *bj=(hd*)malloc(sizeof(hd));
	 hd del;
	 list *data,*tp;
	path=(char*)malloc(strlen(in)+5);
	g_scp(path,in);
	path=g_scat(path,".dat");
	if((f=fopen(path,"rb"))==NULL) {printf("导入数据表失败!\n"); return NULL;}
	fread(bj,sizeof(hd),1,f);
	for(i=0;i<con;i++){
		 *(tmp+i)=*(t+i);
		 if(g_strbj((*(tmp+i)).name,bj->name))
			 if(key==0){
				 del=*(tmp+i);
				  *(tmp+i)=*bj;
				   free(&del);
			 }else{
                 printf("出现同名的数据表 <[Count %d]:%s -> {Length %d}> ,错误!",i+1,*(tmp+i)->name,lenlist(&*(tmp+i)));
				 return NULL;
			 }
	}
	 t=(hd*)malloc(sizeof(hd)*++con);
	 for(i=0;i<con-1;i++){
       *(t+i)=*(tmp+i);
	 }
	 *(t+i)=*bj;
	 if(fread(data=(list*)malloc(sizeof(list)),sizeof(list),1,f)!=NULL){
       tp=((*(t+i)).n)=data;
	 }else
		  return NULL;
	while(fread(data=(list*)malloc(sizeof(list)),sizeof(list),1,f)&&data!=NULL){
		  tp->n=data;
		  tp=data;
		}
	tp->n=NULL;
	return bj->name;
}



bool sort(hd &t,int e){  //排序
  hd *p=&t;
  list *q,*w,*r;
  float sum[2];
  bool pd=false;
  register int i=0,x=lenlist(t),j;
   if(x<=1) return true;
   while(i++<x-1){
	   r=w=relist(p,i);
	   for(j=0,*sum=0;j<MAX_CON;*sum+=w->grade[j],j++);
		   while(r->n!=NULL){
			   {if(e==0)
				   w=(r->n->num>w->num)?r:w;
                  if(e==1)
					  w=(r->n->num<w->num)?r:w;}

			   {if(e==2)
				   w=(strcmp(r->n->name,w->name)>0)?r:w;
                  if(e==3)
				   w=(strcmp(r->n->name,w->name)<0)?r:w;}

			   {if(e==4)
				   w=(strcmp(r->n->sex,w->sex)>0)?r:w;
                  if(e==5)
				   w=(strcmp(r->n->sex,w->sex)<0)?r:w;}

			   {if(e==6){
				   for(j=0,*(sum+1)=0;j<MAX_CON;*(sum+1)+=r->n->grade[j],j++);
				     w=(*(sum+1)>*sum)?r:w;}    
			   if(e==7){
				   for(j=0,*(sum+1)=0;j<MAX_CON;*(sum+1)+=r->n->grade[j],j++);
				     w=(*(sum+1)<*sum)?r:w;}}

			   {if(e==8)
				   w=(strcmp(r->n->text,w->text)>0)?r:w;
                  if(e==9)
				   w=(strcmp(r->n->text,w->text)<0)?r:w;}

			   {if(e==10)
				   w=(strcmp(r->n->user,w->sex)>0)?r:w;
                  if(e==11)
				   w=(strcmp(r->n->user,w->sex)<0)?r:w;}
	
              r=r->n; 
   }
		   q=w->n;
		   w->n=q->n;
		   q->n=p->n;
		   p->n=q;
   }
   return true;
}

int relistc(list *p,hd t){
   list *w=t.n;
   for(register int x=1;w!=p&&w!=NULL;x++,w=w->n);
   return w!=NULL?x:0;
}

bool delelist(hd &t,int i){  //删除第i个表
	if(i<=0 || i>lenlist(t)) return false;
    list *tmp,*p=relist(t,i-1);
	if(i==1) {tmp=t.n;
      t.n=NULL;
	free(tmp);
	return true;
	}
	if(p!=NULL&&p->n!=NULL){
		 tmp=p->n;
        p->n=tmp->n;
		free(tmp);
	}else
		 return false;
	return true;
} 

list* pdlogin(long num,char *user,char *pwd,hd *t,int c){
	hd *p;
	list *w;
	char k;
	for(register int x=0;x<c;x++){
         w=(p=&*(t+x))->n;
		 while(w!=NULL){
			 if(g_strbj(user,w->user)&&(g_strbj(pwd,w->password))&&num==w->num){
				 printf("[<-------------------------------->]\n");
				 printf(" <数据表> : %s\n",(*(t+x)).name);
				 printf(" <索引号> : %d\n",relistc(w,*(t+x)));
                   printf(" <序号> : %ld\n",w->num);
				   printf(" <姓名> : %s\n",w->name);
				   printf(" <性别> : %s\n",w->sex);
				   puts("您是否为这个学生? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
			 }
          w=w->n;
		 }
		printf("[<--------------END--------------->]\n");
		 if(k=='Y')
			 return w;
	}
	return NULL;
}

bool listoutputu(list *p,char *in,int e){
  FILE *f;
	char *path;
	register int i;
	path=(char*)malloc(g_len(in)+5);
	g_scp(path,in);
	path=g_scat(path,".txt");
	if(((f=fopen(path,"r"))==NULL));
	else{
		if(e==1) {puts("绝对路径存在同名文件,终止输出!");
		return false;}}
	if((f=fopen(path,"w"))==NULL) {printf("导出数据 [%s] 失败!\n",p->name); return false;}
	  fprintf(f,"[<-------------------------------->]\n");
					 fprintf(f," <序号> : %ld\n",p->num);
					 fprintf(f," <姓名> : %s\n",p->name);
					 fprintf(f," <性别> : %s\n",p->sex);
					 fprintf(f," <信息> : %s\n",p->text);
					 fprintf(f," <成绩> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 fprintf(f," [%s] : %f\n",Grade_students[i],p->grade[i]);
                     fprintf(f," [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 fprintf(f," <用户名> : %s\n",p->user);
					 fprintf(f," <密码> : %s\n",p->password);
		fprintf(f,"[<--------------END--------------->]\n");
		fprintf(f,"\n\n[<-------------------------------->]\n");

      time_t ts;//将ts声明为时间变量
    struct tm *pf;//struct tm是一个结构体，声明一个结构体指针
    time(&ts);
    pf=localtime(&ts);//获得当地的时间
/*--------------------- 
作者：Baozk-路人甲 
来源：CSDN 
原文：https://blog.csdn.net/qq_37861955/article/details/78070293 
版权声明：本文为博主原创文章，转载请附上博文链接！
*/
		  fprintf(f,"|  ------ 最后修改时间: <%d-%d-%d %d:%d:%d> ------\n",1900+pf->tm_year,1+pf->tm_mon,pf->tm_mday,pf->tm_hour,pf->tm_min,pf->tm_sec);
          fprintf(f,"<<!------    E N D    ------!>>\n",p->name);
	fclose(f);
	return true;	
}

 #endif
