#include <string.h>
#include <stdio.h>
#include <math.h>
const unsigned long Prime_list[28]=
{
53,         97,         193,        389,        769,
1543,       3079,        6151,       12289,      24593,
49157,      98317,        196613,     393241,     786433,
1572869,    3145739,       6291469,    12582917,   25165843,
201326611, 402653189,       50331653,   100663319,

805306457, 1610612741, 3221225473ul,    4294967291ul
};
const int M = 6291469;
struct type
{
        int key;
        int re;
        type(int p)
        {
                key=p;
                re=1;
                next=NULL;
        }
        type *next;
};
class HashTable
{
        public:
                type *table[M];
                HashTable()
                {
                        memset(table,0,sizeof(table));
                }
                int hash(int p)
                {
                        int q=p%M;
                        while (q<0) q+=M;
                        return q;
                }
                void insert(int key)
                {
                        int p=hash(key);
                        type *i = table[p];
                        for(;i!=NULL;i=i->next)
                        {
                                if ((*i).key == key) break;
                        }
                        if (i==NULL)
                        {
                                type *tmp = new type(key);
                                tmp->next = table[p];
                                table[p]=tmp;
                        }
                        else (*i).re++;
                }
                int check(int key)
                {
                        int p=hash(key);
                        type *i = table[p];
                        for (;i!=NULL;i=i->next)
                        {
                                if ((*i).key == key) return (*i).re;
                        }
                        return 0;
                }
}tab;
int main()
{
        int a[6];
        int x[6];
        int i;
        for (i=1;i<=5;i++) scanf("%d",&a[i]);

        for (x[1]=-50;x[1]<=50;x[1]++)
                for (x[2]=-50;x[2]<=50;x[2]++)
                        {
                                int t,i;
                                if (x[1]==0 || x[2]==0) continue;

                                t=0;
                                for (i=1;i<=2;i++) t+=a[i]*x[i]*x[i]*x[i];
                                tab.insert(t);
                        }
        int sum=0;
        for (x[3]=-50;x[3]<=50;x[3]++)
                for (x[4]=-50;x[4]<=50;x[4]++)
                        for (x[5]=-50;x[5]<=50;x[5]++)
                        {
                                int t,i;
                                if (x[3]==0 || x[4]==0 || x[5]==0) continue;

                                t=0;
                                for (i=3;i<=5;i++) t+=a[i]*x[i]*x[i]*x[i];
                                sum+=tab.check(-t);
                        }
        printf("%d\n",sum);
        return 0;
}
