#include <iostream>
using namespace std;

class BinaryTree
{
private:
    struct Node
    {
        Node  *left, *right, *father;
        int data;
        Node() : data(0), left(NULL), right(NULL), father(NULL) {}
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
        int le, ri, i;

        num = size;
        for(i = 0; i < size; i++)
            total[i] = new Node;
        for(i = 0; i < size; i++)
        {
            cin >> le >> ri;
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
        root->data = 1;
        setValue(root);
    }
	bool isCompleteTree(int size)
	{
	    if(valueIsOut(root,size))
            return false;
        else
            return true;
	}

    void clear()
        {if (root != NULL) clear(root); root = NULL;}
    int height() const { return height(root); }

private:
    void clear( Node *t )
    {
    if(t->left != NULL)
        clear(t->left);
    if(t->right != NULL)
        clear(t->right);
    delete t;
    }
    int height( Node *t ) const
    {
        if(t == NULL)
            return 0;
        else
        {
            int lt = height(t->left), rt = height(t->right);
                return 1 + ((lt > rt)? lt : rt);
        }
    }
    void setValue(Node *t)
    {
        if (t->left != NULL || t->right != NULL)
        {
            if(t->left != NULL)
            {
                t->left->data = 2 * t->data;
                setValue(t->left);
            }

            if(t->right != NULL)
            {
                t->right->data = 2 * t->data + 1;
                setValue(t->right);
            }
        }
    }
    bool valueIsOut(Node *t,int size)
    {
        if(t == NULL)
            return false;
        else if(t->data > size)
            return true;
        else if(valueIsOut(t->left,size)||valueIsOut(t->right,size))
            return true;
    }
};



int main()
{
    int size;
    BinaryTree tree;

    cin >> size;
    tree.MakeTree(size);
    if(tree.isCompleteTree(size))
        cout << 'Y' << endl;
    else
        cout << 'N' << endl;


    return 0;
}
