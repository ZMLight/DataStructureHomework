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
        Node  *left, *right, *father;
        int data;
        Node() : data(0), left(NULL), right(NULL), father(NULL) {}
        Node(int item, Node *L, Node *R, Node *F):data(item), left(L), right(R), father(F) {}
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
                total[i]->right = total[ri-1];
                total[ri-1]->father = total[i];
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
            while(p->father != NULL)
            {
                p = p->father;
            }
            root = p;
        }
	}
	void levelOrder()
	{
	    linkQueue<Node*> TreeQueue;
	    TreeQueue.enQueue(root);
	    while(!TreeQueue.isEmpty())
	    {
	        cout << TreeQueue.getHead()->data<< ' ';
	        if(TreeQueue.getHead()->left != NULL)
                TreeQueue.enQueue(TreeQueue.getHead()->left);
            if(TreeQueue.getHead()->right != NULL)
                TreeQueue.enQueue(TreeQueue.getHead()->right);
            TreeQueue.deQueue();
	    }
	}
    void clear()
        {if (root != NULL) clear(root); root = NULL;}

private:
    void clear( Node *t )
    {
        if(t->left != NULL)
            clear(t->left);
        if(t->right != NULL)
            clear(t->right);
        delete t;
    }
};


int main()
{
    int size;
    BinaryTree tree;

    cin >> size;
    tree.MakeTree(size);
    tree.levelOrder();

    return 0;
}
