#include <iostream>
using namespace std;

int SetSet[101][200];
int Size[101] = {0};
int T[200] , cnt;
int N, tmp, op1, op2;
char op;

bool isInSet(int x, int obj)
{
    for(int i = 0; i < Size[i] ;i++)
    {
        if(SetSet[x][i] == obj)
            return true;
    }
    return false;
}

int main()
{
    cin >> N;
    for(int i = 1; i <= N ;i++)
    {
        while(true)
        {
            cin >> tmp;
            if(!isInSet(i,tmp))
                SetSet[i][Size[i]++] = tmp;
            if(cin.get() == '\n')
                break;
        }
    }

    while(cin >> op)
    {
        if(op=='+')
        {
            cin >> op1 >> op2;
            for(int i = 0;i < Size[op2];i++)
            {
                if(!isInSet(op1,SetSet[op2][i]))
                    SetSet[op1][Size[op1]++] = SetSet[op2][i];
            }
        }
        else if(op=='-')
        {
            cnt = 0;
            cin >> op1 >> op2;
            for(int i = 0;i<Size[op1];i++)
            {
                if(!isInSet(op2,SetSet[op1][i]))
                    T[cnt++] = SetSet[op1][i];
            }
            Size[op1] = cnt;
            for(int i = 0;i<cnt;i++)
            {
                SetSet[op1][i] = T[i];
            }
        }
        else if(op=='*')
        {
            cnt = 0;
            cin >> op1 >> op2;
            for(int i = 0;i<Size[op1];i++)
            {
                if(isInSet(op2,SetSet[op1][i]))
                    T[cnt++] = SetSet[op1][i];
            }
            Size[op1] = cnt;
            for(int i = 0;i<cnt;i++)
            {
                SetSet[op1][i] = T[i];
            }
        }
    }

    for(int i = 0;i<N;i++)
    {
        if(Size[i] == 0)
            cout << endl;
        else
        {
            for(int j = 0; j < Size[i];j++)
                cout << SetSet[i][j] << ' ';
            cout << endl;
        }
    }

    return 0;
}
