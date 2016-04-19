#include <iostream>
using namespace std;

template <class T>
class linkedList
{
	friend void operator+(const linkedList& list1,const linkedList& list2)
	{
	    linkedList list3;
	    Node *temp1 = list1.head->next;
	    Node *temp2 = list2.head->next;

	    for(int i = 0;i< list2.length;i++)
	    {
	        list3.insert(temp2->data);
	        temp2 = temp2->next;
	    }
	    for(int i = 0;i< list1.length;i++)
	    {
	        list3.insert(temp1->data);
	        temp1 = temp1->next;
	    }

	    list3.print();
	}
public:
    struct Node{
        T data;
        Node * next;
        Node(const T & d):data(d),next(NULL){}
    };
    void insert(const T &n)
	{
	    Node *temp = new Node(n);
	    temp->next = head->next;
	    head->next = temp;
	}
	linkedList(const int &n=0)
	{
	    length = n;
	    head = new Node(0);
	    for(int i=0;i<length;i++)
	    {
	        T temp;
	        cin>>temp;
	        insert(temp);
	    }
	}
	~linkedList(){clear();}
	void print()
	{
	    Node *p = head->next;
	    while(p)
	    {
	        Node *q = p->next;
	        cout<<p->data<<' ';
	        p = q;
	    }
	}
private:
	int length;
	Node *head;
	void clear()
	{
	    Node *p = head->next;
	    while(p)
	    {
	        Node *q = p->next;
	        delete p;
	        p = q;
	    }
	}
};


int main()
{
    char t[10];
    cin.getline(t,10);
    int n,m;
    cin>>n>>m;

    if(t[0]=='i')
    {
        linkedList<int> list1(n),list2(m);
        list1+list2;
    }
    if(t[0]=='c')
    {
        linkedList<char> list1(n),list2(m);
        list1+list2;
    }
    if(t[0]=='d')
    {
        linkedList<double> list1(n),list2(m);
        list1+list2;
    }
    return 0;
}
