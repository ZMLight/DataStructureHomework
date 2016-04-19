#include <iostream>
using namespace std;

struct Node
{
    int data, sonNumber, location;
    Node *next;
    Node *father;

    Node(int loc = 0,int l = 0):data(l),sonNumber(-1),location(loc),next(NULL),father(NULL){}
};

bool findHary(Node *root,Node **Maps,long long &totalTime,int dest)
{
    if(root->location == dest)
        return true;
    if(root->next == NULL)
        return false;
    Node *temp, *p;
    temp = root;
    while(temp->next != NULL)
    {
        temp = temp->next;
        p = Maps[temp->sonNumber];
        totalTime += temp->data;
        if(findHary(p,Maps,totalTime,dest))
            return true;
        totalTime += temp->data;
    }

    return false;
}

int main()
{
    int n, dest, start, end, length;
    long long totalTime;
    Node *temp, *p, **Maps;

    cin >> n >> dest;
    Maps = new Node*[n];
    for(int i = 0; i < n; i++)
    {
        Maps[i] = new Node(i,0);
    }

    for(int i = 0; i < n-1; i++)
    {
        cin >> start >> end >> length;
        temp = new Node(0,length);
        p = Maps[start];
        while(p->next != NULL && p->next->data < length)
            p = p->next;
        temp->next = p->next;
        p->next = temp;
        temp->sonNumber = end;
        Maps[end]->father = Maps[start];
        Maps[end]->data = length;
    }

    totalTime = 0;
    findHary(Maps[0],Maps,totalTime,dest);

    cout << totalTime;

    return 0;
}
