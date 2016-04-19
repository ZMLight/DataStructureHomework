#include <iostream>
#include <cstring>
using namespace std;

class linkStack
{
private:
    struct Node
    {
        char *data;
        Node *next;
        Node():next(NULL){}
    };
    Node *head;
public:
    linkStack()
    {
        head = new Node;
        head->data = new char[1];
        head->data[0] = '\0';
    }

    ~linkStack(){clear();}

    void push(char *str)
    {
        Node *p = new Node;
        p->data = new char[strlen(str)+1];
        for(int i = 0;i < strlen(str);i++)
            p->data[i] = str[i];
        p->data[strlen(str)] = '\0';
        p->next = head->next;
        head->next = p;
    }

    int pop()
    {
        Node *p;
        if(head->next == NULL)
            return -1;
        else
        {
            p = head->next;
            head->next = p->next;
            delete p;
            return 1;
        }
    }

    bool isEmpty()
    {
        if(head->next == NULL)
            return true;
        else
            return false;
    }

    void clear()
    {
        Node *p, *q;
        p = head->next;
        while(p)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
};


int main()
{
    linkStack words1, words2, words3;
    bool flag = true;
    char *tmp = new char[201];

    while(cin>>tmp)
    {
        if(strcmp(tmp,"if") == 0)
        {
            words1.push(tmp);
        }
        if(strcmp(tmp,"then") == 0)
        {
            if(words1.isEmpty())
            {
                flag = false;
                break;
            }
            else
            {
                words1.pop();
                words2.push(tmp);
            }
        }
        if(strcmp(tmp,"else") == 0)
        {
            if(words2.isEmpty())
            {
                flag = false;
                break;
            }
            else
            {
                words2.pop();
            }
        }
        if(strcmp(tmp,"begin") == 0)
        {
            words3.push(tmp);
        }
        if(strcmp(tmp,"end") == 0)
        {
            if(words3.isEmpty())
            {
                flag = false;
                break;
            }
            else
                words3.pop();
        }
    }

    if(!words3.isEmpty())
        flag = false;
    if(!words1.isEmpty())
        flag = false;

    if(flag)
        cout<<"Match!"<<endl;
    else
        cout<<"Error!"<<endl;

    return 0;
}
