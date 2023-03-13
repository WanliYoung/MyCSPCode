#include<iostream>
using namespace std;
const int maxn = 1e5 + 1;
bool if_come[maxn];  //每个变量是否作为左值出现过
int main()
{
    int n, k;
    cin >> n >> k;  //n个变量，k条赋值语句
    int x, y;
    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        cin >> x >> y;
        if (y && !if_come[y])
        {
            ans++;
        }
        if_come[x] = true;
    }
    cout << ans;
    return 0;
}