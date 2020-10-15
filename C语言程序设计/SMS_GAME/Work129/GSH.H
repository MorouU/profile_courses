/*********

  超级头文件
 
*********/
#ifndef _GSH_H
#define _GSH_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//**************无限制输入 (\n结束)
char* g_input(){
	char *st[2];
	char c;
	register long r=0;
	register long i=1;
	register long x;
	*st=(char*)malloc(i+1);
	while((c=getchar())!='\n'){
		if(r==i){
			*(st+1)=(char*)malloc(++i+1);
			for(x=0;x<i;x++)
				*((*(st+1))+x)=*((*st)+x);
			free(*st);
			*st=*(st+1);
		}
		*((*st)+r++)=c;
		*((*st)+r)='\0';
	}
	return *st;
}
//**************
//**************无限制输入 (ctrl+d结束)
char* g_inputz(){
	char *st[2];
	char c;
	register long r=0;
	register long i=1;
	register long x;
	*st=(char*)malloc(i+1);
	while((c=getchar())!=EOF){
		if(r==i){
			*(st+1)=(char*)malloc(++i+1);
			for(x=0;x<i;x++)
				*((*(st+1))+x)=*((*st)+x);
			free(*st);
			*st=*(st+1);
		}
		*((*st)+r++)=c;
		*((*st)+r)='\0';
	}
	return *st;
}
//**************
//**************精准实数返回整数
long g_r2i(double x){
   register long y=0;
	   while(x-y++>=1);
	   return y-1;
}
//**************
//**************返回整数第w位的值
int g_riw(long x,long w){
    return x/(long)pow(10,w-1)%10;
}
//**************
//**************返回数的位数
int g_raw(double x){
	register int y=0;
  while((long)x/(long)pow(10,y++)!=0);
  return y-1;
}
//***************
//**************返回字符串的长度
long g_len(const char*str){
  register long r=0;
  while(*(str+r++)!='\0');
  return r-1;
}
//**************
//**************返回十六进制字符
char g_hex(long x){
	if(x>=0&&x<10) return x+48;
	if(x>=10&&x<16) return x+87;
	return 32;
}
//**************
//**************返回一到三十六进制字符
char g_nex(long x){
	if(x>=0&&x<10) return x+48;
	else return x+87;
	return 32;
}
//**************返回一到三十六进制数字
long g_xen(char c){
    if(c>='a'&&c<='z')
		return c-87;
	else
		if(c>='A'&&c<='Z')
			return c-55;
		else return c-48;
}
//**************
//**************整数返回字符
char* g_i2s(long x){
	char *re;
	long i=g_raw(x),k;
	k=i;
	re=(char*)malloc(i+1); 
	*(re+i)='\0';
	while(i--)
		*(re+i)=g_riw(x,k-i)+48;
  return re;
} 
//**************
//**************实数返回字符
char* g_r2s(double x){
	long xd=(long)x,xi,gz;
	double xr,xt;
	char *re;
	register long y=0;
	register long i=0;
	xt=xr=x-xd;
	while((xt=xt*10)>1e-6&&++y)
		xt-=g_r2i(xt);
	xi=g_raw(xd);
	gz=y!=0?0:2;
		 re=(char*)malloc(xi+y+gz);
	*(re+xi+y+1+gz)='\0';
    for(;i<=xi+y+gz;i++){
      if(i==xi) *(re+i)='.';
	  else if(i<=xi-1) *(re+i)=g_riw(xd,xi-i)+48;
	   else if(y!=0) *(re+i)=g_riw(g_r2i((xr*pow(10,y))),xi+y-i+1)+48;
	      else *(re+i)=48;
	} 
   return  re;
}
//**************
//**************十六进制数转换为十进制整数
long g_h2d(char *in){
  long x=g_len(in),y=0;
  long d=0;
  while(--x+1)
	  if(*(in+x)>'0'&&*(in+x)<'9')
		  d+=(*(in+x)-48)*(long)pow(16,y++);
	    else if(*(in+x)>='A'&&*(in+x)<='F')
			d+=(*(in+x)-55)*(long)pow(16,y++);
		 else if(*(in+x)>='a'&&*(in+x)<='f')
			 d+=(*(in+x)-87)*(long)pow(16,y++);
	return d;
}
//***************
//***************二进制数转换为十进制整数
long g_b2d(char* in){
   long x=g_len(in),y=0;
   long d=0;
   while(--x+1)
	   d+=(*(in+x)-48)*(long)pow(2,y++);
   return d;
}
//***************
//***************八进制数转换为十进制整数
long g_o2d(char* in){
   long x=g_len(in),y=0;
   long d=0;
   while(--x+1)
	   d+=(*(in+x)-48)*(long)pow(8,y++);
   return d;
}
//***************
//***************三十六进制以下进制转换十进制整数
long g_a2d(char* in,int k){
  long x=g_len(in),y=0;
   long d=0;
   while(--x+1)
	   d+=(g_xen(*(in+x)))*(long)pow(k,y++);
   return d;
}
//***************
//***************十进制数转换为十六进制数
char* g_d2h(long in){
  long x=0,y=0;
  char *re;
  register long i=1;
  if(in/16==0){
      re=(char*)malloc(2);
	  *re=g_hex(in);
	  *(re+1)='\0';
  }else{
    while(in/(long)pow(16,i++));
	re=(char*)malloc(i);
	for(--i;i>0;i--){
		if(in/16==0){
			if(i>1) {*(re+y++)=48;
			continue;}
			*(re+y++)=g_hex(in);
		continue;}
		x=in/(long)pow(16,i-1);
		*(re+y++)=g_hex(x);
      in-=x*(long)pow(16,i-1);
	   if(in<0) break;
	}
	*(re+y)='\0';
  }
return re;
}
//***************
//***************十进制数转换为八进制数
char* g_d2o(long in){
  long x=0,y=0;
  char *re;
  register long i=1;
  if(in/8==0){
      re=(char*)malloc(2);
	  *re=in+48;
	  *(re+1)='\0';
  }else{
    while(in/(long)pow(8,i++));
	re=(char*)malloc(i);
	for(--i;i>0;i--){
		if(in/8==0){
			if(i>1) {*(re+y++)=48;
			continue;}
			*(re+y++)=in+48;
		continue;}
		x=in/(long)pow(8,i-1);
		*(re+y++)=x+48;
      in-=x*(long)pow(8,i-1);
	   if(in<0) break;
	}
	*(re+y)='\0';
  }
return re;
}
//***************
//***************十进制数转换为二进制数
char* g_d2b(long in){
  long x=0,y=0;
  char *re;
  register long i=1;
  if(in/2==0){
      re=(char*)malloc(2);
	  *re=in+48;
	  *(re+1)='\0';
  }else{
    while(in/(long)pow(2,i++));
	re=(char*)malloc(i);
	for(--i;i>0;i--){
		if(in/2==0){
			if(i>1) {*(re+y++)=48;
			continue;}
			*(re+y++)=in+48;
		continue;}
		x=in/(long)pow(2,i-1);
		*(re+y++)=x+48;
      in-=x*(long)pow(2,i-1);
	   if(in<0) break;
	}
	*(re+y)='\0';
  }
return re;
}
//***************
//***************十进制数转换为三十六进制以下的数
char* g_d2a(long in,int b){
  long x=0,y=0;
  char *re;
  register long i=1;
  if(in/b==0){
      re=(char*)malloc(2);
	  *re=g_nex(in);
	  *(re+1)='\0';
  }else{
    while(in/(long)pow(b,i++));
	re=(char*)malloc(i);
	for(--i;i>0;i--){
		if(in/b==0){
			if(i>1) {*(re+y++)=48;
			continue;}
			*(re+y++)=g_nex(in);
		continue;}
		x=in/(long)pow(b,i-1);
		*(re+y++)=g_nex(x);
      in-=x*(long)pow(b,i-1);
	   if(in<0) break;
	}
	*(re+y)='\0';
  }
return re;
}
//***************
//***************两个字符连接
char* g_scat(char *a,const char *b){
   long x=g_len(a),y=g_len(b);
   char *re;
   register long i=0;
   re=(char*)malloc(x+y+1);
   for(;i<x+y;i++)
	   if(i<x)
	   *(re+i)=*(a+i);
	   else
		   *(re+i)=*(b+i-x);
	   *(re+i)='\0';
	   return re;

}
//***************
//***************从一个字符串中删除一个字符
char* g_sdelc(char*a,char c){
  char *re;
	register long y=0;
  register long x=0;
  while(*(a+x)!='\0')
   if(*(a+x++)!=c)
	   y++;
   re=(char*)malloc(y+1);
      *(re+y)='\0';
   x=y=0;
   while(*(a+x)!='\0')
   if(*(a+x++)!=c)
	   *(re+y++)=*(a+x-1);
   *(re+y)='\0';
	   return re;
}
//***************
//***************复制并覆盖字符串
char* g_scp( char *a,const char*b){
   register long x=0;
	while(*(b+x)!='\0')
		*(a+x)=*(b+x++);
	*(a+x)='\0';
	return a;
}
//***************
//***************比较两个字符
bool g_strbj(const char *a,const char *b){
   for(register int x=0;*(a+x)==*(b+x)&&*(a+x)!='\0'&&*(b+x)!='\0';x++);
	   return (x==g_len(a)&&x==g_len(b))?true:false;
}
//***************
#endif