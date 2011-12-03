//FORD_FULKERSON
#include <iostream>
#include <queue>
using namespace std;

//�ڽ���ʵ��
const long MAXN=1000;
const long lmax=0x7FFFFFFF;

long Net[MAXN][MAXN];//��������
long Path[MAXN];//����·��
long Lv[MAXN];//����·��ͨ������

queue<long> q;
long m,n;//�㣬��
long Start,End;

void init()
{
    while (!q.empty())
    {
        q.pop();
    }
    memset(Path,-1,sizeof(Path));
}


long Min(long a,long b)
{
    return a<b?a:b;
}

long bfs()
{
    init();
    Path[Start]=0;
    Lv[Start]=lmax;

    q.push(Start);         //queue q����������һ��һ����ͼ�ϵĶ����

    while (!q.empty())
    {
        long t=q.front();
        q.pop();         //ȡ�˶���ͷ��Ȼ�����pop�� ��

        if (t==End)
        {
            break;         //��Ϊ���Ƚ��ȳ�
        }           //�����������һ���㣬�Ͳ�Ҫ����

        long i;
        for (i=1;i<=m;++i)       //i�ǵ�
        {
            if (i!=Start && Path[i]==-1 && Net[t][i])    //Net[t][i]=1 ��ʾ���д� t~i �������� t->i�����ǿɴ��
            {
                Lv[i]=Min(Lv[t],Net[t][i]);
                q.push(i);
                Path[i]=t;       //path[i]����������������ȫ�������ǰһ���ڵ�
            }
        }
    }

    if (Path[End]==-1)        //�ѵ�end�����ˣ�����start��end ��һ��ͨ·������ͨ�����path��ָʾ��
    {
        return -1;
    }

    return Lv[m];
}

void print(long n)
{
    printf("%ld\n",n);
}

void Ford_Fulkerson()
{
    long i;
    long Max_Flow=0;


    for (i=0;i<n;++i)           //n��ʾ��������m��ʾ������
    {
        long from,to,cost;
        scanf("%ld %ld %ld",&from,&to,&cost);     //*********************************//�ޱȾ���
        Net[from][to]=cost;          //�ǳ����䰡��һ���㵽��һ����Ĳ��������϶������ģ��ܼ��ϵ�������
                //�������������ڻ����ģ����x=u->v Ϊ������ʾ���Ǵ�u->v����֮����Ϊv->u
   //costΪʣ����           //����xΪ����ʱ��v->u�Ǽ���������������ֻȡ�����������������x=u->vΪ����v->uΪ�����ظ��ˣ�ֻ����һ�ξ͹��ˣ����Զ�ȡ�����ɣ��޵еĴ���
        //�����������������չ ʣ����Ϊ����-��ռ����   //���⣬��������������϶�Ϊ���ģ���Ϊ����ȡ������ֻȡ������������������������Ϊ��
        //��������Ҫ�������������
    }

    scanf("%ld %ld",&Start,&End);

    long step;
    while ((step=bfs())!=-1)//��������·������������
    {
        Max_Flow+=step;
        long now=End;

        while (now!=Start)
        {
            long pre=Path[now];     //path[now]���nowΪ�����ĸõ��ǰһ����ʼ��
            Net[pre][now]-=step;    //���ᵽ����ȥ����Ϊ ��-�� ���Ǽ�min()�ģ������bfs�������ӣ����Բ�����ɸ���
            Net[now][pre]+=step;    //����������+������ȥ���϶����Ḻ������Net[][]������ ����ˮ�������������ж��ٿ��Լ������������ʣ��������������
            now=pre;
        }
    }

    print(Max_Flow);
}

int main()
{

    while (scanf("%ld %ld",&m,&n)!=EOF)
    {
        Ford_Fulkerson();
    }
    return 0;
}
