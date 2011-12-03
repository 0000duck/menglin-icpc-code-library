#include <iostream>
#include <algorithm>
using namespace std;
struct type
{
        int x,y;
        bool operator<(const type &a)
        {
                return x<a.x;
        }
};
int main()
{
  int B[10] = {0, 112, 23, 354, 45, 878,66, 87, 9898, 459 };
  type A[10];
  for (int i=0;i<10;i++) A[i].x=A[i].y=B[i];
  make_heap(A, A + 9);    
  push_heap(A, A + 10);//要求[first,last-1)已经是堆
  
  int i;
  for (i=9;i>=0;i--)
  {
        pop_heap(A,A+i+1);
        cout<<A[i].x<<endl;
  }                         
  while (1);
}

