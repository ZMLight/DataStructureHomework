#include <iostream>
using namespace std;

int divide(int a[],int low, int high);

void quickSort(int a[],int low,int high)
{
    int mid;
    if(low>=high)   return;
    mid = divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}

int divide(int a[],int low, int high)
{
    int k = a[low];
    do{
        while(low<high&&a[high]>=k) --high;
        if(low<high)
        {
            a[low] = a[high];++low;
        }
        while(low<high && a[low]<=k) ++low;
        if(low <high)
        {
            a[high] = a[low];--high;
        }
    }while(low!=high);

    a[low] = k;
    return low;
}


int main()
{
    int n, tmp, *a;

    cin >> n;
    a = new int[n];
    for(int i =0;i<n;i++)
    {
        cin >> tmp;
        a[i] = tmp;
    }

    quickSort(a,0,n-1);

    for(int i = 0; i< n;i++)
        cout << a[i] << ' ';

    return 0;
}
