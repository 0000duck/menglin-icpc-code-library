/*
����ͼƥ�䣬�������㷨�����ߵĶ��㶼�Ǵ�0��ʼ��ŵ�
1.ò�ƶ���ͼƥ�������������ϣ����и�Ϊһ��
2.��Щ��Ŀ��ʵ�ϲ�����ƥ�����Ŀ��������С�㸲�ǵ���Ŀ��ֻ�ǿ���֤����ͼ�Ƕ���ͼ��
�����ɶ�������ͼ�����ƥ����Ŀ������С�㸲����Ŀ������ת����˶���ƥ������

��С�㸲�ǣ��������ٵĵ�ʹ��ÿ���߶����ٺ����е�һ���������������Ȼֱ��ȡ���ƥ
���һ�νڵ㼴�ɡ�

����ͼ�ж��������ҽ�������ͼ��ÿһ����·�Ĵ�����Ϊż��ʱ������һ��żͼ������޻�
·���൱����һ��·�Ĵ���Ϊ0��0��Ϊż����

��һ������ͼ�У�·�����Ǿ�����ͼ����һЩ·����ʹ֮������ͼ�е����ж��㣬���κ�һ��
��������ֻ��һ��·����֮���������������Щ·���е�ÿ��·����������ʼ���ߵ������յ㣬
��ôǡ�ÿ��Ծ���ͼ�е�ÿ������һ���ҽ�һ�Σ������������ͼ�д��ڻ�·����ôÿ��·����
��һ������ͨ�Ӽ�
��С·�����Ǿ����ҳ���С��·��������ʹ֮��Ϊͼ��һ��·�����ǣ�

·�����������ͼƥ��Ĺ�ϵ�� ��С·�����ǣ����У������ƥ������
�������ƥ���������ǰѣ��е�ÿ������pi�ֳ���������pi'��pi''��
�����p�д���һ��pi��pj�ıߣ���ô�ڶ���ͼ�У��о���һ������pi'��pj''�ıߣ�

�ǵ�memset map
*/
#include <stdio.h>
#include <memory.h>
#define null 0
const int size = 510;

int maxmatch( int n, int m, bool w[][size], int *p)//if p!=0 ,p returns a set of match
{

        int p_n[size];
        int p_m[size];

        bool sign[size];
        int q[size],from[size],s,t;

        int i,j,link,now,h;

        memset( p_n, -1, sizeof(int)*n );
        memset( p_m, -1, sizeof(int)*m );

        for(i=0;i<n;i++)
        if(p_n[i]==-1)
        {
                memset( sign, 0, sizeof(bool)*m );
                
                s=1;link=-1;
                from[0]=-1;

                q[0]=size-1;
                p_m[size-1]=i;

                for(t=0;t<s;t++)
                {
                   now=q[t];
                   for(j=0;j<m;j++)
                   {
                           if( w[p_m[now]][j] != null && sign[j]==0 )
                           {
                                        sign[j]=1;
                                        q[s]=j;
                                        from[s++]=t;

                                        if(p_m[j]==-1)
                                        {
                                                link=s-1;
                                                break;
                                        }
                           }
                   }
                   if(j<m)break;
                }

                if(t<s)
                {
                         while(from[link]!=-1)
                         {
                                        h=from[link];
                                        p_m[q[link]]=p_m[q[h]];
                                        p_n[p_m[q[h]]]=q[link];
                                        link=h;
                         }
                }

                //���걸ƥ��
                //else return 0;
        }
        int an;

        for(i=0,an=0;i<n;i++)
        {
                if(p)p[i]=p_n[i];
                if(p_n[i]>=0)an++;
        }
        return an;
}

bool map[size][size];

int main() {
        int n, k, i, a, b;
        scanf( "%d%d", &n, &k );
        for( i=0; i<k; i++ ) {
                scanf( "%d%d", &a, &b );
                a--, b--;
                map[a][b] = 1;        //ֻҪ��һ�ξ����ˣ���0��ʼ
        }

        printf( "%d\n", maxmatch( n, n, map, 0 ) );
        return 0;
}
