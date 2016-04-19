#include <iostream>
using namespace std;

template <class Type>
class priorityQueue
{
public:
    priorityQueue(int capacity = 100)
    {
        array = new Type[capacity];maxSize = capacity;currentSize = 0;
    }
    ~priorityQueue(){delete [] array;}

    bool isEmpty() const {return currentSize == 0;}
    void enQueue(const Type &x)
    {
        if(currentSize == maxSize-1)    doubleSpace();

        int hole = ++currentSize;
        for(;hole>1&&x<array[hole/2];hole /= 2)
            array[hole] = array[hole/2];
        array[hole] = x;
    }
    Type deQueue()
    {
        Type minItem;
        minItem = array[1];
        array[1] = array[currentSize --];
        percolateDown(1);
        return minItem;
    }
    Type getHead() const {return array[1];}
private:
    int currentSize;
    Type *array;
    int maxSize;

    void doubleSpace()
    {
        Type *tmp = array;
        maxSize *= 2;
        array = new Type[maxSize];

        for(int i = 0;i<=currentSize;i++)
            array[i] = tmp[i];

        delete []tmp;
    }
    void percolateDown(int hole)
    {
        int child;
        Type tmp = array[hole];

        for(;hole*2 <= currentSize;hole=child)
        {
            child = hole*2;
            if(child!=currentSize && array[child+1]<array[child])
                child ++;
            if(array[child]<tmp)
                array[hole] = array[child];
            else
                break;
        }
        array[hole] = tmp;
    }
};



class MyGraph
{
private:
    struct edgeNode
    {
        int end;
        int value;
        edgeNode *next;
        edgeNode(int e,int v, edgeNode *n = NULL):end(e),value(v),next(n){}
    };
    struct verNode
    {
        int sonNum;
        int level;
        edgeNode *next;
        verNode(int s = 0, edgeNode *n = NULL):sonNum(s), next(n){level=1;}
    };
    struct NODE
    {
        int num;
        int value;
        NODE(int n=0, int v=0):num(n),value(v){}
        bool operator<(const NODE &rp)const{return value<rp.value;}
        void operator=(const NODE &rp){num = rp.num;value = rp.value;}
    };
    verNode **gra;
    int Vers, Edges, Start, End;
    int *distance, *prev;
    bool *known;
    int min1,min2;
public:
    MyGraph(int n, int m, int s, int e)
    {
        Vers = n; Edges = m; Start = s; End = e;
        distance = new int[Vers+1];
        prev = new int[Vers+1];
        known = new bool[Vers+1];

        gra = new verNode*[Vers+1];
        min2=20000;

        for(int i = 0;i < Vers+1;i++)
        {
            gra[i] = new verNode(0);
            known[i] = false;
            prev[i] = -1;
        }
    }
    void Insert(int a, int b, int p)
    {
        edgeNode *tmp = gra[a]->next;

        while(tmp!=NULL)
        {
            if(tmp->end == b)
            {
                if(tmp->value > p)
                    tmp->value = p;
                break;
            }
            tmp = tmp->next;
        }

        if(tmp==NULL)
        {
            tmp = gra[a]->next;
            gra[a]->next = new edgeNode(b,p);
            gra[a]->sonNum ++;
            gra[a]->next->next = tmp;
        }
    }
    void printPath(int x)
    {
        int *Road, cnt = 0;
        Road = new int[Vers];

        while(prev[x] != x)
        {
            Road[cnt++] = x;
            x = prev[x];
        }

        cout << x << ' ';

        for(int i = cnt-1; i >= 0; i--)
        {
            cout << Road[i] << ' ';
        }
    }
    void Dijkstra(int max)
    {
        int u, min;
        NODE tmpNode;
        priorityQueue<NODE> QUEUE;

        for(int i = 0;i<Vers+1;i++)
        {
            distance[i] = max;
        }

        distance[Start] = 0;
        prev[Start] = Start;
        QUEUE.enQueue(NODE(Start,0));

        while(!known[End])
        {
            tmpNode = QUEUE.deQueue();
            while(known[tmpNode.num] && !QUEUE.isEmpty())
                tmpNode = QUEUE.deQueue();
            u = tmpNode.num;
            known[u] = true;
            min = tmpNode.value;

            edgeNode *tmp = gra[u]->next;
            while(tmp != NULL)
            {
                if(!known[tmp->end] && distance[tmp->end] > min + tmp->value)
                {
                    distance[tmp->end] = min + tmp->value;
                    prev[tmp->end] = u;

                    QUEUE.enQueue(NODE(tmp->end,distance[tmp->end]));

                }
                tmp = tmp->next;
            }
        }

        cout << distance[End] << endl;
        min1=distance[End];
        //printPath(End);
    }

