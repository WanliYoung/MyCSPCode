#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    cin >> a[0];
    int max = a[0], min = a[0];
    double mid;
    for (int i = 1; i < n; i++)
    {
        cin >> a[i];
        if (a[i] > max)
        {
            max = a[i];
        }
        if (a[i] < min)
        {
            min = a[i];
        }
    }
    //计算一下中位数
    if (n % 2 == 1)  //奇数个数字
    {
        mid = a[n / 2];
    }
    else
    {
        //两个数的平均值
        double n1 = a[n / 2 - 1];
        double n2 = a[n / 2];
        mid = (n1 + n2) / 2;
    }
    cout << max << " ";
    //cout << mid << " ";
    double delt = mid - (int)mid;
    if (delt == 0)
    {
        cout << (int)mid << " ";
    }
    else{
        cout << fixed << setprecision(1) << mid << " ";
    }
    cout << fixed << setprecision(0) << min << " ";
    return 0;
}