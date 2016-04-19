#include <iostream>
using namespace std;


class openHashTable
{
private:
    struct Node
    {
        int data;
        int keyTimes;
        Node *next;

        Node(int v){data = v;next = NULL;keyTimes = 1;}
        Node(){next=NULL;}
    };

    Node **array;
    int size;

public:
    openHashTable(int length);
    ~openHashTable();
    int find(int x);
    void insert(int x);
};


openHashTable::openHashTable(int length)
{
    size = length;
    array = new Node *[size];
    for(int i = 0;i < size;i++)
        array[i] = new Node;
}

openHashTable::~openHashTable()
{
    Node *p, *q;
    for(int i = 0;i < size;i++)
    {
        p = array[i];
        do
        {
            q = p->next;delete p;p = q;
        }
        while(p!=NULL);
    }

    delete []array;
}

void openHashTable::insert(int x)
{
    int location = (x + 2000000) % size;
    bool flag = false;
    Node *p = array[location];
    while(p->next != NULL)
    {
        p = p->next;
        if(p->data == x)
        {
            p->keyTimes += 1;
            flag = true;
            break;
        }
    }
    if(!flag)
    {
        p->next = new Node(x);
    }
}

int openHashTable::find(int x)
{
    int location = (x + 2000000) % size;
    Node *p = array[location];
    while(p->next != NULL)
    {
        p = p->next;
        if(p->data == x)
        {
            return p->keyTimes;
        }
    }

    return 0;
}


int main()
{
    int N, value, times = 0;
    int *A, *B, *C, *D;

    cin >> N;
    openHashTable T1((N*N)/4);

    A = new int[N];
    B = new int[N];
    C = new int[N];
    D = new int[N];
    for(int i = 0; i < N; i++)
    {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }


    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            value = A[i] + B[j];
            T1.insert(value);
            //cout << value << endl;
        }
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            value = C[i] + D[j];
            times += T1.find(-value);
            //cout << times << ' ' << value << endl;
        }
    }

    cout << times;

    return 0;
}
