#include<iostream>
using namespace std;
const int maxh = 1e6+5;
int b[maxh];  //差分数组
int a[maxh];  //原数字
int numOfTime[200001];  //浇了i次水的花数
int main()
{
    int n;
    cin >> n;
    int l, r;
    for(int i = 1; i<= n; i++)
    {
        cin >> l >> r;
        //对差分数组做出操作
        b[r+1] -= 1;
        b[l] += 1;
    }
    //计算原数组
    a[0] = b[0];
    numOfTime[a[0]]++;
    for(int i = 1; i <= 1e6; i++)
    {
        a[i] = b[i] + a[i-1];
        numOfTime[a[i]]++;
    }
    for(int i = 1; i <= n; i++)
    {
        cout << numOfTime[i] << " ";
    }
    return 0;
}