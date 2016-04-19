#include <iostream>
using namespace std;


void postOrder(int preOrd[], int midOrd[], int N)
{
    if(N == 0)
        return ;
    else
    {
        int *parr1,*parr2,*marr1,*marr2;
        int num1 = 0, num2 = 0;
        while(midOrd[num1] != preOrd[0])
        {
            num1 ++;
        }
        num2 = N - num1 - 1;
        if(num1 > 0)
        {
            parr1 = preOrd + 1;
            marr1 = midOrd;
        }
        else
            parr1 = marr1 = NULL;
        if(num2 > 0)
        {
            parr2 = preOrd + num1 + 1;
            marr2 = midOrd + num1 + 1;
        }
        else
            parr2 = marr2 = NULL;

        postOrder(parr1,marr1,num1);
        postOrder(parr2,marr2,num2);
        cout << preOrd[0] << ' ';
    }
}


int main()
{
    int elements,*preOrder,*midOrder;

    cin >> elements;

    preOrder = new int[elements];
    midOrder = new int[elements];
    for(int i = 0; i < elements; ++i)
    {
        cin >> preOrder[i];
    }
    for(int i = 0; i < elements; ++i)
    {
        cin >> midOrder[i];
    }

    postOrder(preOrder, midOrder, elements);

    return 0;
}
