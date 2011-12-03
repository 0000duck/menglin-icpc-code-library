/*
  Name: ���㼸�α�׼����� 
  Copyright: LogicalMars Library
  Author: StarFish && Improved by LogicalMars
  Date: 12-10-08 12:11
*/

#include <stdlib.h>
#include <math.h>

const double zero = 1e-6;
const double infinity = 1e20;
struct TPoint{
	double x,y;
	};

struct TLineSeg{
	TPoint a,b;
	};

double dis(TPoint p1,TPoint p2)//��ƽ��������֮��ľ���
{
	return(sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)));	
}

double multiply(TPoint p1,TPoint p2,TPoint p0)
{
	return((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y));	
}

//ȷ�������߶��Ƿ��ཻ
double max(double m1,double m2)
{
    if (m1>m2) return m1;
    return m2;
}
double min(double m1,double m2)
{
    if (m1<m2) return m1;
    return m2;
}
int intersect(TLineSeg u,TLineSeg v)//���ϸ��ཻ���ϸ��ཻҪ�� >= �ĳ� > 
{
	return( (max(u.a.x,u.b.x)>=min(v.a.x,v.b.x))&&
	        (max(v.a.x,v.b.x)>=min(u.a.x,u.b.x))&&
	        (max(u.a.y,u.b.y)>=min(v.a.y,v.b.y))&&
	        (max(v.a.y,v.b.y)>=min(u.a.y,u.b.y))&&
	        (multiply(v.a,u.b,u.a)*multiply(u.b,v.b,u.a)>=0)&&
	        (multiply(u.a,v.b,v.a)*multiply(v.b,u.b,v.a)>=0));
}

//�жϵ�p�Ƿ����߶�l��
int online(TLineSeg l,TPoint p)
{
    double temp=multiply(l.b,p,l.a);    
	return(temp>=-zero && temp<=zero &&( ((p.x-l.a.x)*(p.x-l.b.x)<=-zero )||( (p.y-l.a.y)*(p.y-l.b.y)<=-zero )) );
}


//�ж��������Ƿ����
int Euqal_Point(TPoint p1,TPoint p2)
{
return((abs(p1.x-p2.x)<zero)&&(abs(p1.y-p2.y)<zero));
}

//һ���߶��ཻ�жϺ��������ҽ���u,v�ཻ���ҽ��㲻��u,v�Ķ˵�ʱ����Ϊtrue;
int intersect_A(TLineSeg u,TLineSeg v)
{
	return((intersect(u,v))&&
	       (!Euqal_Point(u.a,v.a))&&
	       (!Euqal_Point(u.a,v.b))&&
	       (!Euqal_Point(u.b,v.a))&&
	       (!Euqal_Point(u.b,v.b)));
}


/*===============================================

   �жϵ�q�Ƿ��ڶ����Polygon�ڣ�
   ���ж�����������͹�򰼶���Σ�
   Polygon�д�Ŷ���ε���ʱ�붥������

================================================*/

int InsidePolygon(int vcount,TPoint Polygon[],TPoint q)
{
	int c=0,i,n;
	TLineSeg l1,l2;
		
	l1.a=q;
	l1.b=q;
	l1.b.x=infinity;
	n=vcount;
	for (i=0;i<vcount;i++)
	{
		l2.a=Polygon[i];
		l2.b=Polygon[(i+1)%n];
		if (  (intersect_A(l1,l2))||
		      (
		        (online(l1,Polygon[(i+1)%n]))&&
		        (
		         (!online(l1,Polygon[(i+2)%n]))&&
		         (multiply(Polygon[i],Polygon[(i+1)%n],l1.a)*multiply(Polygon[(i+1)%n],Polygon[(i+2)%n],l1.a)>0)
		         ||
		         (online(l1,Polygon[(i+2)%n]))&&
		         (multiply(Polygon[i],Polygon[(i+2)%n],l1.a)*multiply(Polygon[(i+2)%n],Polygon[(i+3)%n],l1.a)>0)		
		        )
		      )
		   ) c++;
		}
		return(c%2!=0);
}


