#include <iostream>
using namespace std;

void print(long long i, long long *Tree, long long n)
{
    long long arr[n], k = n-1;
    while(k>=0)
    {
        arr[k] = Tree[i];
        i = (i-1) / 4;
        k -= 1;
    }
    for(k = 0; k < n; k++)
        cout << arr[k];
}

bool isInterest(long long i, long long *Tree, long long n)
{
    long long arr[n], k = n-1;
    while(k>=0)
    {
        arr[k] = Tree[i];
        i = (i-1) / 4;
        k -= 1;
    }

    bool flag0 = false,flag1 = false,flag2 = false,flag3 = false;
    bool flag01 = true, flag23 = true;

    k = 0;
    while(k != n)
    {
        if(arr[k] == 0)
        {
            flag0 = true;
            if(flag1)
            {
                flag01 = false;
                break;
            }
        }
        else if(arr[k] == 1)
        {
            flag1 = true;
        }
        else if(arr[k] == 2)
        {
            flag2 = true;
            if(flag3)
            {
                flag23 = false;
                break;
            }
        }
        else if(arr[k] == 3)
        {
            flag3 = true;
        }

        k ++;
    }

    if(flag0&&flag1&&flag2&&flag3&&flag01&&flag23)
        return true;
    else
        return false;
}

int main()
{
    long long *interestTree, n;
    long long N = 1, count = 0, I, J, k, temp;

    cin >> n >> k;

    for(int i = 0; i < n; i++)
        N *= 4;
    N = (N - 1) / 3;
    interestTree = new long long[N];
    N = (N - 1) / 4;
    interestTree[0] = 2;
    for(long long i = 0 ; i < N; i++)
    {
        for(long long j = 1; j <= 4; j++)
        {
            temp = i * 4 + j;
            interestTree[temp] = j-1;
        }
    }

    I = J = 1;
    for(int i = 0 ; i < n-1; i++)
        I *= 4;
    I = (I - 1) / 3;
    for(int i = 0 ; i < n-1; i++)
        J *= 4;
    J += I;
    for(long long i = I + 1; i < J; i = i + 2)
    {
        if(isInterest(i,interestTree,n))
            count ++;

        if(count == k)
        {
            print(i,interestTree,n);
            break;
        }
    }

    return 0;
}
