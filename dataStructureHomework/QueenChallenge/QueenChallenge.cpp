#include <iostream>
using namespace std;

const int H = 14;
int arr[H], counts = 0,N,NumberC = 0,answer[3][14],totalAn = 0;

bool isOk()
{
    for(int i = 2;i<=N;i++)
        for(int j = 1;j<i;j++)
        {
            if((j-i)==(arr[j]-arr[i]))
                return false;
            if((j-i)==-(arr[j]-arr[i]))
                return false;
        }
    return true;
}

bool conti(int x)
{
    for(int i = 1;i<x;i++)
    {
        if(arr[x]==arr[i])
            return false;
        if((x-i)==(arr[x]-arr[i]))
            return false;
        if((x-i)==-(arr[x]-arr[i]))
            return false;
    }
    return true;
}

void makeTheNumber(int x)
{
    if(counts==N)
    {
            if(isOk())
            {
                if(NumberC<3)
                {
                    for(int i =1;i<=N;i++)
                        answer[NumberC][i] = arr[i];
                    NumberC++;
                }
                totalAn++;
            }
        return ;
    }
    for(int i = 1;i<=N;i++)
    {
        arr[x]=i;
        if(!conti(x))
            continue;
        counts++;
        makeTheNumber(x+1);
        counts--;
    }
    return ;
}

int main()
{
    cin>>N;
    counts = 0;
    makeTheNumber(1);

    for(int i = 0;i<NumberC;i++)
    {
        for(int j =1; j <=N;j++)
            cout << answer[i][j] << ' ';
        cout <<endl;
    }

    cout << totalAn;
    return 0;
}
