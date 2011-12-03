/*


求欧拉回路


方法：不分有向图或者无向图，找到起点，然后dfs，只要该点有边相连，就删掉边，


继续dfs，直到改点没有边相连为止，将该点加入栈。


注意加入栈的顺序与输出的顺序相反。


无向图条件： 度为奇数的点至多有两个


有向图条件：出度等于入度，或者相差一个的点最多两个


*/





#include <string>


#include <list>


#include <stdio.h>


#include <string.h>


#include <algorithm>


using namespace std;


const int maxn = 1010;


list<string> map[26][26];


int num[26][26];


int start[26];


string words[maxn];





int ind[26], outd[26];


int n;


int op;


int o[maxn];


int tag[maxn];





void dfs ( int p )


{
    int i, j;
    for ( j = start[p]; words[j][0] - 'a' == p; j++ )
    {
        if ( tag[j] ) continue;
        i = words[j][words[j].size() - 1] - 'a';
        if ( num[p][i] == 0 ) continue;
        tag[j] = 1;
        num[p][i]--;
        dfs ( i );
    }
    op++;
    o[op] = p;
}


int main()


{
    freopen ( "pku.in", "r", stdin );
    freopen ( "pku.out", "w", stdout );
    int i, j;
    int cs;
    scanf ( "%d", &cs );
    while ( cs-- )
    {
        scanf ( "%d", &n );
        int i;
        char s[25];
        for ( i = 1; i <= n; i++ )
        {
            scanf ( "%s", s );
            words[i] = s;
        }
        sort ( words + 1, words + n + 1 );
        for ( i = 0; i < 26; i++ )
            for ( j = 0; j < 26; j++ ) map[i][j].clear();
        memset ( ind, 0, sizeof ( ind ) );
        memset ( outd, 0, sizeof ( outd ) );
        memset ( num, 0, sizeof ( num ) );
        memset ( start, 0, sizeof ( start ) );
        memset ( tag, 0, sizeof ( tag ) );
        for ( i = 1; i <= n; i++ )
        {
            if ( start[words[i][0] - 'a'] == 0 ) start[words[i][0] - 'a'] = i;
        }
        // for (i=1;i<=n;i++) puts(words[i].c_str());
//                for (i=0;i<26;i++) printf("%d ",start[i]);
//                puts("");
        for ( i = 1; i <= n; i++ )
        {
            int p = words[i][0] - 'a';
            int q = words[i][words[i].size() - 1] - 'a';
            outd[p]++;
            ind[q]++;
            map[p][q].push_back ( words[i] );
            num[p][q]++;
        }
        int st;
        int m = 0;
        for ( i = 0; i < 26; i++ )
        {
            if ( ind[i] == outd[i] - 1 || ind[i] == outd[i] + 1 ) m++;
            else if ( ind[i] != outd[i] )
            {
                m = 3;
                break;
            }
        }
        if ( m > 2 )
        {
            puts ( "***" );
            continue;
        }
        for ( i = 0; i < 26; i++ )
        {
            if ( ind[i] < outd[i] )
            {
                st = i;
                break;
            }
        }
        if ( i == 26 ) st = words[1][0] - 'a';
        op = 0;
        dfs ( st );
        if ( op < n )
        {
            puts ( "***" );
            continue;
        }
        reverse ( o + 1, o + op + 1 );
//                for (i=1;i<=op;i++) putchar(o[i]+'a');
//                putchar('\n');
        for ( i = 1; i <= op - 1; i++ )
        {
            int p = o[i];
            int q = o[i + 1];
            if ( i > 1 ) putchar ( '.' );
            printf ( "%s", map[p][q].front().c_str() );
            map[p][q].pop_front();
        }
        printf ( "\n" );
    }
    return 0;
}

