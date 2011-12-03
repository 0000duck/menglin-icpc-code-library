using namespace std;







#include <fstream>







#include <string>







ifstream fin ( "prime.in" );







ofstream fout ( "prime.out" );







const long maxlenth = 0x7fffffff / 2;







int n;







long map[110][110];







long dis[110];







short visited[110];







void prime()







{
    int i, j;
    for ( i = 2; i <= n; i++ ) dis[i] = maxlenth;
    dis[1] = 0;
    memset ( visited, 0, sizeof ( visited ) );
    int count = 0;
    while ( count <= n )
    {
        long k, min = maxlenth;
        for ( i = 1; i <= n; i++ ) if ( !visited[i] && dis[i] < min )
            {
                min = dis[i];
                k = i;
            }
        if ( min == maxlenth ) break;
        visited[k] = 1;
        count++;
        for ( i = 1; i <= n; i++ )
        {
            if ( !visited[i] && i != k && dis[i] > map[k][i] ) dis[i] = map[k][i];
        }
    }
    long re = 0;
    for ( i = 1; i <= n; i++ ) re += dis[i];
    fout << re << endl;
}







int main()







{
    fin >> n;
    int i, j;
    for ( i = 1; i <= n; i++ )
        for ( j = 1; j <= n; j++ ) fin >> map[i][j];
    prime();
    return 0;
}



