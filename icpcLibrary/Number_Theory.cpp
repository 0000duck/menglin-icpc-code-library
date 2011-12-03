/*==========================================*\
*                                           
*            数论算法函数库                  
*                                          
*                  copyright starfish      
*                      2000/10/25          
*Content:
    欧几里德算法求最大公约数
    扩展欧几里德算法求gcd(a,b)=ax+by
    Miller_Rabin随机素数测试算法    
    返回x的二进制长度   
    返回x的二进制表示中从低到高的第i位，最低位为第一位      
    模取幂运算 计算a^b mod n      
    求解模线性方程 ax=b (mod n) ,n>0     
    求解模线性方程组 (中国余数定理)                  
\*==========================================*/

/*********************************************

      欧几里德算法求最大公约数

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

    扩展欧几里德算法求gcd(a,b)=ax+by

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

    Miller_Rabin随机素数测试算法

   说明：这种算法可以快速地测试一个数是否
   满足素数的必要条件，但不是充分条件。不
   过也可以用它来测试素数，出错概率很小，
   对于任意奇数n>2和正整数s,该算法出错概率
   至多为2^(-s)，因此，增大s可以减小出错概
   率，一般取s=50就足够了。

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
	
		返回x的二进制长度

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
	
		返回x的二进制表示中从低到高的第i位
		，最低位为第一位

*********************************************/

int BitAt(int x, int i)
{
	return ( x & (1 << (i-1)) );
}

/*********************************************

        模取幂运算 计算a^b mod n

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

      求解模线性方程 ax=b (mod n) ,n>0

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

      求解模线性方程组 (中国余数定理)

           a=B[1] (mod W[1])
           a=B[2] (mod W[2])
               ........
           a=B[n] (mod W[n])

   其中W,B已知，W[i]>0且W[i]与W[j]互质,  求a

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

