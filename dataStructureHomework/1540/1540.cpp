#include <iostream>

using namespace std;

void selectSort(string *names,long long coun)
{
    string temp;
    long long loc;
    for(long long i = 0;i<coun-1;i++)
    {
        temp = names[i];
        loc = i;
        for(long long j = i; j <coun;j++)
        {
            if(names[j] < temp)
            {
                temp = names[j];
                loc = j;
            }
        }
        names[loc] = names[i];
        names[i] = temp;
    }
}

int calc(string name)
{
    int temp = 1;
    for(int i = 0; i < 3;i++)
    {
        if(name[i]>='a'&&name[i]<='z')
            temp *= (name[i]-'a'+1);
        else if(name[i]>='A'&&name[i]<='Z')
            temp *= (name[i]-'A'+1);
        else
            break;
    }

    return temp;
}

class HashTable
{
private:
    struct Node
    {
        string data;
        Node *next;
        long long num;
        Node(string d=""):data(d),next(NULL),num(1){}
    };
    Node **table;

public:
    HashTable()
    {
        table = new Node*[1000];
        for(int i = 0;i<1000;i++)
        {
            table[i] = new Node();
        }
    }
    int insertK(string d)
    {
        int temp = calc(d);
        temp %= 1000;
        Node *p;
        p = table[temp];
        while(p->data != d && p->next!=NULL)
            p = p->next;
        if(p->data==d)
        {
            p->num++;
            return 1;
        }
        else
            p->next = new Node(d);
        return 0;
    }
    long long getK(string d)
    {
        int temp = calc(d);
        temp %= 1000;
        Node *p;
        p = table[temp];
        while(p->data != d && p->next != NULL)
        {
            p = p->next;
        }
        if(p->data == d)
            return p->num;
        return 0;
    }
};


int main()
{
    string *names = new string[1000000];
    string tname;
    int answ;
    long long coun = 0,totalCoun = 0,a,b,c,e;
    char ttname[31];
    long long my[5];
    HashTable table;

    cin.getline(ttname,31,'\n');
    tname = ttname;
    while(tname!="")
    {
        totalCoun++;
        answ = table.insertK(tname);
        if(answ==0)
        {
            names[coun++] = tname;
        }

        cin.getline(ttname,31,'\n');
        tname = ttname;
    }

    selectSort(names,coun);


    for(long long i =0;i<coun;i++)
    {
        cout << names[i] << ' ';
        a = table.getK(names[i]) * 100;
        b = a/totalCoun;
        c = a%totalCoun;
        for(int j = 0;j<5;j++)
        {
            c*=10;
            my[j] = c/totalCoun;
            c = c%totalCoun;
        }
        if(my[4]>=5)
        {
            my[3] ++;
            e = 3;
            while(my[e]==10&&e>0)
            {
                my[e] = 0;
                my[e--]++;
            }
            if(my[0]==10)
            {
                b++;
                my[0]=0;
            }

        }
        cout << b<<'.'<<my[0]<<my[1]<<my[2]<<my[3];
        cout << endl;
    }

    return 0;
}
