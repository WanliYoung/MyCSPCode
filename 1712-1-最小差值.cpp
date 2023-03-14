#include<iostream>
#include<math.h>
using namespace std;
const int maxn = 1000;
int a[maxn];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int ans = 10001;  //初始化为很大的数
    int delt;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            delt = abs(a[i]-a[j]);
            if (delt < ans)
            {
                ans = delt;
            }   
        }
    }
    cout << ans << endl;
    return 0;
}