#include <iostream>
using namespace std;

int divide(int a[],int low, int high)
{
    int k = a[low];
    do
    {
        while(low < high&&a[high] >=k) --high;
        if(low < high)
        {
            a[low] = a[high];
            ++ low;
        }
        while(low<high&&a[low]<=k) ++low;
        if(low < high)
        {
            a[high] = a[low];
            --high;
        }
    }while(low!=high);
    a[low] = k;
    return low;
}

void quickSort(int a[], int low, int high)
{
    int mid;
    if(low>=high) return ;
    mid = divide(a,low,high);
    quickSort(a,low,mid-1);
    quickSort(a,mid+1,high);
}

int main()
{
    int N, arr[100001];
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    quickSort(arr,0,N-1);

    for(int i = 0;i < N;i++)
    {
        cout << arr[i] << ' ';
    }

    return 0;

}
