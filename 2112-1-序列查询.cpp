//CSP202112-2  序列查询

/*
顺着题目提示做即可
*/
#include<iostream>
using namespace std;
const int maxn = 1e5+1, maxN = 1e7;
int A[maxn];
int f[maxN];
int main(){
    int n, N;
    cin >> n >> N;
    A[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        int delt = A[i+1] - A[i];
        ans += delt * i;
    }

    ans += (N - A[n]) * n;
    
    cout << ans << endl;

    return 0;
}