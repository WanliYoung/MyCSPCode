#include<iostream>
#include<math.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    double* a = new double[n];
    double ave = 0;
    for (int i = 0; i < n; i++)
    {
        cin>>a[i];
        ave += a[i];
    }
    ave /= n;  //平均值
    double D = 0;
    for (int i = 0; i < n; i++)
    {
        D += pow((a[i] - ave), 2);
    }
    D /= n;  //方差
    double* fa = new double[n];
    for (int i = 0; i < n; i++)
    {
        fa[i] = (a[i] - ave) / sqrt(D);
        cout<<fa[i]<<endl;
    }
    return 0;
}