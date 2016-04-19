#include <iostream>
using namespace std;

int N, *maps, *ans, x, y, Pi, Qi, en, ex, counts, con, *fuck, FUCK;
bool **isLinked, *visited;
bool flag = true;

void identifyWhichLine(int t)
{
    x = 1;
    while(t>x)
    {
        t-= x;
        x++;
    }
    y = t;
}


void UnionK(int m, int n)
{
    if(m == n ) return;
        maps[m]=n;
}

int find(int x)
{
    int start = x, tmp;
    while(maps[x] >= 0)
        x = maps[x];
    while(start != x)
    {
        tmp = maps[start];
        maps[start] = x;
        start = tmp;
    }
    return x;
}


void getTheRoad(int t)
{
    if(!flag) return;
    if(t==ex)
    {
        cout << en << ' ';
        for(int i = 0;i<con;i++)
            cout << ans[i] << ' ';
        flag = false;
        return ;
    }
    for(int i = 0;i < 4;i++)
    {
        identifyWhichLine(t);
        if(!(y==1&&i==0)&&!(y==x&&i==1))
        {
            if(i==0)
            {
                if(isLinked[t][0] && find(t-x)==find(ex))
                {
                    if(visited[t-x])
                        continue;
                    visited[t-x] = true;
                    ans[con++] = t-x;
                    getTheRoad(t-x);
                    con--;
                    visited[t-x] = false;
                }
            }
            else if(i==1)
            {
                if(isLinked[t][1] && find(t-x+1)==find(ex))
                {
                    if(visited[t-x+1])
                        continue;
                        visited[t-x+1] = true;
                    ans[con++] = t-x+1;
                    getTheRoad(t-x+1);
                    con--;
                    visited[t-x+1] = false;

                }
            }
            else if(i==2&&x!=N)
            {
                if(isLinked[t][2] && find(t+x)==find(ex))
                {
                    if(visited[t+x])
                        continue;
                    visited[t+x] = true;
                    ans[con++] = t+x;
                    getTheRoad(t+x);
                    con--;
                    visited[t+x] = false;
                }
            }
            else if(i==3&&x!=N)
            {
                if(isLinked[t][3] && find(t+x+1)==find(ex))
                {
                    if(visited[t+x+1])
                        continue;
                    visited[t+x+1] = true;
                    ans[con++] = t+x+1;
                    getTheRoad(t+x+1);
                    con--;
                    visited[t+x+1] = false;
                }
            }
        }
    }
}

int main()
{
    cin >> N >> en >> ex;
    maps = new int[N*(N+1)/2+1];
    ans = new int[N*(N+1)/2+1];
    fuck = new int[N*(N+1)/2+1];
    visited = new bool[N*(N+1)/2+1];
    for(int i = 0;i<N*(N+1)/2;i++)
        maps[i] = -1;
    isLinked = new bool*[N*(N+1)/2+1];
    for(int i = 0;i<N*(N+1)/2+1;i++)
    {
        visited[i] = false;
        isLinked[i] = new bool[4];
        for(int j = 0; j<4;j++)
            isLinked[i][j] = false;
    }

    while(cin >> Pi)
    {
        cin >> Qi;
        identifyWhichLine(Pi);
        if(!(y==1&&Qi==0)&&!(y==x&&Qi==1))
        {
            if(Qi == 0&&x!=1)
            {
                UnionK(Pi,Pi-x);
                isLinked[Pi][0] = true;
                isLinked[Pi-x][3] = true;
            }
            else if(Qi == 1&&x!=1)
            {
                UnionK(Pi,Pi-x+1);
                isLinked[Pi][1] = true;
                isLinked[Pi-x+1][2] = true;
            }
            else if(Qi == 2&&x!=N)
            {
                UnionK(Pi,Pi+x);
                isLinked[Pi][2] = true;
                isLinked[Pi+x][1] = true;
            }
            else if(Qi == 3&&x!=N)
            {
                UnionK(Pi,Pi+x+1);
                isLinked[Pi][3] = true;
                isLinked[Pi+x+1][0] = true;
            }
        }
        if(find(en)==find(ex)&&find(en)!=0)
            break;
    }

    con = 0;
    counts = en;
    getTheRoad(counts);

    return 0;
}
