#include <iostream>
using namespace std;

class Stack
{
private:
    int *array, maxSize, currentSize;
    void doubleSpace()
    {
        int *temp;
        maxSize *= 2;
        temp = new int[maxSize];
        for(int i = 1; i <= currentSize;i++)
            temp[i] = array[i];
        array = temp;
        delete []temp;
    }
public:
    Stack(int capacity = 100){array = new int[capacity];currentSize = 0; maxSize = capacity;}
    ~Stack(){delete []array;}

    bool isEmpty(){return currentSize == 0;}
    bool onlyOneEle(){return currentSize == 1;}
    bool moreThanTwoNum()
    {
        if(array[currentSize] != -1 && array[currentSize - 1] != -1)
            return true;
        else
            return false;
    }
    void push(int x)
    {
        if(currentSize == maxSize -1)
            doubleSpace();
        array[++currentSize] = x;
    }

    int pop()
    {
        int tmp;
        tmp = array[currentSize--];
        return tmp;
    }

    int getHead()
    {
        if(!isEmpty())
            return array[currentSize];
    }
};



int main()
{
    char *inputStr;
    int insertNum = 0,LOperNum, ROperNum, oper, i = 0;
    bool flag = true;
    Stack operStack, numStack;


    inputStr = new char[50000];
    cin.getline(inputStr,50001,'\n');

    while(inputStr[i] != '\0')
    {
        flag = true;
        if(inputStr[i] == '+')
        {
            operStack.push(1);
        }
        else if(inputStr[i] == '-')
        {
            operStack.push(-1);
        }
        else if(inputStr[i] == '(')
        {
            numStack.push(-1);
        }
        else if(inputStr[i] >= '0' && inputStr[i] <= '9')
        {
            flag = false;
            while(inputStr[i] >='0' && inputStr[i] <='9')
            {
                insertNum = insertNum*10 + (inputStr[i] - '0');
                i ++;
            }
            numStack.push(insertNum);

            while(operStack.getHead() == -1 && numStack.moreThanTwoNum() == true)
            {
                operStack.pop();
                ROperNum = numStack.pop();
                LOperNum = numStack.pop();
                ROperNum = LOperNum - ROperNum;
                numStack.push(ROperNum);
            }

            insertNum = 0;
        }
        else if(inputStr[i] == ')')
        {
            if(numStack.getHead() != -1)
            {
                while(true)
                {
                    ROperNum = numStack.pop();
                    if(numStack.getHead() != -1)
                    {
                        LOperNum = numStack.pop();
                        oper = operStack.pop();
                        if(oper == 1)
                            ROperNum += LOperNum;
                        else if(oper == -1)
                            ROperNum = LOperNum - ROperNum;
                        numStack.push(ROperNum);

                        while(operStack.getHead() == -1 && numStack.moreThanTwoNum() == true)
                        {
                            operStack.pop();
                            ROperNum = numStack.pop();
                            LOperNum = numStack.pop();
                            ROperNum = LOperNum - ROperNum;
                            numStack.push(ROperNum);
                        }
                    }
                    else
                    {
                        numStack.pop();
                        numStack.push(ROperNum);

                        while(operStack.getHead() == -1 && numStack.moreThanTwoNum() == true)
                        {
                            operStack.pop();
                            ROperNum = numStack.pop();
                            LOperNum = numStack.pop();
                            ROperNum = LOperNum - ROperNum;
                            numStack.push(ROperNum);
                        }
                        break;
                    }
                }
            }
            else
            {
                numStack.pop();
            }
        }

        if(flag)
            i++;
    }

    while(!operStack.isEmpty())
    {
        ROperNum = numStack.pop();
        LOperNum = numStack.pop();
        if(operStack.pop() == 1)
            ROperNum += LOperNum;
        else
            ROperNum = LOperNum - ROperNum;

        numStack.push(ROperNum);
    }

    cout << numStack.getHead();

    return 0;
}
