#include <iostream>
using namespace std;

bool isInAr(int other[],int size,int num)
{
    for(int i = 0; i < size; i ++)
    {
        if(other[i] == num)
        {
            return true;break;
        }
    }
    return false;
}

class MySet
{
private:
    int *array, maxSize, currentSize;
    void doubleSpace();
public:
    MySet(int capacity = 100)
    {
        maxSize = capacity;
        array = new int[capacity];
        currentSize = 0;
    }
    ~MySet() {delete []array;}
    int find(int x);
    void sortTheSet();
    void add(int other[],int size);
    void sub(int other[],int size);
    void multi(int other[],int size);
    void print()
    {
        for(int i = 1; i <= currentSize; i++)
        {
            cout << array[i] <<' ';
        }
        cout << endl;
    }
};

void MySet::doubleSpace()
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

void MySet::add(int other[],int size)
{
    int i;
    for(i = 0; i < size; i++)
    {
        if(find(other[i]) == 0)
        {
            if(maxSize == currentSize + 1)
                doubleSpace();
            array[++currentSize] = other[i];
        }
    }

    sortTheSet();
    print();
}

void MySet::sub(int other[], int size)
{
    int i, *tmp, j = 0;
    tmp = new int[maxSize];

    for(i = 1; i <= currentSize; i ++)
    {
        if(!isInAr(other,size,array[i]))
        {
            tmp[++j] = array[i];
        }
    }

    array = tmp;
    currentSize = j;

    sortTheSet();
    print();
}

void MySet::multi(int other[], int size)
{
    int i, j = 0 , *tmp;
    tmp = new int[maxSize];

    for(i = 1; i <= currentSize; i ++)
    {
        if(isInAr(other,size,array[i]))
            tmp[++j] = array[i];
    }

    array = tmp;
    currentSize = j;

    sortTheSet();
    print();
}

int MySet::find(int x)
{
    for(int i = 1; i <= currentSize; i++)
    {
        if(x == array[i])
            return i;
    }
    return 0;
}

void MySet::sortTheSet()
{
    int i, j, temp;
    for(i = 1; i < currentSize; i++)
    {
        for(j = currentSize; j >i; j--)
        {
            if(array[j] < array[j - 1])
            {
                temp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main()
{
    int *ArrToOp, ArrNum, OperationNum;
    char op;
    MySet S1;

    cin >> OperationNum;
    for(int i = 0; i < OperationNum; i++)
    {
        cin >> op >> ArrNum;
        ArrToOp = new int[ArrNum];
        for(int j = 0; j < ArrNum; j++)
            cin >> ArrToOp[j];
        if(op == '+')
        {
            S1.add(ArrToOp, ArrNum);
        }
        else if(op == '-')
        {
            S1.sub(ArrToOp, ArrNum);
        }
        else if(op == '*')
        {
            S1.multi(ArrToOp, ArrNum);
        }
        delete []ArrToOp;
    }

    return 0;
}
