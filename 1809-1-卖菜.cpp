#include<iostream>
using namespace std;
const int maxn = 1001;
int first[maxn];  //第一天的价格
int second[maxn];  //第二天的价格
int main()
{
    int n;  //商店数量
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> first[i];
    }
    //计算第二天的菜价
    //单独计算1和n
    second[1] = (first[1] + first[2]) / 2;
    second[n] = (first[n] + first[n-1]) / 2;
    for (int i = 2; i < n; i++)
    {
        second[i] = (first[i] + first[i-1] + first[i+1]) / 3;
    }
    for (int i = 1; i <= n; i++)
    {
        cout << second[i] << " ";
    }
    return 0;
}