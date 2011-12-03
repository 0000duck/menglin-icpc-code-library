/*==========================================*\
*                                           
*            �����㷨������                  
*                                          
*                  copyright starfish      
*                      2000/10/25          
*Content:
    ŷ������㷨�����Լ��
    ��չŷ������㷨��gcd(a,b)=ax+by
    Miller_Rabin������������㷨    
    ����x�Ķ����Ƴ���   
    ����x�Ķ����Ʊ�ʾ�дӵ͵��ߵĵ�iλ�����λΪ��һλ      
    ģȡ������ ����a^b mod n      
    ���ģ���Է��� ax=b (mod n) ,n>0     
    ���ģ���Է����� (�й���������)                  
\*==========================================*/

/*********************************************

      ŷ������㷨�����Լ��

                   copyright starfish
                           2000/10/24

*********************************************/

//classic euclid algorithm to calculate the gcd(a,b),
//ie. greatest common divisor of a and b

int euclid(int a,int b)
{
   if (b==0) return a;
      else return(euclid(b,a%b));
   }

/*********************************************

    ��չŷ������㷨��gcd(a,b)=ax+by

                   copyright starfish
                           2000/10/24

*********************************************/

//extended euclid algorithm to calculate the gcd(a,b),
//as well as the integer x and y where gcd(a,b)=a*x+b*y

int ext_euclid(int a,int b,int &x,int &y)
{
   int t,d;
   if (b==0) {x=1;y=0;return a;}
   d=ext_euclid(b,a %b,x,y);
   t=x;
   x=y;
   y=t-a/b*y;
   return d;
}


/*********************************************

    Miller_Rabin������������㷨

   ˵���������㷨���Կ��ٵز���һ�����Ƿ�
   ���������ı�Ҫ�����������ǳ����������
   ��Ҳ��������������������������ʺ�С��
   ������������n>2��������s,���㷨�������
   ����Ϊ2^(-s)����ˣ�����s���Լ�С�����
   �ʣ�һ��ȡs=50���㹻�ˡ�

*********************************************/

int Witness(int a,int n)
{
  int i,d=1,x;
  for (i=ceil(log((float)n-1)/log(2.0))-1;i>=0;i--)
  { x=d;
    d=(d*d)%n;
    if ((d==1)&&(x!=1)&&(x!=n-1)) return 1;
    if (((n-1)&(1<<i))>0) d=(d*a)%n;
  }
 return (d==1?0:1);	
}

int Miller_Rabin(int n,int s)
{
  int j,a;
  for (j=0;j<s;j++)
   { a=rand()*(n-2)/RAND_MAX+1;
     if (Witness(a,n)) return 0;
   	}
  return 1;	
}


/*********************************************
	
		����x�Ķ����Ƴ���

*********************************************/
int BitLength(int x)
{
	int d = 0;
	while (x > 0) {
		x >>= 1;
		d++;
	}
	return d;
}

/*********************************************
	
		����x�Ķ����Ʊ�ʾ�дӵ͵��ߵĵ�iλ
		�����λΪ��һλ

*********************************************/

int BitAt(int x, int i)
{
	return ( x & (1 << (i-1)) );
}

/*********************************************

        ģȡ������ ����a^b mod n

*********************************************/

int Modular_Expoent(int a,int b,int n)
{

    int i, y=1;
    for (i = BitLength(b); i > 0; i--)
    { 
         y = (y*y)%n;
         if (BitAt(b,i) > 0) 
			 y = (y*a)%n;
    }
   return y;

}

/********************************************

      ���ģ���Է��� ax=b (mod n) ,n>0

*********************************************/

void modular_linear_equation_solver(int a,int b,int n)
{
   int e,i,d;
   int x,y;
   d=ext_euclid(a,n,x,y);
   if (b%d>0) printf("No answer!\n");
      else
         {  e=(x*(b/d))%n;
            for (i=0;i<d;i++)  //notice! here x maybe <0
               printf("The %dth answer is : %ld\n",i+1,(e+i*(n/d))%n); 
            }
   }

/*********************************************

      ���ģ���Է����� (�й���������)

           a=B[1] (mod W[1])
           a=B[2] (mod W[2])
               ........
           a=B[n] (mod W[n])

   ����W,B��֪��W[i]>0��W[i]��W[j]����,  ��a

*********************************************/

int China(int B[],int W[],int k)
{  int i;
   int d,x,y,a=0,m,n=1;
   for (i=0;i<k;i++)
      n*=W[i];
   for (i=0;i<k;i++)
      {  m=n/W[i];
         d=ext_euclid(W[i],m,x,y);
         a=(a+y*m*B[i])%n;
         }
   if (a>0) return a;
      else return(a+n);
}

