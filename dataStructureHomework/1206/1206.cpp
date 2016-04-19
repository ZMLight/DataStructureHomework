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
    Node *p;
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
        p = new Node;
        p->data = new char[strlen(str)+1];
        for(int i = 0;i < strlen(str);i++)
            p->data[i] = str[i];
        p->data[strlen(str)] = '\0';
        p->next = head->next;
        head->next = p;
    }
    int pop()
    {
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
    char top()
    {
        if(head->next!=NULL)
            return head->next->data[0];
        else
            return '\0';
    }
    void clear()
    {
        Node *q;
        p = head->next;
        while(p)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }


    void print()
    {
        p = head;
        while(p->next != NULL)
        {
            p = p->next;
            cout<<p->data<<endl;
        }
    }
};

int main()
{
    char x;
    int i = 0;
    char *str;
    bool flag = true;
    linkStack words1,words11,words2;

    str = new char[1001];
    str[0] = '\0';
    while(cin>>x)
    {
        if((x>='a'&&x<='z')||(x>='A'&&x<='Z'))
        {
            str[i] = x;
            i++;
        }
        if(!((x>='a'&&x<='z')||(x>='A'&&x<='Z'))&&str[0]!='\0')
        {
            str[i] = '\0';
            if(strcmp(str,"if")==0)
            {
                words1.push(str);
            }
            if(strcmp(str,"then")==0)
            {
                if(words1.top()!='i')
                {
                    flag = false;
                    break;
                }
                else
                    words11.push(str);
            }
            if(strcmp(str,"else")==0)
            {
                if(words11.top()!='t')
                {
                    flag = false;
                    break;
                }
                else
                {
                    words11.pop();
                    words1.pop();
                }
            }
            if(strcmp(str,"begin")==0)
            {
                    words2.push(str);
            }
            if(strcmp(str,"end")==0)
            {
                if(words2.pop()<0)
                {
                    flag = false;
                    break;
                }
            }
            str[0] = '\0';
            i = 0;
        }
    }


    if(words2.pop() > 0)
        flag = false;
    while(words1.pop() > 0)
    {
        if(words11.pop() < 0)
        {
            flag = false;
            break;
        }
    }

    if(!flag)
        cout<<"Error!"<<endl;
    else
        cout<<"Match!"<<endl;

    delete [] str;
    return 0;
}
