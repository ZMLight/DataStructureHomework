#include <iostream>
using namespace std;

int walls[1001][1001];
int *visited, *Road;
int SetX, SetY;
int N, A, B, M;
int Pi, Qi, PRoot;
int counts = 0;
bool flag = true;

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
        if(r1 == r2 ) return;
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

disJointSet mySet(1000000);

void identifyWhichLine(int t)
{
    SetX = 1;
    while(t>SetX)
    {
        t-= SetX;
        SetX++;
    }
    SetY = t;
}

bool zsj()
{
    if(SetY == 1)
        return true;
    return false;
}

bool ysj()
{
    if(SetY == SetX)
        return true;
    return false;
}

bool xm()
{
    if(SetX == N)
        return true;
    return false;
}

void getTheRoad(int t)
{
    if(!flag)   return;
    if(t==B)
    {
        cout << A << ' ';
        for(int i = 0;i<counts;i++)
            cout << Road[i] <<' ';
        flag = false;
        return ;
    }
    for (int i = 0; i < M; i++)
        if (walls[t][i] && !visited[i])
        {
            visited[i]=1;
            Road[counts++]=i;
            getTheRoad(i);
            counts--;
            visited[i]=0;
        }
}

int main()
{
    for(int i = 0; i < 1001;i++)
        for(int j = 0;j< 1001;j++)
            walls[i][j] = 0;
    cin >> N >> A >> B;

    M = N*(N+1)/2 + 1;

    visited = new int[M];
    Road = new int[M];
    for(int i= 0 ; i < M;i++){visited[i] = 0;Road[i] = -1;}

    while(true)
    {
        if(mySet.Find(A)==mySet.Find(B) && mySet.Find(A)!= -1)
            break;
        cin >> Pi >> Qi;

        identifyWhichLine(Pi);
        PRoot = mySet.Find(Pi);
        switch(Qi)
        {
            case 0:
                if(!zsj())
                {
                    mySet.Union(PRoot,mySet.Find(Pi-SetX));
                    walls[Pi][Pi-SetX] = 1;
                    walls[Pi-SetX][Pi] = 1;
                }
                break;
            case 1:
                if(!ysj())
                {
                    mySet.Union(PRoot,mySet.Find(Pi-SetX+1));
                    walls[Pi][Pi-SetX+1] = 1;
                    walls[Pi-SetX+1][Pi] = 1;
                }
                break;
            case 2:
                if(!xm())
                {
                    mySet.Union(PRoot,mySet.Find(Pi+SetX));
                    walls[Pi][Pi+SetX] = 1;
                    walls[Pi+SetX][Pi] = 1;
                }
                break;
            case 3:
                if(!xm())
                {
                    mySet.Union(PRoot,mySet.Find(Pi+SetX+1));
                    walls[Pi][Pi+SetX+1] = 1;
                    walls[Pi+SetX+1][Pi] = 1;
                }
                break;
        }

    }

    getTheRoad(A);

    return 0;
}
