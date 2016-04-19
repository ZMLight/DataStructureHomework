#include <iostream>
using namespace std;

class adjListGraph
{
private:
    struct Node
    {
        int start,end;
        Node *next;
        Node(int s=0, int e=0, Node *n = NULL):start(s),end(e),next(n){}
    };
    int Vers, Edges;
    Node **verList;
    void dfs(int start, int M, bool visited[],int nums, int &counts)
    {
        if(nums==M)
        {
            counts ++;
            return ;
        }
        Node *p = verList[start-1];
        while(p->next != NULL)
        {
            p = p->next;
            if(visited[p->end]==true)
                continue;
            nums++;
            visited[p->end] = true;
            dfs(p->end,M,visited,nums,counts);
            visited[p->end] = false;
            nums--;
        }
        return;
    }
public:
    adjListGraph(int vSize,int edges)
    {
        Vers = vSize;Edges = edges;
        verList = new Node*[vSize];
        for(int i = 0;i<vSize;i++)
        {
            verList[i] = new Node(i+1,-1);
        }
    }
    bool insert(int a, int b)
    {
        Node *temp = verList[a-1];
        while(temp->next != NULL)
        {
            temp = temp->next;
            if(temp->end == b)
            {
                return true;
            }
        }
        temp->next = new Node(a,b);
        return false;
    }
    void dfs(int start, int M)
    {
        bool *visited = new bool[Vers];
        int counts = 0, nums = 0;
        for(int i = 0; i < Vers;i++)
            visited[i] = false;
        visited[start] = true;
        dfs(start,M,visited,nums,counts);
        cout << counts;
    }
};




int main()
{
    int n,m,start,M,x,y;
    cin >> n >> m >> start >> M;

    adjListGraph g(n,m);
    for(int i = 0; i<m;i++)
    {
        cin >> x >> y;
        g.insert(x,y);
    }
    g.dfs(start,M);
    return 0;
}
