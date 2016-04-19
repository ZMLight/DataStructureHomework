#include <iostream>
#include <cstring>
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
        int dataOfLocation;
        Node() : data(0), left(NULL), right(NULL), father(NULL) {}
        Node(int item, Node *L, Node *R, Node *F):data(item), left(L), right(R), father(F) {}
        ~Node() {}
    };
  	Node *root;
  	int num;
public:
	BinaryTree() {root = NULL;num = 0;}
	~BinaryTree()  { clear(); }

	Node *getRoot() const
	{
	    return root;
	}

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
        setValue();
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

    void setValue()
    {
        root->dataOfLocation = 1;
        setValue(root);
    }

    bool isSameWith(const BinaryTree &other)
    {
        if(num != other.getSize())
            return false;
        bool flag = true;
        linkQueue<Node*> TreeQueue1, TreeQueue2;
        int levelOd1, levelOd2, location1, location2;

	    TreeQueue1.enQueue(root);
	    TreeQueue2.enQueue(other.getRoot());
	    while(!TreeQueue1.isEmpty())
	    {
	        levelOd1 = TreeQueue1.getHead()->data;
	        location1 = TreeQueue1.getHead()->dataOfLocation;
            levelOd2 = TreeQueue2.getHead()->data;
	        location2 = TreeQueue2.getHead()->dataOfLocation;

            if(levelOd1 != levelOd2 || location1 != location2)
            {
                flag = false;
                break;
            }
	        if(TreeQueue1.getHead()->left != NULL)
                TreeQueue1.enQueue(TreeQueue1.getHead()->left);
            if(TreeQueue1.getHead()->right != NULL)
                TreeQueue1.enQueue(TreeQueue1.getHead()->right);

	        if(TreeQueue2.getHead()->left != NULL)
                TreeQueue2.enQueue(TreeQueue2.getHead()->left);
            if(TreeQueue2.getHead()->right != NULL)
                TreeQueue2.enQueue(TreeQueue2.getHead()->right);


            TreeQueue1.deQueue();
            TreeQueue2.deQueue();
	    }

        return flag;
    }

    void clear()
        {if (root != NULL) clear(root); root = NULL;}

    int getSize() const
    {
        return num;
    }

private:
    void clear( Node *t )
    {
        if(t->left != NULL)
            clear(t->left);
        if(t->right != NULL)
            clear(t->right);
        delete t;
    }
    void setValue(Node *t)
    {
        if (t->left != NULL || t->right != NULL)
        {
            if(t->left != NULL)
            {
                t->left->dataOfLocation = 2 * t->dataOfLocation;
                setValue(t->left);
            }

            if(t->right != NULL)
            {
                t->right->dataOfLocation = 2 * t->dataOfLocation + 1;
                setValue(t->right);
            }
        }
    }
};


int main()
{
    int size1, size2;
    BinaryTree tree1, tree2;

    cin >> size1;
    tree1.MakeTree(size1);
    cin >> size2;
    tree2.MakeTree(size2);

    if(tree1.isSameWith(tree2))
        cout << 'Y' << endl;
    else
        cout << 'N' << endl;

    return 0;
}
