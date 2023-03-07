#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5e5 + 1;
const int maxN = 1e4 + 2;
int A[maxn];
int cnt[maxN];
int B[maxN];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
        if (A[i] > A[i-1])
        {
            B[A[i-1]]++;
            B[A[i]]--;
        }
    }
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < maxN; i++)
    {
        sum += B[i];
        if (ans < sum)
        {
            ans = sum;
        }
    }
    cout << ans << endl;
}