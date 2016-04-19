#include <iostream>
using namespace std;

class MyGraph
{
private:
    int Vers, Edges, Start, End;
    int **Connected, *visited;
    long long **Value, minLen, tempMinLen;
    bool flag;
    void getTheRoad(int t)
    {
        if(t==End)
        {
            if(flag)
            {
                minLen = tempMinLen;
                flag = false;
            }
            else if(tempMinLen < minLen)
                minLen = tempMinLen;
            return ;
        }
        for(int i = 1; i < Vers+1;i++)
        {
            if(Connected[t][i]==1 && visited[i]!=1)
            {
                visited[i] = 1;
                tempMinLen += Value[t][i];
                getTheRoad(i);
                tempMinLen -= Value[t][i];
                visited[i] = 0;
            }
        }
    }
public:
    MyGraph(int v, int e, int s, int en)
    {
        Vers = v; Edges = e; minLen = 0;
        Start = s; End = en; tempMinLen = 0;
        Value = new long long*[Vers+1];
        Connected = new int*[Vers+1];
        visited = new int[Vers+1];
        for(int i = 0;i<Vers+1;i++)
        {
            visited[i] = 0;
            Value[i] = new long long[Vers+1];
            Connected[i] = new int[Vers+1];
            for(int j = 0;j<Vers+1;j++)
            {
                Value[i][j] = 0;Connected[i][j] = 0;
            }
        }
    }
    void Insert(int a, int b, long long p)
    {
        if(Connected[a][b] == 1)
        {
            if(p<Value[a][b])
                Value[a][b] = p;
        }
        else
            Value[a][b] = p;
        Connected[a][b] = 1;
    }
    void getTheRoad()
    {
        flag = true;
        minLen = 0;
        tempMinLen = 0;
        visited[Start] = 1;
        getTheRoad(Start);
        cout << minLen;
    }
};



int main()
{
    int n, m, start, end, a, b;
    long long p;
    cin >> n >> m >> start >> end;

    MyGraph GG(n,m,start,end);
    for(int i = 0;i < m;i++)
    {
        cin >> a >> b >> p;
        GG.Insert(a,b,p);
    }
    GG.getTheRoad();

    return 0;
}
