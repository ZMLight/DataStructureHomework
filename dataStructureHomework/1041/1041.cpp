#include <iostream>
using namespace std;


template <class Type>
class priorityQueue
{
public:
    priorityQueue(int capacity = 100)
    {
        array = new Type[capacity];
        maxSize = capacity; currentSize = 0;
    }
    ~priorityQueue(){delete []array;}

    bool isEmpty()const{return currentSize == 0;}
    void enQueue(const Type &x)
    {
        if(currentSize == maxSize)
            doubleSpace();
        int hole = ++ currentSize;
        for(;hole>1 && x<array[hole/2];hole/=2)
            array[hole] = array[hole/2];
        array[hole] = x;
    }

    Type deQueue()
    {
        Type minItem;
        minItem = array[1];
        array[1] = array[currentSize --];
        percolateDown(1);

        return minItem;
    }

    Type getHead() const {return array[1];}

    void buildHeap()
    {
        for(int i = currentSize/2;i>0;i--)
            percolateDown(i);
    }

    void Decrease(int op1, int op2)
    {
        for(int i = 1;i <= currentSize;i++)
            if(array[i].getNum() == op1)
            {
                array[i].decreaValue(op2);
                break;
            }
        buildHeap();
    }

    void findMin(int obj)
    {
        cout << findMin(obj,1) << endl;
    }
private:
    int currentSize;
    Type *array;
    int maxSize;
    void doubleSpace()
    {
        Type *tmp = array;

        maxSize *= 2;
        array = new Type[maxSize];

        for(int i = 0; i <= currentSize;i++)
            array[i] = tmp[i];

        delete []tmp;
    }

    void percolateDown(int hole)
    {
        int child;
        Type tmp = array[hole];

        for(;hole*2 <= currentSize;hole = child)
        {
            child = hole*2;
            if(child != currentSize && array[child+1] < array[child])
                child++;
            if(array[child] < tmp) array[hole] = array[child];
            else break;
        }

        array[hole] = tmp;
    }

    int findMin(int obj, int loca)
    {
        int a = 2000000, b = 2000000;
        if(array[loca].getValue() > obj)
            return array[loca].getNum();
        else
        {
            if(loca * 2 <= currentSize)
                a = findMin(obj,loca*2);
            if(loca * 2 <= currentSize)
                b = findMin(obj,loca*2 +1);
            if(a>b)
                return b;
            else return a;
        }
    }
};


struct Node
{
    int num, height;
    Node(int n=0, int h=0):num(n),height(h){}

    bool operator<(const Node &a) const {return height < a.height;}
    int getNum(){return num;}
    int getValue(){return height;}
    void decreaValue(int op2){height -= op2;}
    void operator=(const Node &a){num = a.num;height = a.height;}
};

int main()
{
    int N, high, op1, op2, cnt, t1, t2;
    Node *tmp;
    char Op[15];
    priorityQueue<Node> MyQueue;

    cin >> N;
    tmp = new Node[N+1];
    for(int i = 1;i <= N; i++)
    {
        cin >> high;
        MyQueue.enQueue(Node(i,high));
    }

    while(cin >> Op)
    {
        if(Op[0] == 'd')
        {
            cin >> op1 >> op2;
            MyQueue.Decrease(op1,op2);
        }

        else if(Op[0] == 'f')
        {
            cin >> op1;
            MyQueue.findMin(op1);
        }
    }

    return 0;
}
