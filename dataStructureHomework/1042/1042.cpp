#include <iostream>
using namespace std;

class linkQueue
{
private:
    struct node
    {
        int data;
        node *next;
        node(int x, node *n = NULL):data(x), next(n){}
        node():next(NULL){}
    };

    node *front, *rear;
public:
    linkQueue()
    {
        front = rear = NULL;
    }
    bool isEmpty()
    {
        return front == NULL;
    }
    void enQueue(int x)
    {
        if(rear == NULL)
            front = rear = new node(x);
        else
        {
            rear->next = new node(x);
            rear = rear->next;
        }
    }
    int deQueue()
    {
        node *tmp = front;
        int value = front->data;
        front = front->next;
        if(front == NULL)   rear = NULL;
        delete tmp;
        return value;
    }
    int getHead()
    {
        return front->data;
    }
};


class Tree
{
private:
    struct Node
    {
        int value;
        int leftSon, rightBrother;
        int father, leftBrother;
        Node(int v,int ls=0, int r=0, int f=0, int lb=0):value(v),leftSon(ls),
                                    rightBrother(r),father(f),leftBrother(lb){}
    };
    Node **tree;
    int Size;
    int Root;

    void preOrder(int x)
    {
        if(x<=Size)
        {
            cout << x << ' ';
            Node *tmp = tree[x];
            if(tmp->leftSon != 0)
            {
                tmp = tree[tmp->leftSon];
                preOrder(tmp->value);
                while(tmp->rightBrother != 0)
                {
                    tmp = tree[tmp->rightBrother];
                    preOrder(tmp->value);
                }
            }
        }
    }

    void postOrder(int x)
    {
        if(x<=Size)
        {
            Node *tmp = tree[x];
            if(tmp->leftSon != 0)
            {
                tmp = tree[tmp->leftSon];
                postOrder(tmp->value);
                while(tmp->rightBrother != 0)
                {
                    tmp = tree[tmp->rightBrother];
                    postOrder(tmp->value);
                }
            }
            cout << x << ' ';
        }
    }
public:
    Tree(int s)
    {
        Size = s;
        tree = new Node*[Size+1];
        for(int i = 0;i <= Size ; i++)
            tree[i] = new Node(i);
    }
    void Insert(int x,int Cx,int Sx)
    {
        if(Cx != 0){tree[x]->leftSon = Cx;tree[Cx]->father = x;}
        if(Sx != 0){tree[x]->rightBrother = Sx;tree[Sx]->leftBrother = x;}
    }
    void setRoot()
    {
        Node *tmp = tree[1];
        while(tmp->leftBrother != 0 || tmp->father != 0)
        {
            if(tmp->leftBrother != 0)
                tmp = tree[tmp->leftBrother];
            else
                tmp = tree[tmp->father];
        }
        Root = tmp->value;
    }
    void preOrder()
    {
        preOrder(Root);
        cout << endl;
    }
    void postOrder()
    {
        postOrder(Root);
        cout << endl;
    }
    void traverse()
    {
        int tmp;
        linkQueue Q;
        Q.enQueue(Root);

        while(!Q.isEmpty())
        {
            tmp = Q.deQueue();
            cout << tmp << ' ';
            if(tree[tmp]->leftSon != 0)
                Q.enQueue(tree[tmp]->leftSon);
            tmp = tree[tmp]->leftSon;
            if(tree[tmp]->rightBrother != 0)
            {
                while(tree[tmp]->rightBrother != 0)
                {
                    Q.enQueue(tree[tmp]->rightBrother);
                    tmp = tree[tmp]->rightBrother;
                }
            }
        }

        cout << endl;
    }
};


int main()
{
    int N, a, b, c;


    cin >> N;
    Tree aTree(N);

    for(int i = 0;i<N;i++)
    {
        cin >> a >> b >> c;
        aTree.Insert(a,b,c);
    }
    aTree.setRoot();
    aTree.preOrder();
    aTree.postOrder();
    aTree.traverse();
    return 0;
}
