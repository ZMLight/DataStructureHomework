#include <iostream>
#include <cstring>
using namespace std;

template <class elemType>
class seqStack
{
private:
    elemType *elem;
    int top_p;
    int maxSize;
    void doubleSpace()
    {
        elemType *tmp = elem;

        elem = new elemType[2 * maxSize];
        for(int i = 0; i< maxSize; i++)
            elem[i] = tmp[i];
        maxSize *= 2;
        delete []tmp;
    }

public:
    seqStack(int initSize = 10)
    {
        elem = new elemType[initSize];
        maxSize = initSize;
        top_p = -1;
    }
    ~seqStack(){delete []elem;}

    bool isEmpty(){return top_p == -1;}
    void push(const elemType &x)
    {
        if(top_p == maxSize - 1)
            doubleSpace();
        elem[++top_p] = x;
    }

    elemType pop()
    {
        return elem[top_p--];
    }

    elemType top() const {return elem[top_p];}

};



class calc
{
    char *expression;
    enum token{OPAREN, ADD, SUB, CPAREN, VALUE, EOL};

    void BinaryOp(token op, seqStack <int> &dataStack);
    token getOp(int &value);

public:
    calc(char *s)
    {
        expression = new char[strlen(s)+1];
        strcpy(expression,s);
    }
    ~calc(){delete [] expression;}
    int result();
};


int calc::result()
{
    token lastOp, topOp;
    int result_value, CurrentValue;

    seqStack<token> opStack;
    seqStack<int> dataStack;

    char *str = expression;

    while(true)
    {
        lastOp = getOp(CurrentValue);
        if(lastOp == EOL) break;
        switch(lastOp)
        {
            case VALUE: dataStack.push(CurrentValue); break;
            case CPAREN:
                while(!opStack.isEmpty()&& (topOp = opStack.pop())!=OPAREN)
                    BinaryOp(topOp,dataStack);
                break;
            case OPAREN:
                opStack.push(OPAREN);
                break;
            case ADD:case SUB:
                while(!opStack.isEmpty() && opStack.top() != OPAREN)
                    BinaryOp(opStack.pop(),dataStack);
                opStack.push(lastOp);
        }
    }

    while(!opStack.isEmpty())
        BinaryOp(opStack.pop(), dataStack);

    result_value = dataStack.pop();

    expression = str;
    return result_value;
}

void calc::BinaryOp(token op, seqStack<int> &dataStack)
{
    int num1, num2;
    if(!dataStack.isEmpty())
        num2 = dataStack.pop();

    if(!dataStack.isEmpty())
        num1 = dataStack.pop();

    switch(op)
    {
        case ADD: dataStack.push(num1 + num2);break;
        case SUB: dataStack.push(num1 - num2);break;
    }
}

calc::token calc::getOp(int &value)
{
    while(*expression)
    {
        while(*expression && *expression == ' ')
            ++expression;
        if(*expression <= '9' && *expression>= '0')
        {
            value = 0;
            while(*expression >='0' && *expression <='9')
            {
                value = value * 10 + (*expression - '0');
                ++expression;
            }
            return VALUE;
        }

        switch(*expression)
        {
            case '(': ++expression;return OPAREN;
            case ')': ++expression;return CPAREN;
            case '+': ++expression;return ADD;
            case '-': ++expression;return SUB;
        }

    }

    return EOL;
}





int main()
{
    char *inputStr;
    inputStr = new char[100001];
    cin.getline(inputStr,100001,'\n');
//    cin >> inputStr;
    calc exp1(inputStr);
    cout << exp1.result();

    delete []inputStr;
    return 0;
}
