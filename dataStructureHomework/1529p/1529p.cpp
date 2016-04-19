#include <iostream>
using namespace std;

const int N = 25;
int number[N], n, k, count = 0;
int use[4] = {0};


bool isOk()
{
    if(!number[0]) return false;
    for(int i = 0; i < 4; i++)
        if(!use[i]) return false;
    return true;
}

void getTheNumber(int x)
{
    if(x==n)
    {
        if(isOk())
        {
            count ++;
        }
        return;
    }

    for(int i = 0; i < 4; i++)
    {
        if(count == k)   return ;
        if(i == 0 && use[1]) continue ;
        if(i == 2 && use[3]) continue ;
        number[x] = i;
        use[i]++;
        getTheNumber(x+1);
        use[i]--;
    }
}

int main()
{
    cin >> n >> k;
    getTheNumber(0);
    for(int i = 0; i < n; i++)
        cout << number[i];
    cout << endl;
    return 0;
}
