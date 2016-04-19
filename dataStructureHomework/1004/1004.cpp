#include <iostream>
using namespace std;

int main()
{
    int M, T, U, F, D, len, counts;
    char *Road;
    Road = new char[T];
    cin >> M>>T>>U>>F>>D;

    for(int i = 0;i<T;i++)
        cin >> Road[i];
    counts = 0;
    len = 0;
    while(counts < T&&len<=M)
    {
        if(Road[counts]=='u'||Road[counts]=='d')
            len+=U+D;
        else
            len+=F+F;
        counts++;
    }
    if(len>M)
    {
        counts--;
    }

    cout << counts;

    return 0;
}
