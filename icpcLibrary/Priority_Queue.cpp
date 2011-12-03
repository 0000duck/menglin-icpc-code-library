#include <string.h>
#include <stack>
#include <queue>
using namespace std;
bool gre(int a,int b)
{
        return a>b;
}
int main()
{
	int a[20]={1,2,3,4,5,945,323,23,43,45};//10 numbers in total
	priority_queue<int,vector<int>,gre> Q(a,a+10);
	while (!Q.empty())
	{
		printf("%d\n",Q.top());//输出最大的
		Q.pop();
	}
	puts("-------");
	int i;
	for (i=0;i<10;i++) Q.push(a[i]);
	while (!Q.empty())
	{
		printf("%d\n",Q.top());
		Q.pop();
	}
	while (1);
	return 0;
}
