#include <iostream>
using namespace std;


struct fraction
{
    int demo, num;
    fraction *next;
    fraction(int a = 1, int b = 0) :next(NULL){demo = a; num = b;}
};

bool isMinimum(fraction *obj)
{
    bool flag = true;
    for(int i = 2; i <= obj->num; ++i)
    {
        if(obj->demo % i == 0 && obj->num % i == 0)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool isBiggerThan(fraction *f1,fraction *f2)
{
    if((f1->num * f2->demo - f2->num * f1->demo) > 0)
        return true;
    else
        return false;
}

int main()
{
    int N;
    fraction *head, *pres, *frac;

    cin >> N;

    head = new fraction(1,0);
    if(N > 1)
    {
        for(int i = 2; i <= N; ++i)
        {
            pres = head;
            for(int j = 1; j < i;j ++)
            {
                frac = new fraction(i,j);
                if(isMinimum(frac))
                {
                    while(pres->next != NULL && isBiggerThan(frac,pres->next))
                    {
                            pres = pres->next;
                    }
                    frac->next = pres->next;
                    pres->next = frac;
                    pres = frac;
                }
            }
        }
    }

    pres = head;
    while(pres != NULL)
    {
        cout << pres->num << '/' << pres->demo << endl;
        pres = pres->next;
    }

    cout << 1 << '/' << 1 << endl;

    return 0;
}
