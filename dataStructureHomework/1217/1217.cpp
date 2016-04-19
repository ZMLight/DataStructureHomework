#include <iostream>
using namespace std;

int main()
{
    int elemNum, searchNum, numToSearch, i, j;
    int *elem;
    bool flag;

    cin >> elemNum;
    elem = new int[elemNum + 1];
    for(i = 1; i <= elemNum; i++)
        cin >> elem[i];
    cin >> searchNum;
    for(i = 1; i <= searchNum; i++)
    {
        cin >> numToSearch;
        flag = false;
        for(j = 1; j <= elemNum; j++)
        {
            if(numToSearch == elem[j])
            {
                flag = true;
                break;
            }
        }
        if(flag)
            cout << 'Y' << endl;
        else
            cout << 'N' << endl;
    }

    return 0;
}
