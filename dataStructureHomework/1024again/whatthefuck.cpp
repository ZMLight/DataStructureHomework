#include <iostream>
#include <cstring>
using namespace std;

class wordList
{
public:
    struct Node
    {
        int length;
        char *data;
        Node *next;
        Node():next(NULL),data(NULL){}
    };

    int lineNum;
    Node *head,*tail;
    wordList(){head = new Node;tail = head;lineNum = 0;}
    ~wordList(){clear();}
    void clear()
    {
        tail = head->next;
        delete head;
        while(tail)
        {
            head = tail->next;
            delete [] tail->data;
            delete tail;
            tail = head;
        }
    }

    void insertLine(char *n)
    {
        tail->next = new Node;
        tail = tail->next;
        tail->length = strlen(n);
        tail->data = new char[tail->length+1];
        for(int i = 0;i<tail->length;i++)
            tail->data[i] = n[i];
        tail->data[tail->length] = '\0';
        ++lineNum;
    }

    void print(int num)
    {
        tail = head;
        for(int i=0;i<num;i++)
            tail = tail->next;
        cout<<tail->data<<endl;
    }

    void insertChar(int m,int n,char *ch)
    {
        int i;
        char *temp;
        tail = head;
        temp = new char[2001];
        for(i = 0;i < m;i++)
            tail = tail->next;
        if(n>tail->length+1||n<1)
            cout<<"Error!"<<endl;
        else
        {
            for(i = 0;i < n-1;i++)
                temp[i] = tail->data[i];
            i = 0;
            while(ch[i]!= '\0')
            {
                temp[i+n-1] = ch[i];
                i++;
            }
            for(i = n-1;i < tail->length+1;i++)
                temp[i+strlen(ch)] = tail->data[i];
            tail->length += strlen(ch);
            delete [] tail->data;
            tail->data = new char[tail->length+1];
            for(i = 0;i <= tail->length;i++)
                tail->data[i] = temp[i];
        }

        delete []temp;
    }

    void removeChar(int m,int n,int num)
    {
        int i =0;
        tail = head;
        for(i = 0;i < m;i++)
            tail = tail->next;
        if(n+num>tail->length+1||n<1||num<0)
            cout<<"Error!"<<endl;
        else
        {
            char *temp;
            for(i = 0;i < (tail->length - n - num + 1);i++)
                tail->data[n+i-1] = tail->data[n+i+num-1];
            tail->length -= num;
            tail->data[tail->length] = '\0';
            temp = new char[tail->length+1];
            for(i = 0;i <= tail->length;i++)
                temp[i] = tail->data[i];
            delete [] tail->data;
            tail->data = new char[tail->length+1];
            for(i = 0;i <= tail->length;i++)
                tail->data[i] = temp[i];
            delete [] temp;
        }
    }
};




int main()
{
    wordList list;

    char *temp;
    char da;
    int m,n,num;
    int i=0;

    temp = new char[2001];
    cin.getline(temp,2001);
    while(strcmp(temp,"******"))
    {
        list.insertLine(temp);
        cin.getline(temp,2001);
    }

    i = 0;
    da = cin.get();
    while(da !=' ' && da !='\n')
    {
        temp[i] = da;
        i++;
        da = cin.get();
    }
    temp[i] = '\0';

    while(temp[1]!= 'u')
    {
        if(temp[1] == 'i')
        {
            cin>>m>>n;
            while((da = cin.get())!='\n')
            {
            }
            if(m>list.lineNum||n>list.lineNum||m<1||n<1|| m>n)
                cout<<"Error!"<<endl;
            else
            {
                for(int k=m;k<=n;k++)
                    list.print(k);
            }
        }
        if(temp[1] == 'n')
        {
            i = 0;
            char *Temp;
            Temp = new char[100];
            cin>>m>>n;
            cin.get();
            while((da = cin.get())!= '\n')
            {
                Temp[i] = da;
                i++;
            }
            Temp[i] = '\0';

            if(m>list.lineNum || m<=0)
                cout<<"Error!"<<endl;
            else
                list.insertChar(m,n,Temp);
        }

        if(temp[1] == 'e')
        {
            cin>>m>>n>>num;
            while((da = cin.get())!='\n')
            {
            }
            if(m>list.lineNum || m<=0)
                cout<<"Error!"<<endl;
            else
                list.removeChar(m,n,num);
        }

        i = 0;
        da = cin.get();
        while(da !=' ' && da !='\n')
        {
            temp[i] = da;
            i++;
            da = cin.get();
        }
        temp[i] = '\0';
    }

    for(int k=0;k<list.lineNum;k++)
        list.print(k+1);
    delete []temp;

    return 0;
}
