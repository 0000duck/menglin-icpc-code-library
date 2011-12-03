#include <iostream>







#include <algorithm>





using namespace std;







void RMQ_Init ( int s[], int n )







{
    for ( int i = 1, j = 0, k = n; i + i <= n; i <<= 1 )
    {
        for ( int w = k - i; j < w; j++, k++ ) s[k] = max ( s[j], s[j + i] ); //*
        j += i;
    }
}







int RMQ_Query ( int s[], int n, int a, int b )







{
    int k = 0;
    for ( ; ( 1 << ( k + 1 ) ) <= b - a; k++ );
    int w = k * ( n + 1 ) - ( 1 << k ) + 1;
    return max ( s[w + a], s[w + 1 + b - ( 1 << k )] ); //*
}





int main()





{
    int s[1024] = {0, 2, 5, 8, 9, 4, 2, 4, 6, 8, 6, 7, 5, 3, 2, 5, 7, 8, 3, 2, 5, 7, 0, 3, 5, 7, 8, 2, 5, 7, 9, 2, 5};
    int n = 33;
    RMQ_Init ( s, n );
    while ( true )
    {
        int a, b;
        cin >> a >> b;
        cout << RMQ_Query ( s, n, a, b ) << endl;
    }
    return 0;
}

