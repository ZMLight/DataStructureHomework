#include <iostream>
using namespace std;

int main()
{
    int A, B, counts = 0;
    bool flag = false;


    cin >> A >> B;
    for(int i = A; i <=B; i++)
    {
        flag = true;
        for(int j = 2; j < i; j++)
        {
            if(i%j == 0)
            {
                flag = false;
                break;
            }
        }
        if(flag)
            counts ++;
    }

    if(A==1)
        counts --;

    cout << counts;

    return 0;
}
