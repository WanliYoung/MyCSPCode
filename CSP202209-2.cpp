#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n, x;
    cin>>n>>x;
    int* a = new int[n + 1];
    int sum = 0;  //总额
    for (int i = 1; i <= n; i++)
    {
        cin>>a[i];
        sum += a[i];
    }
    sort(a+1, a+n+1);
    //比x大的当中选最小的集合，转换一个角度就是从sum-x当中选不超过的最大的集合
    //实际上就是子集和问题，用动态规划做
    int y = sum - x;
    int** M;
    M = new int*[n + 1];
    for (int i = 0; i <= n; i++)
    {
        M[i] = new int[y+1];
    }
    for (int i = 0; i <= y; i++)
    {
        M[0][i] = 0;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= y; w++)
        {
            if(a[i] > w){
                M[i][w] = M[i-1][w];
            }
            else{
                M[i][w] = max(M[i-1][w], a[i]+M[i-1][w-a[i]]);
            }
        } 
    }
    cout<<sum - M[n][y];
    return 0;
}