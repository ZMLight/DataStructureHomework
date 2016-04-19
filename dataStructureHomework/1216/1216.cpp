#include <iostream>
using namespace std;

class PriorityQueue
{
public:
    PriorityQueue(int capacity = 100)
    {
        array = new int[capacity];maxSize = capacity;currentSize = 0;
    }
    ~PriorityQueue(){delete [] array;}

    bool isEmpty() const {return currentSize == 0;}
    void enQueue(int x);
    int deQueue();
    int getHead() const {return array[1];}

    void find(int findNum);
    void decrease(int i, int v);
private:
    int currentSize;
    int *array;
    int maxSize;
    void doubleSpace();
    void buildHeap();
    void percolateDown(int hole);
};

void PriorityQueue::doubleSpace()
{
    maxSize *= 2;
    int *tmp;
    tmp = new int[maxSize];
    for(int i = 1; i <= currentSize; i++)
    {
        tmp[i] = array[i];
    }
    delete []array;
    array = tmp;
}

void PriorityQueue::enQueue(int x)
{
    if(currentSize == maxSize - 1)
        doubleSpace();

    int hole = ++ currentSize;
    for(;hole > 1&& x < array[hole/2];hole/=2)
        array[hole] = array[hole/2];
    array[hole] = x;
}

int PriorityQueue::deQueue()
{
    int minItem;
    minItem = array[1];
    array[1] = array[currentSize --];
    percolateDown(1);

    return minItem;
}

void PriorityQueue::percolateDown(int hole)
{
    int child;
    int tmp = array[hole];

    for(;hole*2 <= currentSize;hole = child)
    {
        child = hole * 2;
        if(child != currentSize && array[child + 1] < array[child])
            child ++;
        if(array[child] < tmp)
            array[hole] = array[child];
        else
            break;
    }
    array[hole] = tmp;
}

void PriorityQueue::buildHeap()
{
    for(int i = currentSize/2;i>0;i--)
        percolateDown(i);
}


void PriorityQueue::find(int findNum)
{
    int minLocation = 0, i;

    for(i = 1; i <= currentSize;i ++)
    {
        if((array[i] > findNum) &&((array[i] < array[minLocation])||(minLocation == 0)) )
            minLocation = i;
    }

    if(minLocation != 0)
        cout << minLocation << endl;
}

void PriorityQueue::decrease(int i, int v)
{
    int tmp;
    array[i] -= v;
    while(i/2 > 0 && array[i] < array[i/2])
    {
        tmp = array[i];
        array[i] = array[i/2];
        array[i/2] = tmp;
        i /= 2;
    }
}

int main()
{
    int operationNum = 0, insertNum, findNum, location, decreaseNum, i;
    char oper[10];

    PriorityQueue Q1;

    cin >> operationNum;
    for(i = 0; i < operationNum; i ++)
    {
        cin >> oper;
        if(oper[0] == 'i')
        {
            cin >> insertNum;
            Q1.enQueue(insertNum);
        }
        else if(oper[0] == 'd')
        {
            cin >> location >> decreaseNum;
            Q1.decrease(location, decreaseNum);
        }
        else if(oper[0] == 'f')
        {
            cin >> findNum;
            Q1.find(findNum);
        }
        oper[0] = '\0';
    }

    return 0;
}
