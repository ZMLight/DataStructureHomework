#include <iostream>
using namespace std;


struct Node
{
    int left,right,father;
    Node(int l,int r,int f):left(l),right(r),father(f){}
};

int N, X, Y, left, right, counts, root;
int *Disjointset, *PostOrder;
Node **Tree;

void postOrder(int root)
{
    if(Tree[root]->left != 0)
        postOrder(Tree[root]->left);
    if(Tree[root]->right != 0)
        postOrder(Tree[root]->right);
    PostOrder[++counts] = root;
}

void insertK(int x)
{
    Disjointset[x] = Tree[x]->father;
}

int find(int x)
{
    while(Disjointset[x] != -1)
        x = Disjointset[x];
    return x;
}

int main()
{
    int a, b;
    cin >> N >> X >> Y;

    Tree = new Node*[N+1];
    for(int i = 0; i <= N; i++)
        Tree[i] = new Node(0,0,0);
    for(int i = 1; i <= N; i++)
    {
        cin >> a >> b;
        Tree[i]->left = a;
        Tree[i]->right = b;
        if(X != 0)
            Tree[a]->father = i;
        if(Y != 0)
            Tree[b]->father = i;
    }

    Disjointset = new int[N+1];
    for(int i = 0; i <= N;i++)
        Disjointset[i] = -1;

    root = 1;
    if(Tree[root]->father != 0)
        root = Tree[root]->father;

    PostOrder = new int[N+1];
    counts = 0;
    postOrder(root);

    for(int i = 1; i <= N; i++)
    {
        insertK(PostOrder[i]);
        if(find(X) == find(Y))
        {
            cout << find(X) << endl;
            break;
        }
    }


//    for(int i = 1; i <= N;i++)
//    {
//        cout << PostOrder[i] << ' ';
//    }
    return 0;
}
