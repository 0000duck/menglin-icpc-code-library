#include <stdio.h>
const int N = 250000 + 5;
int num;
struct Node{
    Node *branch[26];
    int key;
    Node(){
        for ( int i=0; i<26; i++ )
            branch[i] = NULL;
        key = 0;//×Ö·û´®µÄ±àºÅ
    }
} *root;
void NewNode( Node *point, int cnum )
{
    Node *nnode = new Node();
    point->branch[cnum] = nnode;
}

int insert( char *word )
{
    Node *point = root;
    while ( *word!='\0' )
    {
        int cnum = *word-'a';
        if ( point->branch[cnum] == NULL  )
            NewNode( point , cnum );
        point = point->branch[cnum];
        word ++;
    }
    if ( point->key==0 )
    {
        point->key = ++num;
    }
    return point->key;
}
int main ()
{
    num = 0;
    root = new Node();
    int t1, t2;
    char s1[15], s2[15];
    while ( scanf("%s %s", s1, s2 )!=EOF )
    {
        t1 = insert( s1 );
        t2 = insert( s2 );
