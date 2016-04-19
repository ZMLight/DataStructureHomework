#include <iostream>
using namespace std;

class disJointSet
{
private:
    int Size;
    int *maps;

public:
    disJointSet(int s)
    {
        Size = s;
        maps = new int[Size];
        for(int i = 0; i < Size; i++)
        {
            maps[i] = -1;
        }

    }
    ~disJointSet(){delete [] maps;}
    void Union(int r1, int r2)
    {
        if(r1 == r2) return;
        maps[r1]=r2;
    }
    int Find(int x)
    {
        int start = x, tmp;
        while(maps[x] >= 0) x = maps[x];
        while(start != x){
            tmp = maps[start];
            maps[start] = x;
            start = tmp;
        }
        return x;
    }
};

class MyGraph
{
private:
    int Vers, Edges;
    struct edge
    {
        int start;
        int end;
        long long value;
        edge(int s, int e, long long v):start(s),end(e),value(v){}
    };
    edge **alEdges;
    int nowEdge;
    int divide(int low,int high)
    {
        long long tmp = alEdges[low]->value;
        int x = alEdges[low]->start,y = alEdges[low]->end;
        do
        {
            while(low<high && alEdges[high]->value >= tmp)  --high;
            if(low<high)
            {
                alEdges[low]->start = alEdges[high]->start;
                alEdges[low]->end = alEdges[high]->end;
                alEdges[low]->value = alEdges[high]->value;
                ++low;
            }
            while(low<high && alEdges[low]->value <= tmp) ++low;
            if(low<high)
            {
                alEdges[high]->start = alEdges[low]->start;
                alEdges[high]->end = alEdges[low]->end;
                alEdges[high]->value = alEdges[low]->value;
                --high;
            }
        }while(low!=high);

        alEdges[low]->value = tmp;
        alEdges[low]->start = x;
        alEdges[low]->end = y;

        return low;
    }

    void quickSort(int low,int high)
    {
        int mid;
        if(low>=high)   return;
        mid = divide(low,high);
        quickSort(low,mid-1);
        quickSort(mid+1,high);
    }
public:
    MyGraph(int v, int e)
    {
        Vers = v;
        Edges = e;
        alEdges = new edge*[Edges];
        nowEdge = 0;
    }
    void insert(int a, int b, long long p)
    {
        alEdges[nowEdge++] = new edge(a,b,p);
    }
    int getTheMin()
    {
        int alreadyE = 0, cnt = 0, s, e;
        long long answer = 0;
        disJointSet vSet(Vers+1);
        quickSort();
        while(alreadyE < Vers - 1)
        {
            s = alEdges[cnt]->start;
            e = alEdges[cnt]->end;
            if(vSet.Find(s)!=vSet.Find(e))
            {
                alreadyE++;
                answer += alEdges[cnt]->value;
                vSet.Union(s,e);
            }
            cnt++;
        }
        if(Vers <= 1)
            return 0;
        return answer;
    }
    void quickSort()
    {
        quickSort(0,Edges-1);
//        for(int i = 0; i < Edges; i++)
//            cout << alEdges[i]->value <<endl;
    }
};


int main()
{
    int n, m , a, b;
    long long p;
    cin >> n >> m;

    MyGraph g(n,m);
    for(int i = 0; i < m; i++)
    {
        cin >> a >> b;
        cin >> p;
        g.insert(a,b,p);
    }

    cout << g.getTheMin();

    return 0;
}
