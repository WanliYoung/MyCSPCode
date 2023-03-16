#include<iostream>
#include<math.h>
using namespace std;
int N, M;  //苹果树棵数和蔬果轮数
const int maxN = 1001, maxM = 1001;
int apple_num[maxN];  //实时的苹果数目
int del_num[maxN];  //累计的蔬果数目
int main()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        cin >> apple_num[i];  //初始数量
        int d;
        for (int j = 1; j <= M; j++)
        {
            cin >> d;  //蔬果数量
            apple_num[i] += d;
            del_num[i] += abs(d);
        }
    }
    int T = 0, P = 0, k;
    for (int i = 1; i <= N; i++)
    {
        T += apple_num[i];
        if (del_num[i] > P)
        {
            k = i;
            P = del_num[i];
        }
        
    }
    cout << T << " "<< k << " " << P;
    return 0;
}