#include <iostream>
#include <iomanip>
using namespace std;

class linkQueue
{
private:
    struct Node
    {
        int data;
        Node *next;
        Node(int x = 1000000, Node *N = NULL)
        {
            data = x;next = N;
        }
        Node():next(NULL){}
        ~Node(){}
    };
    Node *head, *tail;
public:
    linkQueue()
    {
        head = tail = NULL;
    }
    ~linkQueue()
    {
        Node *tmp;
        while(head != NULL)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    bool isEmpty()
    {
        return head == NULL;
    }

    void enQueue(int x = -1)
    {
        if(tail == NULL)
            head = tail = new Node(x);
        else
        {
            tail->next = new Node(x);
            tail = tail->next;
        }
    }

    int deQueue()
    {
        Node *tmp = head;
        int value = head->data;
        head = head->next;
        if(head == NULL)
            tail = NULL;
        delete tmp;
        return value;
    }
    int getHead()
    {
        if(head == NULL)
            return 1000000;
        else
            return head->data;
    }
};


int main()
{
    int BusWaitTime = 0, TruckWaitTime = 0, TotalCarsNum, BusNum = 0, TruckNum = 0, Type, ArrivedTime, FerryTime;
    int i = 0, CarsToGo, BusToGo;
    linkQueue Bus, Truck;


    cin >> TotalCarsNum;
    for(i = 0;i < TotalCarsNum;i++)
    {
        cin >> Type >> ArrivedTime;
        if(Type == 0)
        {
            Bus.enQueue(ArrivedTime);
            ++ BusNum;
        }
        if(Type == 1)
        {
            Truck.enQueue(ArrivedTime);
            ++ TruckNum;
        }
    }

    FerryTime = 0;
    while(!Bus.isEmpty() || !Truck.isEmpty())
    {
        CarsToGo = BusToGo = 0;
        while(CarsToGo < 10 && (Bus.getHead() <= FerryTime || Truck.getHead() <= FerryTime))
        {
            while(CarsToGo < 10 && BusToGo < 4 && Bus.getHead() <= FerryTime)
            {
                BusWaitTime += (FerryTime - Bus.deQueue());
                ++ BusToGo;
                ++ CarsToGo;
            }
            if(BusToGo < 4)
            {
                while(CarsToGo < 10 && Truck.getHead() <= FerryTime)
                {
                    TruckWaitTime += (FerryTime - Truck.deQueue());
                    ++ CarsToGo;
                }
            }
            if(BusToGo == 4)
            {
                if(Truck.getHead() <= FerryTime)
                {
                    TruckWaitTime += (FerryTime - Truck.deQueue());
                    ++ CarsToGo;
                }
                BusToGo = 0;
            }
        }
        FerryTime += 10;
    }
//    cout << BusWaitTime <<  ' ' << TruckWaitTime<<endl;
//    cout << BusNum << ' ' << TruckNum<<endl;

    cout << setiosflags(ios::fixed) << setiosflags(ios::right) << setprecision(3)<< (BusWaitTime/double(BusNum));
    cout << ' ' << setiosflags(ios::fixed) << setiosflags(ios::right) << setprecision(3)<<(TruckWaitTime/double(TruckNum));

    return 0;
}
