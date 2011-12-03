/*
  Name: High Precision Calculation
  Copyright: LogicalMars Library
  Author: LogicalMars
  Date: 12-10-08 15:02
  Description: µ¹Ðò´æ´¢£¬a[0]´æ´¢Î»Êý 
*/

#include <stdio.h>
#include <string.h>
const long maxn=10000;
long a[maxn],b[maxn];
void HPread(long *a)
{
    char s[maxn];
    scanf("%s",s);
    long i;
    a[0]=strlen(s);
    for (i=0;i<=a[0]-1;i++)
    {
        a[a[0]-i]=s[i]-'0';
    }
}
void HPprint(long *c)
{
    long i;
    for (i=c[0];i>=1;i--) printf("%ld",c[i]);
    printf("\n");
}
void HPswap(long *a,long *b)
{
    long i;
    long c[maxn];
    long l1=a[0],l2=b[0];
    for (i=0;i<=l1;i++) {c[i]=a[i];a[i]=0;}
    for (i=0;i<=l2;i++) {a[i]=b[i];b[i]=0;}
    for (i=0;i<=l1;i++) b[i]=c[i];
}
int HPcomp(long *a,long *b)//a>b,return 1,a==b,return 0,a<b,return -1
{
    if (a[0]>b[0]) return 1;
    else if (a[0]<b[0]) return -1;
    else 
    {
        long i;
        for (i=a[0];i>=1;i--) 
        {
            if (a[i]>b[i]) return 1;
            else if (a[i]<b[i]) return -1;
        }        
    }
    return 0;
}
void HPplus(long *a,long *b,long *c)
{
    long i,j;
    j=0;
    for (i=1;i<=a[0] || i<=b[0];i++)
    {
        c[i]=a[i]+b[i]+j;
        j=c[i]/10;
        c[i]%=10;
    }
    if (j!=0) c[i]=j;
    c[0]=a[0]>b[0]?a[0]:b[0]+2;
    while (c[c[0]]==0 && c[0]>1) c[0]--;
}    
void HPminus(long *a,long *b,long *c)
{
    long i,j;
    j=0;
    for (i=1;i<=a[0];i++)// a must be larger than b
    {
        c[i]=a[i]-b[i]-j;
        if (c[i]<0) {c[i]+=10;j=1;}
            else j=0;
    }
    c[0]=a[0]+2;
    while (c[c[0]]==0 && c[0]>1) c[0]--;
}
void HPmulty(long *a,long *b,long *c)
{
    long i,j,k;
    for (i=1;i<=a[0];i++)
    {
        for (j=1;j<=b[0];j++) c[i+j-1]+=a[i]*b[j];
        k=0;
        for (j=1;j<=i+b[0];j++) 
        {
            c[j]+=k;
            k=c[j]/10;
            c[j]%=10;
        }
    }
    c[0]=a[0]+b[0]+3;
    while (c[c[0]]==0 && c[0]>1) c[0]--;    
}       
void HPdividNUM(long *a,long x,long *c)
{
    long d=0;
    long i;
    for (i=a[0];i>=1;i--)
    {
        c[i]=d*10+a[i];
        d=c[i]%x;
        c[i]/=x;
    }
    c[0]=a[0]+2;
    while (c[c[0]]==0 && c[0]>1) c[0]--;      
}
void HPdividHP(long *a,long *b,long *c)
{
    long d[maxn];
    memset(d,0,sizeof(d));
    long i,j;
    long t[maxn];
    d[0]=1;
    for (i=a[0];i>=1;i--)
    {
        memset(t,0,sizeof(t));
        t[0]=d[0]+1;
        for (j=t[0];j>=2;j--) t[j]=d[j-1];
        while (t[t[0]]==0 && t[0]>1) t[0]--;
        t[1]=a[i];              //t=d*10+a[i]
        
        long temp=0;
        while (HPcomp(t,b)>=0)//t>b
        {
            temp++;
            HPminus(t,b,t);
        }
        c[i]=temp;
        memset(d,0,sizeof(d));
        for (j=0;j<=t[0];j++) d[j]=t[j];
    }
    c[0]=a[0]+2;
    while(c[c[0]]==0 && c[0]>1) c[0]--;
}        
int main()
{
    long c[maxn];
    printf("a=?"); HPread(a);
    printf("b=?"); HPread(b);
    printf("a+b=");
    memset(c,0,sizeof(c));HPplus(a,b,c);HPprint(c);
    printf("-------------------------------\n");
    
    printf("a-b=");
    if (HPcomp(a,b)==-1) 
    {
        HPswap(a,b);
        printf("-");
    }
    memset(c,0,sizeof(c));
    HPminus(a,b,c);     
    HPprint(c);
    printf("-------------------------------\n");
    
    printf("a*b=");
    memset(c,0,sizeof(c));
    HPmulty(a,b,c);
    HPprint(c);
    printf("-------------------------------\n");

    printf("a=?"); HPread(a);
    long x;
    printf("x=?"); scanf("%ld",&x);
    printf("a/x=");
    memset(c,0,sizeof(c));
    HPdividNUM(a,x,c);
    HPprint(c);
    printf("-------------------------------\n");
    
    printf("b=?"); HPread(b);
    memset(c,0,sizeof(c));
    HPdividHP(a,b,c);
    HPprint(c);
    printf("-------------------------------\n");
   
    while (1);
    return 0;
}
