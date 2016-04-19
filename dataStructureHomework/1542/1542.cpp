#include <iostream>
using namespace std;

const int N = 300005;

int a[N],tmp[N];
long long ans;

void merge(int left,int mid,int right)
{
    int i = left, j = mid, k = 0;
    while(i<mid&&j<=right)
    {
        if(a[i]>a[j])
        {
            tmp[k++] = a[j++];
            ans += mid - i;
        }
        else
            tmp[k++] = a[i++];
    }
    while(i<mid) tmp[k++] = a[i++];
    while(j<=right) tmp[k++] = a[j++];

    for(i = 0,k = left;k<=right;)
    {
        a[k++] = tmp[i++];
    }
}

void mergeSort(int left,int right)
{
    int mid = (left+right)/2;

    if(left==right) return;
    mergeSort(left,mid);
    mergeSort(mid+1,right);
    merge(left,mid+1,right);
}

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n;i++)
        cin >> a[i];
    mergeSort(0,n-1);
    cout << ans;

    return 0;
}
