
/*******************

 ��лDM_LongLone��CMDER����
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
	printf("<!--        ����Ա <%s> ��ӭ��!          --!>\n",adminuser);
	 puts("--------------------------------------------");
	 puts("| ( A )  <����> ѧ�����ݱ�; ");
     puts("| ( B ) �� <ĳ��λ�ò���> ѧ������; ");
	 puts("| ( C )  <ɾ��> ĳ��ѧ������;");
	 puts("| ( D )  <��ѯ> ĳ��ѧ������;");
	 puts("| ( E )  <�޸�> ĳ��ѧ������;");
	 puts("| ( F ) ���������ݽ��� <����> ;");
	 puts("| ( G ) һ���� <����> ����ѧ������; ");
	 puts("| ( H )  <����> ѧ������;");
	 puts("| ( I )  <����> ѧ������;");
	 puts("| ( J ) !-- <�޸�> ����Ա�û���;");
     puts("| ( K ) !-- <�޸�> ����Ա����;"); 
	 puts("| ( L ) �˳���½;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
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
    printf("<!--   <����> ѧ�����ݱ�[���б���:%d]    --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ��ʼ�������ݱ�; ");
	 puts("| ( B ) ��ʾ��ǰ���б�; ");
	 puts("| ( C ) ɾ�����ݱ�; ");
	 puts("| ( D ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 char *name;
			 printf("�������½��ĵ�[%d]��������:",table_cont+1);
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
		   printf("�½��� <%s> ���[���б���%d]\n",name,++table_cont);
		 }
		 if(c=='B'){
			 printf("��ʾ��ǰ���б�[���б���%d]\n",table_cont);
			  for(i=0;i<table_cont;i++)
				  printf("[Count %d]: <%s> -> {Length %d}\n",i+1,(*(table+i)).name,lenlist(*(table+i)));
		 }
		 if(c=='C'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
			 printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫɾ�����ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
	
             printf("�Ƿ�ʼ�� <[Count %d]:%s -> {Length %d}> ����ɾ������:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			  printf("������ (Y/N) ");
			  setbuf(stdin,NULL);
			  if((k=getchar())!='Y')
				  break;
			  if(table_cont-1==0){
				  tp=&*table;
			  printf("ɾ�� <%s> ���!\n",(*tp).name);
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
					  printf("ɾ�� <%s> ���!\n",(*(tp+index-1)).name);
					  table_cont--;
		   }else
			    printf("�������������!\n");
		 }
		 if(c=='D'){
           loop=0;
		   puts("����!");
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
    printf("<!--�� <ĳ��λ�ò���> ѧ������[���б���:%d]--!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ��������; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ�������ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			   while(1){
             printf("��ʼ�� <[Count %d]:%s -> {Length %d}> ���в������:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("��������Ҫ�����[λ��]:");
              if(!scanf("%d",&location)) continue;
			 if(insertlist(*(table+index-1),location))
				 printf("�ɹ��������� -> [Location %d] 0 error(s), 0 warning(s)\n",location);
				 
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������������;");
	           puts("| ( B ) ֹͣ��������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					break;
			 }

		   }else
			   printf("�������������!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
    printf("<!--  <ɾ��> ĳ��ѧ������[���б���:%d]  --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ɾ������; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫɾ�����ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			   while(true){
             printf("��ʼ�� <[Count %d]:%s -> {Length %d}> ����ɾ������:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("��������Ҫɾ����[λ��]:");
              if(!scanf("%d",&location)) continue;
				  if(delelist(*(table+index-1),location))
					  printf("ɾ�� <%d> λ�����ݳɹ�!\n",location);
				  else
					printf("�����λ�ò���ȷ![1 -> %d]\n",lenlist(*(table+index-1)));
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ����ɾ������;");
	           puts("| ( B ) ֹͣɾ������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				 if(c!='A')
				break;
			 }

		   }else
			   printf("�������������!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("����!");
		 }
		 }
   return true;}
   //D{
bool checka(){
	setbuf(stdin,NULL);
	system("cls");
	char c,msg[][12]={"<���>","<����>","<�Ա�>","<�û���>","<����>"},*in;
   register int i;
   int index;
   long f;
   bool loop=1,np=1;
    list *p;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!--  <��ѯ> ĳ��ѧ������[���б���:%d]  --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ��ѯ����; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ��ѯ���ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			 while(np){
		     printf("��ʼ�� <[Count %d]:%s -> {Length %d}> ���в�ѯ����:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("��ѡ����Ҫ��ѯ������[����]:\n");
			 for(i=0;i<5;i++)
				 printf("| ( %c ) ���� %s ; \n",65+i,msg[i]);
			 printf("���ѡ��:");
			 printf("%c\n",c=getch());
			 if(c=='A'){
				 printf("������ %s :",msg[0]);
				 scanf("%ld",&f);
				 p=checklistint(*(table+index-1),f);
				  if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
					 p=checklistint(p,f);
				 }
				 printf("[<--------------END--------------->]\n");
			 }else if(c!='E'){
				 printf("������ %s :",msg[c-'A']);
				 setbuf(stdin,NULL);
                in=g_input();
				p=checkliststr(*(table+index-1),c-'B',in);
				if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
					 p=checkliststr(p,c-'B',in);
				 }
				 printf("[<--------------END--------------->]\n");
			 }
			 else{
				 printf("������ %s :",msg[4]);
				 scanf("%ld",&f);
                  p=relist(*(table+index-1),f);
				   if(p==NULL) printf("[<-------------------------------->]\n");
				  if(p!=NULL){
                    printf("[<-------------------------------->]\n");
					printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
				  }
				  printf("[<--------------END--------------->]\n");
			 }
			 
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������ѯ����;");
	           puts("| ( B ) ֹͣ��ѯ����;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
				break;
			 }
		   }else
			   printf("�������������!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("����!");
		 }
		 }
	return true;
}


   //E{

   bool xga(){
	   setbuf(stdin,NULL);
	   system("cls");
	char c,k,msg[][12]={"<���>","<����>","<�Ա�>","<�û���>","<����>"},*in;
	char msg1[][12]={"<���>","<����>","<�Ա�>","<�ɼ�>","<��Ϣ>","<�û���>","<����>"};
   register int i;
   int index;
   long f;
   bool loop=1,np=1;
    list *p;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!--  <�޸�> ĳ��ѧ������[���б���:%d]  --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) �޸�����; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ�޸����ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			 while(np){
				 k='N';
		     printf("��ʼ�� <[Count %d]:%s -> {Length %d}> �����޸Ĳ���:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("��ѡ�����޸ĵı��λ��[����]:\n");
			 for(i=0;i<5;i++)
				 printf("| ( %c ) ���� %s ����; \n",65+i,msg[i]);
			 printf("���ѡ��:");
			 printf("%c\n",c=getch());
			 if(c=='A'){
				 printf("������ %s :",msg[0]);
				 scanf("%ld",&f);
				 p=checklistint(*(table+index-1),f);
				  if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
					 puts("�Ƿ�ѡ���޸����������? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
					p=checklistint(p,f);
				 }
				 printf("[<--------------END--------------->]\n");
				 if(k=='Y'){
					 while(1){
                    printf("��ѡ����Ҫ�޸ĵ�����[����]:\n");
						for(i=0;i<7;i++)
							printf("| ( %c ) �޸� %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) ����; \n",65+i);
						printf("���ѡ��:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("�޸� %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
				 }
			 }else if(c!='E'){
				 printf("������ %s :",msg[c-'A']);
				 setbuf(stdin,NULL);
                in=g_input();
				p=checkliststr(*(table+index-1),c-'B',in);
				if(p==NULL)
				 printf("[<-------------------------------->]\n");
				 while(p!=NULL){
                     printf("[<-------------------------------->]\n");
					 printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
					 puts("�Ƿ�ѡ���޸����������? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
				     p=checkliststr(p,c-'B',in);
				 }
				 printf("[<--------------END--------------->]\n");
				  if(k=='Y'){
					 while(1){
                    printf("��ѡ����Ҫ�޸ĵ�����[����]:\n");
						for(i=0;i<7;i++)
							printf("| ( %c ) �޸� %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) ����; \n",65+i);
						printf("���ѡ��:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("�޸� %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
				 }
			 }
			 else{
				 printf("������ %s :",msg[4]);
				 scanf("%ld",&f);
                  p=relist(*(table+index-1),f);
				   if(p==NULL) printf("[<-------------------------------->]\n");
				  if(p!=NULL){
                    printf("[<-------------------------------->]\n");
					printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
					 puts("�Ƿ�ѡ���޸����������? [Y/N]");
					 k=getch();
						  if(k=='Y')
							  break;
				  }
				  printf("[<--------------END--------------->]\n");
				   if(k=='Y'){
					 while(1){
                    printf("��ѡ����Ҫ�޸ĵ�����[����]:\n");
						for(i=0;i<7;i++)
							printf("| ( %c ) �޸� %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) ����; \n",65+i);
						printf("���ѡ��:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("�޸� %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
				 }
			 }
			 
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������ѯ���޸�����;");
	           puts("| ( B ) ֹͣ��ѯ���޸�����;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
				break;
			 }
		   }else
			   printf("�������������!\n");
		   }
		 if(c=='B'){
			 loop=0;
                puts("����!");
		 }
		 }
	return true;
}
   //F{

  bool sorta(){
	  setbuf(stdin,NULL);
	  system("cls");
	char c,msg[][12]={"<���>","<����>","<�Ա�>","<�ɼ�>","<��Ϣ>","<�û���>"};
   register int i;
   int index;
   bool loop=1,np=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!-- ���������ݽ��� <����> [���б���:%d] --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ��������; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ��ѯ���ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
			 while(np){
		     printf("��ʼ�� <[Count %d]:%s -> {Length %d}> �����������:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("��ѡ����Ҫ�������������[����]:\n");
			 for(i=0;i<12;i+=2){
				 printf("| ( %c ) ���� %s [���� -> ��С����]; \n",65+i,msg[i/2]);
				 printf("| ( %c ) ���� %s [���� -> �Ӵ�С]; \n",65+i+1,msg[i/2]);
			 }
			 printf("���ѡ��:");
			 printf("%c\n",c=getch());
			  if(sort(*(table+index-1),c-'A'))
			     printf("�������!\n");
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ����������������;");
	           puts("| ( B ) ֹͣ������������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				 if(c!='A')
					 break;
			 }
		   }else
			   printf("�������������!\n");
		 }
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
    printf("<!--һ���� <����> ����ѧ������[���б���:%d]--!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ��������; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ�������ݵı�[����]:");
		   scanf("%d",&index);
		   if(index<=table_cont&&index>0){
             printf("��ʼ�� <[Count %d]:%s -> {Length %d}> ������������:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 j=1;
			 p=relist(*(table+index-1),j);
             if(p==NULL)
				 printf("[<-------------------------------->]\n");
			 while(p!=NULL){
				 printf("[<-------------------------------->]\n");
				 printf(" <������> : %d\n",relistc(p,*(table+index-1)));
					 printf(" <���> : %ld\n",p->num);
					 printf(" <����> : %s\n",p->name);
					 printf(" <�Ա�> : %s\n",p->sex);
					 printf(" <��Ϣ> : %s\n",p->text);
					 printf(" <�ɼ�> : {\n");
					 for(i=0;i<MAX_CON-1;i++)
						 printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
                     printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
					 printf(" <�û���> : %s\n",p->user);
					 printf(" <����> : %s\n",p->password);
					 p=relist(*(table+index-1),++j);}
				  
				 printf("[<--------------END--------------->]\n");
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������������;");
	           puts("| ( B ) ֹͣ��������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		   }else
			   printf("�������������!\n");
		 }	 
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
    printf("<!--    <����> ѧ������[���б���:%d]    --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ���ǵ�������; ");
	 puts("| ( B ) Ĭ�ϵ�������;");
	 puts("| ( C ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'||c=='B'){
			 table_cont>0?printf("��ǰ���б�:\n"):printf("��ǰû�б�!\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ�������ݵı��λ��[����·��]:");
		    in=g_input();
             printf("��ʼ�� <%s.dat> ���е������:\n",in);
			   if((out=listinput(in,c-'A',table,table_cont))!=NULL)
				   printf("�ѳɹ������ <%s> \n",out);
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������������;");
	           puts("| ( B ) ֹͣ��������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }	 
		 if(c=='C'){
			 loop=0;
                puts("����!");
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
    printf("<!--    <����> ѧ������[���б���:%d]    --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) ���ǵ�������; ");
	 puts("| ( B ) Ĭ�ϵ�������;");
	 puts("| ( C ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'||c=='B'){
			 if(!table_cont) {printf("Ŀǰ����Ϊ0,�޷����в���!\n");
			 continue;}
		   printf("��ǰ���б�:\n");
		   for(i=0;i<table_cont;i++)
             printf("[Count %d]:%s\n",i+1,(*(table+i)).name);
		   printf("��ѡ��Ҫ�������ݵı�[����]:");
		   scanf("%d",&index);
		   setbuf(stdin,NULL);
		   if(index<=table_cont&&index>0){
             printf("��ʼ�� <[Count %d]:%s -> {Length %d}> ���е�������:\n",index,(*(table+index-1)).name,lenlist(*(table+index-1)));
			 printf("��������Ҫ������λ��[����·��]:");
              in=g_input();
			   if(listoutput(*(table+index-1),in,c-'A'))
				   printf("�ѳɹ������ <%s.txt> | <%s.dat> \n",in,in);
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������������;");
	           puts("| ( B ) ֹͣ��������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		   }else
			   printf("�������������!\n");
		 }	 
		 if(c=='C'){
			 loop=0;
                puts("����!");
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
    printf("<!--         <�޸�> ����Ա�û���        --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) �޸��û���; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("������ <�ɵ��û���> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,adminuser))
              { puts("�û�������ȷ!��ֹ!");
                    continue;
			  }
			  printf("������ <�µ��û���> -> ");
			  in=g_input();
			   g_scp(adminuser,in);
			   printf("<Username> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,adminuser);
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) �����޸��û���;");
	           puts("| ( B ) ֹͣ�޸��û���;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
    printf("<!--          <�޸�> ����Ա����         --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) �޸�����; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("������ <�ɵ�����> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,adminpwd))
              { puts("���벻��ȷ!��ֹ!");
                    continue;
			  }
			  while(bt){
			  printf("������ <�µ�����> -> ");
			  *in=g_input();
			  printf("���ٴ����� <�µ�����> -> ");
			  *(in+1)=g_input();
			   if(!g_strbj(*in,*(in+1)))
                  { puts("�������벻��ͬ!����������!");
                    continue;
			  }
			   g_scp(adminpwd,*in);
			   printf("<Password> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,adminpwd);
			  bt=0;
			  }puts("��ѡ��ǰ����:");
			   puts("| ( A ) �����޸�����;");
	           puts("| ( B ) ֹͣ�޸�����;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
			 }
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
	printf("<!--        ѧ�� <%s> ��ӭ��!          --!>\n",p->name);
	 puts("--------------------------------------------");
	printf(" <���> : %ld\n",p->num);
	printf(" <����> : %s\n",p->name);
	printf(" <�Ա�> : %s\n",p->sex);
    printf(" <��Ϣ> : %s\n",p->text);
	printf(" <�ɼ�> : {\n");
	for(i=0;i<MAX_CON-1;i++)
	printf(" [%s] : %f\n",Grade_students[i],p->grade[i]);
       printf(" [%s] : %f}\n",Grade_students[i],p->grade[i]);
		printf(" <�û���> : %s\n",p->user);
	printf(" <����> : %s\n",p->password);
	puts("--------------------------------------------");
	 puts("| ( A )  <�޸�> ĳ������;");
	 puts("| ( B )  <����> ѧ������;");
	 puts("| ( C ) !-- <�޸�> �û���;");
     puts("| ( D ) !-- <�޸�> ����;"); 
	 puts("| ( E ) �˳���½;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
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
	char msg1[][12]={"<���>","<����>","<�Ա�>","<�ɼ�>","<��Ϣ>"};
   register int i;
   bool loop=1,np=1;
   while(loop){
	   system("cls");
		setbuf(stdin,NULL);
	   np=1;
    printf("<!--          <�޸�> ĳ������           --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) �޸�����; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
					 while(np){
                    printf("��ѡ����Ҫ�޸ĵ�����[����]:\n");
						for(i=0;i<5;i++)
							printf("| ( %c ) �޸� %s ; \n",65+i,msg1[i]);
						printf("| ( %c ) ����; \n",65+i);
						printf("���ѡ��:");
						printf("%c\n",c=getch());
						if(c==65+i)
							break;
						else{
							printf("�޸� %s {\n",msg1[c-'A']);
							if(listxg(p,c-'A'))
								puts("}");
						}
					 }
			 }
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
    printf("<!--          <����> ����[%s]          --!>\n",p->name);
	 puts("--------------------------------------------");
	 puts("| ( A ) ���ǵ�������; ");
	 puts("| ( B ) Ĭ�ϵ�������;");
	 puts("| ( C ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'||c=='B'){
			 printf("��������Ҫ������λ��[����·��]:");
              in=g_input();
			   if(listoutputu(p,in,c-'A'))
				   printf("�ѳɹ������ <%s.txt> \n",in);
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) ������������;");
	           puts("| ( B ) ֹͣ��������;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }
		 if(c=='C'){
			 loop=0;
                puts("����!");
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
    printf("<!--           <�޸�> �û���          --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) �޸��û���; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("������ <�ɵ��û���> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,p->user))
              { puts("�û�������ȷ!��ֹ!");
                    continue;
			  }
			  printf("������ <�µ��û���> -> ");
			  in=g_input();
			   g_scp(p->user,in);
			   printf("<Username> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,p->user);
               puts("��ѡ��ǰ����:");
			   puts("| ( A ) �����޸��û���;");
	           puts("| ( B ) ֹͣ�޸��û���;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
		 }
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
    printf("<!--            <�޸�> ����           --!>\n",table_cont);
	 puts("--------------------------------------------");
	 puts("| ( A ) �޸�����; ");
	 puts("| ( B ) ����");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
         printf("%c\n",c=getch());
		 if(c=='A'){
			 printf("������ <�ɵ�����> -> ");
			 inf=g_input();
			  if(!g_strbj(inf,p->password))
              { puts("���벻��ȷ!��ֹ!");
                    continue;
			  }
			  while(bt){
			  printf("������ <�µ�����> -> ");
			  *in=g_input();
			  printf("���ٴ����� <�µ�����> -> ");
			  *(in+1)=g_input();
			   if(!g_strbj(*in,*(in+1)))
                  { puts("�������벻��ͬ!����������!");
                    continue;
			  }
			   g_scp(p->password,*in);
			   printf("<Password> [%s] -> [%s] - 0 error(s), 0 warning(s) \n",inf,p->password);
			  bt=0;
			  }puts("��ѡ��ǰ����:");
			   puts("| ( A ) �����޸�����;");
	           puts("| ( B ) ֹͣ�޸�����;");
			   printf("���ѡ��:");
                printf("%c\n",c=getch());
				if(c!='A')
					 break;
			 }
		 if(c=='B'){
			 loop=0;
                puts("����!");
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
     puts("<!--            ����Ա��½              --!>");
	 puts("--------------------------------------------");
	 printf("| ( 1 ) �������û���: ");
	 *in=g_input();
	 printf("| ( 2 ) ����������: ");
	 *(in+1)=g_input();
	 printf("| ( press any key ) ��½ϵͳ\n");
	 getch();
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	if(g_strbj(*in,adminuser)&&g_strbj(*(in+1),adminpwd))
		return aset();
	else {printf("�û������������!!!\n{ �Ƿ����µ�½? }\n| ( A ) ���µ�½;\n| ( B ) �˳���½\n");
	   printf("���ѡ��:");
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
        printf("( press any key ) Ŀǰû���κ����ݱ����ο�!�޷����е�½����!\n");
		getch();
		return false;
	 }
	while(loop){
		system("cls");
		setbuf(stdin,NULL);
     puts("<!--             ѧ����½              --!>");
	 puts("--------------------------------------------");
	 printf("| ( 1 ) ���������: ");
	 scanf("%ld",&num);
	 setbuf(stdin,NULL);
	 printf("| ( 2 ) �������û���: ");
	 *in=g_input();
	 printf("| ( 3 ) ����������: ");
	 *(in+1)=g_input();
	 printf("| ( press any key ) ��½ϵͳ\n");
	 getch();
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 
	if((p=pdlogin(num,*in,*(in+1),table,table_cont))!=NULL)
		return uset(p);
	else {printf("��½����!!!\n{ �Ƿ����µ�½? }\n| ( A ) ���µ�½;\n| ( B ) �˳���½\n");
	   printf("���ѡ��:");
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
     puts("<!--             ��Ϸģʽ              --!>");
	 puts("--------------------------------------------");
	 puts("| ( A ) ̰�Գ��; ");
	 puts("| ( B ) �Թ�����; ");
	 puts("| ( C ) �˳���Ϸģʽ;");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
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
	  puts("�����������ʼ��ʼ����Ϸ!~~");
	  getch();
  CreateMap();
  Sleep(500);
     puts("��ͼ��ʼ�����!~~");
	 Sleep(500);
	  if(C_S.LONG!=1)
	  CreateS(C_W/2,C_H/2,C_S.LONG,4);
	  else
       CreateS(C_W/2,C_H/2,C_LENGTH,4);
	  puts("����������!~~");
	  Sleep(500);
	  Create0();
	  C_C=1;
	  puts("�����������!~~");
	  Sleep(500);
       RefreshS();
	   puts("��ͼ�������!~~");
	  Sleep(1500);
	  puts("�����������ʼ!~~");
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
  puts("�����ˣ��Ƿ�ѡ�����¼���������Ϸ��\n| ( 1 ) ����\n| ( 2 ) �˳�");
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
		puts("���ڴ����Թ���ͼ~~~");
		createmap();
		Sleep(300);
		puts("���ڳ�ʼ���Թ�~~~");
		setmap();
		Sleep(500);
		puts("���ڳ�ʼ�����Ӻͳ���~~~");
		createflags(M_flags=M_gk+rand()%M_gk+1);
		puts("�����Թ����~~~");
		Sleep(500);
		showmap();
		puts("���������ʼ��Ϸ!~~~");
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
		puts("�ɹ�������һ��~~~");
		puts("�밴���������~~~");
		system("pause");
	}
	system("cls");
	return true;
}

//--- end ---

//selection function Admin_setting

/*

   puts("--------------------------------------------");
	 puts("| ( A )  <��ʼ��> ѧ�����ݱ�; ");
     puts("| ( B ) �� <ĳ��λ�ò���> ѧ������; ");
	 puts("| ( C )  <ɾ��> ĳ��ѧ������;");
	 puts("| ( D )  <��ѯ> ĳ��ѧ������;");
	 puts("| ( E )  <�޸�> ĳ��ѧ������;");
	 puts("| ( F ) ���������ݽ��� <����> ;");
	 puts("| ( G ) һ���� <����> ����ѧ������; ");
	 puts("| ( H )  <����> ѧ������;");
	 puts("| ( I )  <����> ѧ������;");
	 puts("| ( J ) !-- <�޸�> ����Ա�û���;");
     puts("| ( K ) !-- <�޸�> ����Ա����;"); 
	 puts("| ( L ) �˳���½;");
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
	 puts("| ( A )  <�޸�> ĳ������;");
	 puts("| ( B )  <����> ѧ������;");
	 puts("| ( C ) !-- <�޸�> �û���;");
     puts("| ( D ) !-- <�޸�> ����;"); 
	 puts("| ( E ) �˳���½;");
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
     puts("<!--        ѧ����Ϣ������ϵͳ        --!>");
	 puts("--------------------------------------------");
	 puts("| ( A ) ѧ����½; ");
	 puts("| ( B ) ����Ա��½; ");
	 puts("| ( C ) С��Ϸ");
     puts("| ( D ) �˳�ϵͳ");
	 puts("--------------------------------------------");
	 puts("<!--                END                 --!>");
	 printf("���ѡ��:");
	 
		 printf("%c\n",c=getch());
          if( !selectf(c) )
	        continue;
	}

	return 0;
}