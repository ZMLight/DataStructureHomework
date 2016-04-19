#include <iostream>
using namespace std;

class BinarySearchTree
{
private:
    struct BinaryNode
    {
        int data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(int thedata,BinaryNode *lt = NULL,BinaryNode *rt = NULL)
            :data(thedata),left(lt),right(rt){}
    };

    BinaryNode *root;
    void insert(int x, BinaryNode *&t);
    void remove(int x, BinaryNode *&t);
    bool find(int x, BinaryNode *t);
    void makeEmpty(BinaryNode *&t);
    void getMidOrder(int *arr,int &arrNum,BinaryNode *&t);

public:
    BinarySearchTree(BinaryNode *t = NULL){root = t;}
    ~BinarySearchTree(){makeEmpty(root);}
    bool find(int x);
    void insert(int x);
    void remove(int x);
    void getMidOrder(int *arr,int &arrNum);
};

void BinarySearchTree::getMidOrder(int *arr,int &arrNum)
{
    getMidOrder(arr,arrNum,root);
}

void BinarySearchTree::getMidOrder(int *arr, int &arrNum, BinaryNode *&t)
{
    if(t->left != NULL)
        getMidOrder(arr,arrNum,t->left);
    arr[arrNum++] = t->data;
    if(t->right != NULL)
        getMidOrder(arr,arrNum,t->right);
}
bool BinarySearchTree::find(int x)
{
    return find(x,root);
}

bool BinarySearchTree::find(int x, BinaryNode *t)
{
    if(t==NULL)
        return false;
    else if(x < t->data)
        return find(x,t->left);
    else if(x > t->data)
        return find(x,t->right);
    else
        return true;
}

void BinarySearchTree::insert(int x)
{
    insert(x,root);
}

void BinarySearchTree::insert(int x,BinaryNode *&t)
{
    if(t==NULL)
        t = new BinaryNode(x,NULL,NULL);
    else if(x < t->data)
        insert(x,t->left);
    else if(x >= t->data)
        insert(x,t->right);
}

void BinarySearchTree::remove(int x)
{
    remove(x,root);
}

void BinarySearchTree::remove(int x, BinaryNode *&t)
{
    if(t==NULL) return ;
    if(x < t->data)
        remove(x,t->left);
    else if(x > t->data)
        remove(x,t->right);
    else if(t->left !=NULL && t->right != NULL)
    {
        BinaryNode *tmp = t->right;
        while(tmp->left != NULL)
            tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data,t->right);
    }
    else
    {
        BinaryNode *oldNode = t;
        t = (t->left!=NULL) ?t->left:t->right;
        delete oldNode;
    }
}

void BinarySearchTree::makeEmpty(BinaryNode *&t)
{
//    if(t->left != NULL)
//        makeEmpty(t->left);
//    if(t->right != NULL)
//        makeEmpty(t->right);
//    if(t->left == NULL && t->right == NULL)
//        delete t;
}

int main()
{
    int N, operateNum, operateNum2;
    int arr[5001], arrNum = 0;
    char operation[25];
    BinarySearchTree TreeOne;

    cin >> N;

    for(int i = 0; i < N; i++)
    {
        cin >> operation;
        if(operation[0] == 'i')
        {
            cin >> operateNum;
            TreeOne.insert(operateNum);
        }
        if(operation[0] == 'd')
        {
            if(operation[6] == '\0')
            {
                cin >> operateNum;
                TreeOne.remove(operateNum);
            }
            else if(operation[7] == 'g')
            {
                arrNum = 0;
                cin >> operateNum;
                TreeOne.getMidOrder(arr,arrNum);
                for(int j = 0; j < arrNum; j++)
                {
                    if(arr[j] > operateNum)
                        TreeOne.remove(arr[j]);
                }
            }
            else if(operation[7] == 'l')
            {
                arrNum = 0;
                cin >> operateNum;
                TreeOne.getMidOrder(arr,arrNum);
                for(int j = 0; j < arrNum; j++)
                {
                    if(arr[j] < operateNum)
                        TreeOne.remove(arr[j]);
                }
            }
            else if(operation[7] == 'i')
            {
                arrNum = 0;
                cin >> operateNum >> operateNum2;
                TreeOne.getMidOrder(arr,arrNum);
                for(int j = 0; j < arrNum; j++)
                {
                    if(arr[j] > operateNum && arr[j] < operateNum2)
                        TreeOne.remove(arr[j]);
                }
            }
        }
        if(operation[0] == 'f')
        {
            if(operation[4] == '\0')
            {
                cin >> operateNum;
                if(TreeOne.find(operateNum))
                    cout << 'Y' << endl;
                else
                    cout << 'N' << endl;
            }
            else
            {
                arrNum = 0;
                cin >> operateNum;
                TreeOne.getMidOrder(arr,arrNum);
                if(arrNum < operateNum)
                    cout << 'N' << endl;
                else
                    cout << arr[operateNum - 1] << endl;
            }
        }
    }

    return 0;
}
