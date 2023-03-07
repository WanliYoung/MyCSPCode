#include<iostream>
using namespace std;
const int maxn = 101;
int B[maxn];
int A[maxn];
int main(){
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> B[i];
    }
    int sum_max = 0, sum_min = 0;

    if (n == 1)
    {
        cout << B[1] << endl;
        cout << B[1] << endl;
    }
    else
    {
        A[1] = B[1];
        sum_max += A[1];
        sum_min += A[1];
        for (int i = 2; i <= n; i++)
        {
            if (B[i] > B[i-1])  //A[i]确定
            {
                A[i] = B[i];
                sum_max += A[i];
                sum_min += A[i];
            }
            else  //A[i]不确定
            {
                sum_max += B[i-1];
                sum_min += 0;
            }
        }
        cout << sum_max << endl;
        cout << sum_min << endl;
    }

    return 0;
}