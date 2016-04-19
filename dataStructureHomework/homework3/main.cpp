#include <iostream>
#include <cstring>
using namespace std;

struct Node
{
    int length;
    char data[2001];
    Node *next;
    Node():next(NULL){data[0] = 0;data[1] = '\0';}
};

class wordList
{
    friend void run(wordList &obj);
private:
    int lineNum;
    Node *head;
    Node *tail;
public:
    void insert(const char *n)
    {
        tail->next = new Node;
        tail = tail->next;
        tail->length = strlen(n);
        for(int i= 0 ;i<tail->length;i++)
            tail->data[i] = n[i];
        tail->data[tail->length] = '\0';
        lineNum ++;
    }
    wordList()
    {
        Node *head = new Node;
        tail = head;
        lineNum = 0;
        char temp[2001];
        cin.getline(temp,2001);
        while(strncmp(temp,"******",6))
        {
            insert(temp);
            cin.getline(temp,2001);
        }
    }
    ~wordList()
    {
        Node *p,*q;
        p = head->next;
        while(p)
        {
            cout<<p->data<<endl<<p->length<<endl;
            q = p->next;
            delete p;
            p = q;
        }
        delete head;
    }
    void printList(int m,int n);
    void insertList(int i,int j,char *p);
    void delList(int i,int j,int num);
    void quit();
};

void wordList::printList(int m,int n)
{
    if(m >lineNum||n >lineNum)
        cout<<"Error!"<<endl;
    else
    {
        int i = 0;
        Node *tmp = head;
        for(i = 0;i < m;i++)
        {
            tmp = tmp->next;
        }
        for(i = m;i<n+1;i++)
        {
            for(int k=0;k<tmp->length;k++)
                cout<<tmp->data[k];
            cout<<endl;
            tmp = tmp->next;
        }
    }
}

void wordList::insertList(int i,int j,char *p)
{
    if(i>lineNum)
    {
        cout<<"Error!"<<endl;
    }
    else
    {
        int m;
        Node *tmp = head;
        for(m = 0;m<i;m++)
        {
            tmp = tmp->next;
        }
        if(j>(tmp->length+1))
            cout<<"Error!"<<endl;
        else
        {
            char t[2001];
            int n;
            for(m =0;m < j;m++)
                t[m] = tmp->data[m];
            for(n = 0;n < strlen(p);n++)
                t[m+n] = p[n];
            for(;m<tmp->length;m++)
                t[n+m] = tmp->data[m];
            tmp->length += strlen(p);
            for(m = 0;m< tmp->length;m++)
                tmp->data[m] = t[m];
            tmp->data[m] = '\0';
        }
    }
}

void wordList::delList(int i,int j,int num)
{
    if(i>lineNum)
    {
        cout<<"Error!"<<endl;
    }
    else
    {
        int m;
        Node *tmp = head;
        for(m = 0;m<i;m++)
        {
            tmp = tmp->next;
        }
        if((j+num)>(tmp->length + 1))
            cout<<"Error!"<<endl;
        else
        {
            char t[2001];
            for(m = 0;m < j-1;m++)
                t[m] = tmp->data[m];
            m = m + num;
            for(m = j;m < tmp->length; m++)
                t[m-num] = tmp->data[m];
            tmp->length -= num;
            for(m = 0;m<tmp->length;m++)
                tmp->data[m] = t[m];
            tmp->data[m] = '\0';
        }
    }
}

void wordList::quit()
{
    Node *tmp = head;
    for(int i=0;i<lineNum;i++)
    {
        tmp = tmp->next;
        for(int k=0;k<tmp->length;k++)
            cout<<tmp->data[k];
        cout<<endl;
    }
}

int main()
{
    wordList list1;
//    list1.quit();
//    run(list1);
    return 0;
}

void run(wordList &obj)
{
    char type;
    int m,n,num;
    cin.get();
    type = cin.get();
    cin.get();
    cin.get();
    while(type != 'u')
    {
        if(type =='i')
        {
            cin>>m>>n;
            cin.get();
            obj.printList(m,n);
        }
        if(type == 'e')
        {
            cin>>m>>n>>num;
            cin.get();
            obj.delList(m,n,num);
        }
        if(type == 'n')
        {
            cin>>m>>n;
            char *p = new char[101];
            cin.get();
            cin.getline(p,101);
            obj.insertList(m,n,p);
            delete p;
        }
        cin.get();
        type = cin.get();
        cin.get();
        cin.get();
    }
    obj.quit();
}