/********************************************\
*                                            *
*      �������ε����                        *
*                                            *
*     Ҫ������ʱ�뷽���������ζ���           *
*     ������͹����λ򰼶����			   *
*     ���Ϊ˳ʱ�룬��Ϊ��Ӧ��ֵ                  *
*                                            *
\********************************************/

double area_of_polygon(int vcount,double x[],double y[])
{
  int i;
  double s;
  if (vcount<3) return 0;
  s=y[0]*(x[vcount-1]-x[1]);
  for (i=1;i<vcount;i++)
     s+=y[i]*(x[(i-1)]-x[(i+1)%vcount]);
  return s/2;
  }


/*====================================================================================
   Ѱ��͹�� graham ɨ�跨

  PointSetΪ����ĵ㼯��
  chΪ�����͹���ϵĵ㼯��������ʱ�뷽������;
  nΪPointSet�еĵ����Ŀ
  lenΪ�����͹���ϵĵ�ĸ�����

	   ����һ��ɨ��ĵ�PointSet[i]=P2,��ǰջ����������ch[top]=P1,ch[top-1]=P0,
     ���P1P2�����P0P1�ڵ�P1������ת(����Ҳ����)����P0,P1һ����͹���ϵĵ㣻
     ����P1һ������͹���ϵĵ㣬Ӧ�ý����ջ��
     ����������ͼ�е�1��һ����͹���ϵĵ㣬��ͼ�е�1��һ������͹���ϵĵ㣬��Ϊ
     �������ӵ�0,2����͹���ı�
           2
           |
           |                 _____2
           1               1
          /               /
    ____0/          ____0/

====================================================================================*/
//δ����ʵ�����ͣ�������1e-8
TPoint bp;
bool PolarComp(const TPoint &p1,const TPoint &p2)
{
    int u=multiply(p1,p2,bp);
    return (u>0) || (u==0 && dis(p1,bp)<dis(p2,bp));
}
void Graham_scan(TPoint PointSet[],TPoint ch[],int n,long &len)
{
    if (n<=3)
    {
        len=n;
        int i;
        for (i=0;i<n;i++) ch[i]=PointSet[i];
        return;
    }
    int i,j,k=0,top=2;
	TPoint tmp;
	
	//ѡȡPointSet��y������С�ĵ�PointSet[k]����������ĵ��Ҷ������ȡ����ߵ�һ��
	for(i=1;i<n;i++)
		if ((PointSet[i].y<PointSet[k].y)||((PointSet[i].y==PointSet[k].y)&&(PointSet[i].x<PointSet[k].x)))
	    k=i;
	tmp=PointSet[0];
	PointSet[0]=PointSet[k];
	PointSet[k]=tmp; //����PointSet��y������С�ĵ���PointSet[0]
	bp = PointSet[0];
	sort(PointSet,PointSet+n,PolarComp);
	ch[0]=PointSet[0];
	ch[1]=PointSet[1];
	ch[2]=PointSet[2];	
	top=2;
	for (i=3;i<n;i++)
		{
			while (multiply(PointSet[i],ch[top],ch[top-1])>=0 && top>0) top--;
			if (top<0)break;
			ch[++top]=PointSet[i];
			}
	len=top+1;
}

=====================================================================
��ֱ��			δ����1e-8
=====================================================================

long Diameter(TPoint ch[],long len)
{
	if (len==1) return 0;
	if (len==2) return dis(ch[0],ch[1]);
	int nu,nv,v,u,k;	
	long re=0;
	ch[len]=ch[0];
	for (u=0,v=1;u<len;u=nu)
	{
		nu=u+1;
		while(1)
		{            
			nv=(v+1)%len;
			k=( (ch[nu].x-ch[u].x)*(ch[nv].y-ch[v].y) - 
				(ch[nv].x-ch[v].x)*(ch[nu].y-ch[u].y));
			if (k<=0) break;		
			v=nv;			
		}
		re=max(re,dis(ch[u],ch[v]));
		re=max(re,dis(ch[u],ch[nv]));
	}
	return re;
}
