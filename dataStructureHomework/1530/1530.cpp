#include <iostream>
#include <cmath>
using namespace std;

int count = 0;

void printInord(char *S, int n, int k)
{
    if(k>=n)
        return;
    printInord(S,n,2*k + 1);
    cout << S[k];
    printInord(S,n,2*k + 2);
}

void printPoord(char *S, int n, int k)
{
    if(k>=n)
        return;
    printPoord(S,n,2*k + 1);
    printPoord(S,n,2*k + 2);
    cout << S[k];
}

void printPrord(char *S, int n, int k)
{
    if(k>=n)
        return;
    cout << S[k];
    printPrord(S,n,2*k + 1);
    printPrord(S,n,2*k + 2);
}

void getPreOrd(char *&SA, char *S, int n, int k)
{
    if(k>=n)
        return;
    SA[k] = S[count++];
    getPreOrd(SA,S,n,2*k+1);
    getPreOrd(SA,S,n,2*k+2);
}

void getPosOrd(char *&SA, char *S, int n, int k)
{
    if(k>=n)
        return;
    getPosOrd(SA,S,n,2*k+1);
    getPosOrd(SA,S,n,2*k+2);
    SA[k] = S[count++];
}

void getInOrd(char *&SA, char *S, int n, int k)
{
    if(k>=n)
        return;
    getInOrd(SA,S,n,2*k+1);
    SA[k] = S[count++];
    getInOrd(SA,S,n,2*k+2);
}

int main()
{
    int t, n;
    char *order, *coder, *S, *SA;
    order = new char[10];
    coder = new char[7];

    cin >> t;

    while(t>0)
    {
        cin >> n;
        cin >> order;
        cin >> coder;
        S = new char[n + 1];
        SA = new char[n + 1];
        cin >> S;
        if(coder[0] == 'E')
        {
            if(order[0] == 'I')
            {
                printInord(S,n,0);
            }
            else if(order[1] == 'R')
            {
                printPrord(S,n,0);
            }
            else if(order[1] == 'O')
            {
                printPoord(S,n,0);
            }
            cout << endl;
        }
        else if(coder[0] == 'D')
        {
            count = 0;
            if(order[1] == 'R')
            {
                getPreOrd(SA,S,n,0);
            }
            else if(order[1] == 'O')
            {
                getPosOrd(SA,S,n,0);
            }
            else if(order[0] == 'I')
            {
                getInOrd(SA,S,n,0);
            }
            for(int j = 0; j < n; j++)
                cout << SA[j];
            cout << endl;
        }
        delete []S;
        delete []SA;
        t--;
    }

    delete [] order;
    delete [] coder;

    return 0;
}
