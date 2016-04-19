#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


bool flag=true,sign=true;
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
	char *expression;
    bool flag2;
	enum token {OPAREN,ADD,SUB,MULTI,DIV,EXP,CPAREN,VALUE,EOL};
    void BinaryOp(token op,seqStack <long long> &dataStack );
	token getOp(long long &value);
public:
	calculation(char *s)
    {
        expression = new char[strlen(s) + 5];
        for(int i=0;i<strlen(s) + 5;i++)
            expression[i]='\0';
        strcpy(expression,s); flag2=true;}
	~calculation( ) { }
	void result( );
};

void calculation::result()
{
    token lastOp, topOp;
    long long result_value, CurrentValue;
    seqStack<token> opStack;
    seqStack<long long> dataStack;
    char *str = expression;
    while (true)
    {
        lastOp = getOp(CurrentValue);
        if (lastOp == EOL) break;
        switch (lastOp)
        {
            case VALUE:
                dataStack.push(CurrentValue) ; break;
            case CPAREN:
                while( !opStack.isEmpty() && (topOp = opStack.pop())  != OPAREN )
                        BinaryOp(topOp, dataStack);
                if ( topOp  != OPAREN and flag)  {cout << "Error" ;flag=false;}
                break;
            case OPAREN:
                opStack.push(OPAREN); break;
            case EXP:
                opStack.push(EXP); break;
            case MULTI:case DIV:
                while ( !opStack.isEmpty() && opStack.top() >= MULTI)
                    BinaryOp(opStack.pop(), dataStack);
                opStack.push(lastOp);
                break;
            case ADD:case SUB:
                while ( !opStack.isEmpty() && opStack.top() != OPAREN )
                    BinaryOp(opStack.pop(), dataStack );
                opStack.push(lastOp);
        }
        }
        while (!opStack.isEmpty())
            BinaryOp(opStack.pop(),dataStack);
        if (dataStack.isEmpty() and flag)
        { cout  << "Error";  flag=false;  }
        result_value = dataStack.pop();
        if (!dataStack.isEmpty() and flag and !sign and flag2)
        { cout  << "Error";  flag=false; }
        expression = str;
        if(flag)cout<< result_value;
}

void calculation::BinaryOp(token op,seqStack<long long> &dataStack)
{
    long long  num1, num2;
    if ( dataStack.isEmpty() and flag)
    { cout  << "Error";  flag=false; }
    else num2 = dataStack.pop();
    if (!dataStack.isEmpty())
        num1 = dataStack.pop();
    switch(op) {
      case ADD: dataStack.push(num1 + num2);
                          break;
      case SUB: dataStack.push(num1 - num2);
                         break;
	  case MULTI: dataStack.push(num1 * num2);
                         break;
	  case DIV: {if(num2!=0)dataStack.push(num1 / num2);else if(flag){cout<<"Error";flag=false;}}
                         break;
	  case EXP: {if(num1!=0)dataStack.push(pow(num1,num2));else dataStack.push(0);}
     }
}

calculation::token calculation::getOp(long long &value)
{
    while (*expression)
    {
        while( *expression  && *expression == ' ' )
            {++expression;}
        if(*expression == '-' and flag2)
        {
            flag2=false;
            value=0;
            return VALUE;
        }
        if ( *expression <= '9' && *expression >= '0')
        {
            value = 0;
            while (*expression >='0' && *expression <='9')
            {
                value = value * 10 + *expression - '0';
                    ++expression;
                while( *expression  && *expression == ' ' )
                    ++expression;
            }
	        sign=false;
            flag2=false;
	        return VALUE;
        }

        if(*expression == '-' and sign)
        {
            ++ expression;
            while(*expression&&*expression == ' ')
                    ++expression;
            if(*expression <= '9' && *expression >= '0')
            {
                value = 0;
                while (*expression >='0' && *expression <='9')
                {
                    value = value * 10 + *expression - '0';
                    ++expression;
                }
                value*=-1;
                sign=false;
                flag2=false;
                return VALUE;
	        }
	        else{sign=true;flag2=false;return SUB;}
        }
        else
        {
            switch (*expression)
            {
            case '(': {++expression ;sign=true;flag2=false;} return OPAREN;
            case ')': {++expression ;sign=true;flag2=false;} return CPAREN;
            case '+': {++expression ;sign=true;flag2=false;} return ADD;
            case '-': {++expression ;sign=true;flag2=false;} return SUB;
            case '*': {++expression ;sign=true;flag2=false;} return MULTI;
            case '/': {++expression ;sign=true;flag2=false;} return DIV;
            case '^': {++expression ;sign=true;flag2=false;} return EXP;
            }
        }

    }
    return EOL;
 }


 int main()
{
    char s[5001];
    cin.getline(s,5001);
    calculation value(s);
    value.result();

    return 0;
}
