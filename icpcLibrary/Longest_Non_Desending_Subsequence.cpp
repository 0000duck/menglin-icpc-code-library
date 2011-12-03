#include <string.h>
#include <algorithm>
using namespace std;
int LNDSS(int a[], int n) // Longest Non descending Sub Sequence
{
	int i,j,*b=new int[n+1],ans=0;
	b[ans]=-0x3f3f3f3f;
	for (i=0; i<n ; i++)
	{ // lower bound for Ascending Sub Squence
		j=upper_bound(b,b+ans+1,a[i])-b;
		if ( j>ans ) b[++ans]=a[i]; 
		else if (a[i]<b[j]) b[j]=a[i];
	}
	delete b;
	return ans ;
}
int main()
{
	freopen("l.in","r",stdin);
	int a[100];
	int n;
	scanf("%d",&n);
	int i;
	for (i=0;i<n;i++) scanf("%d",&a[i]);
	printf("%d\n",LNDSS(a,n));
	return 0;
}
