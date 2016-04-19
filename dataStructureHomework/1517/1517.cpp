#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *next, *prev;
    Node() :value(0), next(NULL), prev(NULL) {}
};
class LongLongInt
{
    friend istream &operator>>(istream &,LongLongInt&);
    friend ostream &operator<<(ostream &,const LongLongInt &);
private:
    Node *head, *tail;
    int length;
public:
    LongLongInt()
    {
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
        length = 0;
    }
    ~LongLongInt()
    {
        Node *p,*q;
        p = head;
        while(p != NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }

    bool isBiggerThan(LongLongInt &other)
    {
        bool flag = false;
        Node *p, *q;
        if(length > other.length)
            return true;
        else if(length < other.length)
            return false;
        else
        {
            p = tail;
            q = other.tail;
            for(int i = 0; i < length; i++)
            {
                p = p->prev;q = q->prev;
                if(p->value < q->value)
                {
                    flag = false;
                    break;
                }
                else if(p->value > q->value)
                {
                    flag = true;
                    break;
                }
            }
        }
        return flag;
    }

    void sub(LongLongInt &other)
    {
        int len1 = length, len2 = other.length;
        int minus = 0, i;
        int *tmp;
        Node *n1, *n2;

        n1 = head;
        n2 = other.head;
        tmp = new int[len1 + 1];
        for(i = 0; i < len2; i++)
        {
            n1 = n1->next;n2 = n2->next;
            tmp[i] = n1->value - n2->value - minus;
            if(tmp[i] < 0){tmp[i]+=10;minus = 1;}
            else minus = 0;
        }

        while(i < len1)
        {
            n1 = n1->next;
            tmp[i] = n1->value - minus;
            if(tmp[i] < 0)  {tmp[i] += 10;minus = 1;}
            else minus = 0;
            ++i;
        }
        do
        {
            --i;
        }while(i>=0&&tmp[i] == 0);

        for(;i >=0; i--)
            cout << tmp[i];
    }

};


istream &operator>>(istream &in, LongLongInt &obj)
{
    char ch;
    Node *p;
    while((ch = in.get())!= '\n')
    {
        p = new Node;
        p->value = ch - '0';
        p->prev = obj.head;
        p->next = obj.head->next;
        obj.head->next->prev = p;
        obj.head->next = p;
        obj.length ++;
    }
    return in;
}

ostream &operator<<(ostream &out,const LongLongInt &obj)
{
    Node *p;
    p = obj.tail;
    while(p->prev != obj.head)
    {
        p = p->prev;
        out<<p->value;
    }

    return out;
}

int main()
{
    LongLongInt num1, num2;

    cin >> num1;cin >> num2;

    if(num1.isBiggerThan(num2))
    {
        num1.sub(num2);
    }
    else if(num2.isBiggerThan(num1))
    {
        cout<< '-';
        num2.sub(num1);
    }
    else
        cout << 0;

    return 0;
}
