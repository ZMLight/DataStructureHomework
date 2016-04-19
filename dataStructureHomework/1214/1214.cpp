#include <iostream>
using namespace std;


template <class elemType>
class linkQueue
{
private:
    struct Node
    {
        elemType data;
        Node *next;
        Node(const elemType &x, Node *N = NULL)
        {
            data = x;next = N;
        }
        Node():next(NULL){}
        ~Node(){}
    };
    Node *head, *tail;
public:
    linkQueue()
    {
        head = tail = NULL;
    }

    ~linkQueue()
    {
        Node *tmp;
        while(head != NULL)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    bool isEmpty()
    {
        return head == NULL;
    }

    void enQueue(const elemType &x)
    {
        if(tail == NULL)
            head = tail = new Node(x);
        else
        {
            tail->next = new Node(x);
            tail = tail->next;
        }
    }

    void deQueue()
    {
        Node *tmp = head;
        head = head->next;
        if(head == NULL)
            tail = NULL;
        delete tmp;
    }

    elemType getHead()
    {
        return head->data;
    }
};


class BinaryTree
{
private:
    struct Node
    {
        Node  *left, *rightBrother, *father, *leftBrother;
        int data;
        Node() : data(0), left(NULL), rightBrother(NULL), father(NULL), leftBrother(NULL) {}
        Node(int item, Node *L, Node *RB, Node *F, Node *LB):data(item), left(L), rightBrother(RB), father(F), leftBrother(LB) {}
        ~Node() {}
    };
  	Node *root;
  	int num;
public:
	BinaryTree() {root = NULL;num = 0;}
	~BinaryTree()  { clear(); }

	void MakeTree(int size)
	{
        Node *total[120000];
        int le, ri, va, i;

        num = size;
        for(i = 0; i < size; i++)
            total[i] = new Node;
        for(i = 0; i < size; i++)
        {
            cin >> le >> ri >> va;
            if(le != 0)
            {
                total[i]->left = total[le-1];
                total[le-1]->father = total[i];
            }
            if(ri != 0)
            {
                total[i]->rightBrother = total[ri-1];
                total[ri-1]->leftBrother = total[i];
            }
            total[i]->data = va;
        }
        if(size > 0)
            root = total[0];
        setRoot();
	}

	void setRoot()
	{
	    Node *p;
        if(num > 0)
        {
            p = root;
            while(p->father != NULL || p->leftBrother != NULL)
            {
                if(p->father != NULL)
                    p = p->father;
                else if(p->leftBrother != NULL)
                    p = p->leftBrother;
            }
            root = p;
        }
	}

    void levelOrder()
    {
        linkQueue<Node*> TreeQueue1,TreeQueue2;
        TreeQueue1.enQueue(root);

        while(!TreeQueue1.isEmpty() || !TreeQueue2.isEmpty())
        {
            if(TreeQueue1.isEmpty())
            {
                while(!TreeQueue2.isEmpty() && TreeQueue2.getHead()->left == NULL)
                    TreeQueue2.deQueue();
                if(!TreeQueue2.isEmpty())
                {
                    TreeQueue1.enQueue(TreeQueue2.getHead()->left);
                    TreeQueue2.deQueue();
                }
            }
            else
            {
                cout << TreeQueue1.getHead()->data << ' ';
                if(TreeQueue1.getHead()->rightBrother != NULL)
                {
                    TreeQueue1.enQueue(TreeQueue1.getHead()->rightBrother);
                }

                TreeQueue2.enQueue(TreeQueue1.getHead());
                TreeQueue1.deQueue();
            }
        }

        cout << endl;
    }

    void preOrder()
    {
        if(root != NULL)
        {
            preOrder(root);
            cout << endl;
        }
    }

    void postOrder()
    {
        if(root != NULL)
        {
            postOrder(root);
            cout << endl;
        }
    }

    void clear()
        {if (root != NULL) clear(root); root = NULL;}


private:
    void clear(Node *t)
    {
        if(t->rightBrother != NULL)
            clear(t->rightBrother);
        if(t->left != NULL)
            clear(t->left);
        delete t;
    }

    void preOrder(Node *t)
    {
        if(t != NULL)
        {
            cout << t->data << ' ';

            preOrder(t->left);
            preOrder(t->rightBrother);
        }
    }

    void postOrder(Node *t)
    {
        if(t != NULL)
        {
            postOrder(t->left);
            cout << t->data << ' ';
            postOrder(t->rightBrother);
        }
    }
};


int main()
{
    int size;
    BinaryTree tree;

    cin >> size;
    tree.MakeTree(size);
    tree.preOrder();
    tree.postOrder();
    tree.levelOrder();

    return 0;
}
