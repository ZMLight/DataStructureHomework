#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

template <class elemType>
class seqStack
{
private:
    elemType *elem;
    int Top;
    int maxSize;
    void doubleSpace();
public:
    seqStack(int initSize = 5000)
    {
        elem = new elemType[initSize];
        maxSize = initSize ;
        Top = -1;
    }
    ~seqStack(){ }

	void push(const elemType &x)
    {
        if (Top == maxSize - 1)
            doubleSpace();
        elem[++Top] = x;
    }
	elemType  pop()  { 	return elem[Top--];  }
    elemType  top() { return elem[Top];  }
	bool isEmpty() { 	return Top == -1;	}
};

template <class elemType>
void seqStack<elemType>::doubleSpace()
{	elemType *tmp = elem;
	elem = new elemType[2 * maxSize];
	for (int i = 0; i < maxSize; ++i)
		elem[i] = tmp[i];
	maxSize *= 2;
	delete [] tmp;
}



class calculation
{

}
