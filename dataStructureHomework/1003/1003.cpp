#include <iostream>
using namespace std;

void multi(int **map, int N)
{
    bool **ifNeedMulti;
    ifNeedMulti = new bool*[N];
    for(int i = 0;i<N;i++)
    {
        ifNeedMulti[i] = new bool[N];
        for(int j = 0; j <N;j++)
            ifNeedMulti[i][j] = false;
    }
    for(int i = 0;i<N;i++)
    {
        for(int j = 0;j<N;j++)
        {
            if(map[i][j] == 1)
                ifNeedMulti[i][j] = true;
        }
    }
    for(int i = 0;i<N;i++)
    {
        for(int j = 0; j<N;j++)
        {
            if(ifNeedMulti[i][j])
            {
                if(i!=0&&map[i-1][j]!=2)
                    map[i-1][j] = 1;
                if(i!=N-1&&map[i+1][j]!=2)
                    map[i+1][j] = 1;
                if(j!=0&&map[i][j-1]!=2)
                    map[i][j-1] = 1;
                if(j!=N-1&&map[i][j+1]!=2)
                    map[i][j+1] = 1;
            }
        }
    }
}


int main()
{
    int N,**map,counts;
    bool *Ok, end;
    cin >> N;
    map = new int*[N];
    Ok = new bool[N];
    end = false;
    for(int i = 0;i<N;i++)
        Ok[i] = false;
    for(int i = 0;i<N;i++)
    {
        map[i] = new int[N];
        for(int j = 0;j<N;j++)
            cin >> map[i][j];
    }

    end = true;
    for(int i = 0;i<N;i++)
    {
        Ok[i] = true;
        for(int j = 0;j<N;j++)
        {
            if(map[i][j]==0)
            {
                Ok[i] = false;
                end = false;
                break;
            }
        }
    }

    counts = 0;
    while(!end)
    {
        counts++;
        multi(map,N);

        end = true;
        for(int i = 0;i<N;i++)
        {
            Ok[i] = true;
            for(int j = 0;j<N;j++)
            {
                if(map[i][j]==0)
                {
                    Ok[i] = false;
                    end = false;
                    break;
                }
            }
        }
    }

    cout << counts;
    return 0;
}
