#include<iostream>
using namespace std;
int main(){
    //读取输入
    int n,m;
    cin>>n>>m;
    int* a = new int[n + 1];
    int* b = new int[n + 1];
    int* c = new int[n];
    int* d = new int[n];
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
    }
    //计算ci
    for (int i = 0; i < n; i++)
    {
        c[i] = 1;
        for (int j = 1; j < i+1; j++)
        {
            c[i] *= a[j];
        }
    }
    //计算bi
    for (int i = 1; i < n; i++)
    {
        d[i-1] = m % c[i];
    }
    d[n-1] = m;
    b[1] = d[0] / c[0];
    for (int i = 2; i <= n; i++)
    {
        b[i] = (d[i-1] - d[i-2]) / c[i-1];
    }
    for (int i = 1; i <= n; i++)
    {
        cout<<b[i]<<" ";
    }
    return 0;
}