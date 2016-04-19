#include <iostream>
using namespace std;

struct Node
{
    int sonNumber;
    int max1, max2;
    Node *next;
    Node(int i = -1):sonNumber(i),max1(0),max2(0),next(NULL){}
};

void makeMax(Node *&root, Node **&tree)
{
    if(root->next == NULL)
    {
        root->max1 = 0;
        root->max2 = 0;
    }
    else
    {
        Node *p, *q;
        p = root->next;
        while(p != NULL)
        {
            makeMax(tree[p->sonNumber],tree);
            p = p->next;
        }

        int Max1, Max2, tem;
        p = root->next;
        q = tree[p->sonNumber];
        Max1 = q->max1 + 1;
        Max2 = 0;

        if(p->next != NULL)
        {
            p = p->next;
            q = tree[p->sonNumber];
            tem = q->max1;
            if(tem > Max1 - 1)
            {
                Max2 = Max1;
                Max1 = tem + 1;
            }
            else
                Max2 = tem + 1;
        }

        while(p->next != NULL)
        {
            p = p->next;
            q = tree[p->sonNumber];
            tem = q->max1;
            if(tem > Max1-1)
            {
                Max2 = Max1;
                Max1 = tem + 1;
            }
            else if(tem > Max2 - 1)
            {
                Max2 = tem + 1;
            }
        }

        root->max1 = Max1;
        root->max2 = Max2;
    }
}

int main()
{
    Node **tree, *temp;
    int n, m, fatherLoc, longestTrac;
    cin >> n >> m;

    tree = new Node*[n+m];
    for(int i = 0; i < n + m; i++)
        tree[i] = new Node;

    for(int i = 1; i < n; i++)
    {
        cin >> fatherLoc;
        temp = new Node(i);
        temp->next = tree[fatherLoc-1]->next;
        tree[fatherLoc-1]->next = temp;
    }

    for(int i = n; i < n + m; i++)
    {
        cin >> fatherLoc;
        temp = new Node(i);
        temp->next = tree[fatherLoc-1]->next;
        tree[fatherLoc-1]->next = temp;
    }

    makeMax(tree[0],tree);
    longestTrac = 0;

    for(int i = 0; i < n + m; i++)
    {
        if((tree[i]->max1 + tree[i]->max2)>longestTrac)
            longestTrac = tree[i]->max1 + tree[i]->max2;
    }

    cout << longestTrac;

    return 0;
}
