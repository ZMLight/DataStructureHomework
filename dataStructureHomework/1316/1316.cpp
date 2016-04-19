#include <iostream>
using namespace std;

struct MilkProcessTime
{
    int start, end;
    MilkProcessTime *next;
    MilkProcessTime(int s = 0, int e = 0, MilkProcessTime *t = NULL):start(s), end(e), next(t){}
};

int main()
{
    int N, startT, endT, oneInterval, noInterval;
    bool flag = false;
    MilkProcessTime *head, *pres, *temp;

    cin >> N;

    head = new MilkProcessTime(0,0,NULL);
    for(int i = 0; i < N; ++i)
    {
        cin >> startT >> endT;
        pres = head;
        while(pres->next != NULL && startT > pres->next->start)
            pres = pres->next;
        temp = new MilkProcessTime(startT,endT,pres->next);
        pres->next = temp;
    }

    while(!flag)
    {
        flag = true;
        pres = head->next;
        while(pres->next != NULL)
        {
            if(pres->end >= pres->next->start)
            {
                if(pres->end < pres->next->end)
                    pres->end = pres->next->end;

                flag = false;

                temp = pres->next;
                pres->next = temp->next;
                delete temp;
            }
            else
                pres = pres->next;
        }
    }

    oneInterval = 0;
    noInterval = 0;

    pres = head->next;
    while(pres->next != NULL)
    {
        if((pres->end - pres->start) > oneInterval)
            oneInterval = pres->end - pres->start;
        if((pres->next->start - pres->end) > noInterval)
            noInterval = pres->next->start - pres->end;
        pres = pres->next;
    }
    if((pres->end - pres->start) > oneInterval)
        oneInterval = pres->end - pres->start;

    cout << oneInterval << ' ' << noInterval;

    pres = head;
    while(pres != NULL)
    {
        temp = pres->next;
        delete pres;
        pres = temp;
    }

    return 0;
}
