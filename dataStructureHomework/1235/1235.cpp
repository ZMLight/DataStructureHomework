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
        edgeNode *next;
        verNode(int s = 0, edgeNode *n = NULL):sonNum(s), next(n){}
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
public:
    MyGraph(int n, int m, int s, int e)
    {
        Vers = n; Edges = m; Start = s; End = e;
        distance = new int[Vers+1];
        prev = new int[Vers+1];
        gra = new verNode*[Vers+1];

        for(int i = 0;i < Vers+1;i++)
        {
            gra[i] = new verNode(0);
            prev[i] = -1;
        }
    }
    void Insert(int a, int b, int p)
    {
        edgeNode *tmp = gra[a]->next;
        gra[a]->next = new edgeNode(b,p);
        gra[a]->next->next = tmp;
    }
    void printPath()
    {
        for(int i = End; i!=Start; i=prev[i])
        	cout << i << ' ';
	    cout << Start << endl;
    }
    void Dijkstra(int max)
    {
        int now;
        NODE tmpNode;
        priorityQueue<NODE> QUEUE;
        for(int i = 0;i<Vers+1;i++)
        {
            distance[i] = max;
        }
        distance[Start] = 0;
        prev[Start] = Start;
        QUEUE.enQueue(NODE(Start,0));

        while (!QUEUE.isEmpty())
        {
            tmpNode = QUEUE.deQueue();
            now = tmpNode.num;
            for (edgeNode *j = gra[now]->next; j; j = j->next)
            if (distance[now] + j->value < distance[j->end])
            {
                prev[j->end] = now;
                distance[j->end] = distance[now] + j->value;
                QUEUE.enQueue(NODE(j->end, distance[j->end]));
            }
        }
        cout << distance[End] << endl;
        printPath();
    }
};


int main()
{
    int n,m,start,end,a,b,p;
    cin >> n >> m >> start >> end;

    MyGraph GG(n,m,end,start);

    for(int i = 0; i < m; i++)
    {
        cin >> a >> b >> p;
        GG.Insert(b,a,p);
    }

    GG.Dijkstra(2147483646);

    return 0;
}
