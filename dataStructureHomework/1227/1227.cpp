#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int d):data(d),next(NULL){}
};

int main()
{
    int N, tmp, min;
    Node *head, *location, *temp, *nhead;

    cin >> N;
    head = new Node(0);
    location = head;
    for(int i = 0; i < N;i++)
    {
        cin >> tmp;
        location->next = new Node(tmp);
        location = location->next;
    }

    for(int i = 0; i < N-1;i++)
    {
        nhead = head;
        for(int j = 0 ;j < i; j++)
        {
            nhead = nhead->next;
        }

        location = nhead->next;
        min = location->data;
        temp = location;
        for(int j = i;j < N-1; j++)
        {
            location = location->next;
            if(location->data < min)
            {
                min = location->data;
                temp = location;
            }
        }
        if(temp != nhead->next)
        {
            temp->data = nhead->next->data;
            nhead->next->data = min;
        }
    }

    location = head;
    for(int i = 0;i < N; i++)
    {
        location = location->next;
        cout << location->data << ' ';
    }

    return 0;
}
