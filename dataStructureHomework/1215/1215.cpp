#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    int degree;
    Node *child;
    Node *next;

    Node(int value):key(value),degree(0),child(NULL),next(NULL) {}
};

class BernoulliQueue
{
private:
    Node *Root;

public:
    BernoulliQueue():Root(NULL)
    {
    }
    ~BernoulliQueue()
    {
    }

    void insert(int key);
    void deleteMinimum();
    void printMinimum();
private:
    Node *combine(Node *h1, Node *h2);
    Node *merge(Node *h1, Node *h2);
    void link(Node *h1, Node *h2);
};


void BernoulliQueue::insert(int key)
{
    Node *newNode;

    newNode = new Node(key);

    Root = combine(Root,newNode);
}

Node *BernoulliQueue::merge(Node *h1, Node *h2)
{
    Node *root = NULL;
    Node **pos = &root;

    while(h1&&h2)
    {
        if(h1->degree < h2->degree)
        {
            *pos = h1;
            h1 = h1->next;
        }
        else
        {
            *pos = h2;
            h2 = h2->next;
        }
        pos = &(*pos)->next;
    }
    if(h1)
        *pos = h1;
    else
        *pos = h2;

    return root;
}

Node *BernoulliQueue::combine(Node *h1, Node *h2)
{
    Node *root;
    Node *prev_x, *x, *next_x;

    root = merge(h1,h2);
    if(root == NULL)
        return NULL;

    prev_x = NULL;
    x = root;
    next_x = x->next;

    while(next_x != NULL)
    {
        if((x->degree != next_x->degree)||((next_x->next != NULL)&&(next_x->degree == next_x->next->degree)))
        {
            prev_x = x;
            x = next_x;
        }
        else if(x->key <= next_x->key)
        {
            x->next = next_x->next;
            link(x,next_x);
        }
        else
        {
            if(prev_x == NULL)
                root = next_x;
            else
                prev_x->next = next_x;
            link(next_x,x);
            x = next_x;
        }
        next_x = next_x->next;
    }

    return root;
}

void BernoulliQueue::link(Node *h1, Node *h2)
{
    Node *temp;
    if(h1->child == NULL)
    {
        h1->child = h2;
        h1->degree ++;
    }
    else
    {
        temp = h1->child;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = h2;

        h1->degree ++;
    }
    h2->next = NULL;
}


void BernoulliQueue::printMinimum()
{
    Node *x;
    if(Root == NULL)
        return ;

    x = Root;

    int mini = x->key;

    while(x->next !=NULL)
    {
        x = x->next;
        if(x->key < mini)
        {
            mini = x->key;
        }
    }

    cout << mini << endl;
}

void BernoulliQueue::deleteMinimum()
{
    Node *x, *prev_x, *mini, *prev_mini;

    if(Root == NULL)
        return ;

    x = mini = Root;
    prev_x = prev_mini = NULL;

    while(x->next != NULL)
    {
        prev_x = x;
        x = x->next;
        if(x->key < mini->key)
        {
            prev_mini = prev_x;
            mini = x;
        }
    }

    if(prev_mini == NULL)
    {
        Root = Root->next;
        Root = combine(Root, mini->child);
    }
    else
    {
        prev_mini->next = mini->next;
        Root = combine(Root, mini->child);
    }

    delete mini;
}


int main()
{
    int operationNum = 0, insertNum, i;
    char oper[10];

    BernoulliQueue Q1;

    cin >> operationNum;
    for(i = 0; i < operationNum; i ++)
    {
        cin >> oper;
        if(oper[0] == 'i')
        {
            cin >> insertNum;
            Q1.insert(insertNum);
        }
        else if(oper[0] == 'd')
        {
            Q1.deleteMinimum();
        }
        else if(oper[0] == 'm')
        {
            Q1.printMinimum();
        }
        oper[0] = '\0';
    }

    return 0;
}
