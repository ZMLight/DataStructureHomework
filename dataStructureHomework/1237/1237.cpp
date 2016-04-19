#include <iostream>
using namespace std;

class MyGraph
{
private:
    struct Node
    {
        int inDegree;
        Node *next;
        int SonNum;
        Node(int in):inDegree(in),next(NULL){SonNum = 0;}
    };
    Node **gra;
    int Size;
public:
    MyGraph(int s)
    {
        Size = s;
        gra = new Node*[Size];
        for(int i = 0; i < Size; i++)
            gra[i] = new Node(0);
    }
    ~MyGraph()
    {

    }
    void Insert(int out, int in)
    {
        Node *tmp;
        gra[out]->inDegree ++;
        tmp = gra[in]->next;
        gra[in]->next = new Node(out);
        gra[in]->next->next = tmp;
        gra[in]->SonNum++;
    }
    int getTheTime()
    {
        Node *temp;
        bool flag = false;
        int counts = 0;
        bool *Sons;
        Sons = new bool[Size];
        for(int i = 0;i < Size;i++)
            Sons[i] = false;
        while(!flag)
        {
            flag = true;
            counts ++;
            for(int i = 1;i < Size; i++)
            {
                if(gra[i]->inDegree == 0)
                {
                    Sons[i] = true;
                }
                else if(gra[i]->inDegree > 0)
                    flag = false;
            }
            for(int i = 1;i < Size; i++)
            {
                if(Sons[i])
                {
                    temp = gra[i];
                    for(int j = 0;j<gra[i]->SonNum;j++)
                    {
                        temp = temp->next;
                        gra[temp->inDegree]->inDegree--;
                    }
                    gra[i]->inDegree = -1;
                }
            }
            for(int i = 0;i<Size;i++)
            {
                Sons[i] = false;
            }
        }

        delete [] Sons;
        return counts;
    }
};

int main()
{
    int n, m, a, b;
    cin >> n >> m;
    MyGraph g(n+1);
    for(int i = 0;i < m;i++)
    {
        cin >> a >> b;
        g.Insert(a,b);
    }
    cout << g.getTheTime();

    return 0;
}