    void Dijkstra1(int max)
    {
        int u, min;
        NODE tmpNode;
        priorityQueue<NODE> QUEUE;

        for(int i = 0;i<Vers+1;i++)
        {
            distance[i] = max;
        }

        distance[Start] = 0;
        prev[Start] = Start;
        QUEUE.enQueue(NODE(Start,0));

        while(!known[End])
        {
            tmpNode = QUEUE.deQueue();
            while(known[tmpNode.num] && !QUEUE.isEmpty())
                tmpNode = QUEUE.deQueue();
            u = tmpNode.num;
            known[u] = true;
            min = tmpNode.value;

            edgeNode *tmp = gra[u]->next;
            while(tmp != NULL)
            {
                if(!known[tmp->end] && distance[tmp->end] >= min + tmp->value)
                {
                    distance[tmp->end] = min + tmp->value;
                    gra[tmp->end]->level=gra[u]->level+1;
                    if(tmp->end==End and distance[tmp->end]==min1 and gra[tmp->end]->level<min1)
                    {min2=gra[tmp->end]->level;}
                    prev[tmp->end] = u;
                    QUEUE.enQueue(NODE(tmp->end,distance[tmp->end]));
                }
                tmp = tmp->next;
            }
        }

        //cout << distance[End] << endl;
        //printPath(End);
    }

    void Dijkstra2(int max)
    {
        int u, min;
        NODE tmpNode;
        priorityQueue<NODE> QUEUE;

        for(int i = 0;i<Vers+1;i++)
        {
            distance[i] = max;
        }

        distance[Start] = 0;
        prev[Start] = Start;
        QUEUE.enQueue(NODE(Start,0));
        bool flag=true;

        while(!known[End])
        {
            tmpNode = QUEUE.deQueue();
            while(known[tmpNode.num] && !QUEUE.isEmpty())
                tmpNode = QUEUE.deQueue();
            u = tmpNode.num;
            known[u] = true;
            min = tmpNode.value;

            edgeNode *tmp = gra[u]->next;
            while(tmp != NULL and flag)
            {
                if(!known[tmp->end] && distance[tmp->end] >= min + tmp->value)
                {
                    distance[tmp->end] = min + tmp->value;
                    gra[tmp->end]->level=gra[u]->level+1;
                    prev[tmp->end] = u;
                    if(tmp->end==End and gra[tmp->end]->level==min2 and distance[tmp->end]==min1)
                    {
                        flag=false;
                        printPath(End);
                    }
                    QUEUE.enQueue(NODE(tmp->end,distance[tmp->end]));
                }
                tmp = tmp->next;
            }
        }

        //cout << distance[End] << endl;
        //printPath(End);
    }
};


int main()
{
    int n,m,start,end,a,b,p;
    cin >> n >> m >> start >> end;

    MyGraph GG(n,m,start,end);

    for(int i = 0; i < m; i++)
    {
        cin >> a >> b >> p;
        if(a!=b)
            GG.Insert(a,b,p);
    }

    GG.Dijkstra(2147483646);
    GG.Dijkstra1(2147483646);
    GG.Dijkstra2(2147483646);
    return 0;
}
