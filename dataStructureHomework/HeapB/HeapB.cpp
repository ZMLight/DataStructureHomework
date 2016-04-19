#include <iostream>
using namespace std;

int getMaxLocation(long long *nums,int mi,int ma)
{
    long long MAX = nums[mi];
    int location = mi;
    for(int i = mi;i<=ma;i++)
        if(nums[i]>MAX)
    {
        MAX = nums[i];
        location = i;
    }
    return location;
}

int main()
{
    int k, n ,*maxLocation;
    long long *nums;

    cin >> k >> n;
    nums = new long long[n];
    for(int i = 0; i < n;i++)
        cin >> nums[i];

    maxLocation = new int[n-k+1];

    maxLocation[0] = getMaxLocation(nums,0,k-1);
    for(int i =1;i<=n-k;i++)
    {
        if(maxLocation[i-1]>=i)
        {
            if(nums[maxLocation[i-1]]<=nums[i+k-1])
                maxLocation[i] = i+k-1;
            else
                maxLocation[i] = maxLocation[i-1];
        }
        else
        {
            maxLocation[i] = getMaxLocation(nums,i,i+k-1);
        }

    }

    for(int i =0;i<n-k+1;i++)
        cout << nums[maxLocation[i]] <<' ';
    cout << endl;

    return 0;

}
