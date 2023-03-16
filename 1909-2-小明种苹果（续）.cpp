#include<iostream>
using namespace std;
int N;
const int maxN = 1001;
int apple_num[maxN];  //实时苹果数目
bool if_drop[maxN];  //每棵树是否掉落
int main()
{
    cin >> N;
    int m, a;
    for (int i = 1; i <= N; i++)
    {
        cin >> m;
        cin >> a;  //第一个数一定是个数
        apple_num[i] = a;
        for (int j = 0; j < m-1; j++)
        {
            cin >> a;
            if (a <= 0)  //蔬果操作
            {
                apple_num[i] += a;
            }
            else
            {
                if (a == apple_num[i])  //没有掉落
                {
                    ;
                }
                else
                {
                    apple_num[i] = a;
                    if_drop[i] = true;
                }
            }
        }
    }
    int T = 0, D = 0, E = 0;  //flag表示目前连续掉落的数目
    for (int i = 1; i <= N; i++)
    {
        T += apple_num[i];
        if (if_drop[i] == true)
        {
            D++;
            //向后看两位
            int b1 = i+1, b2 = i+2;
            b1 = b1 % N;
            b2 = b2 % N;
            if (b1 == 0)
            {
                b1 = N;
            }
            if (b2 == 0)
            {
                b2 = N;
            }
            if (if_drop[b1] && if_drop[b2])
            {
                E++;
            }
        }
    }
    cout << T << " " << D << " " << E;
    return 0;
}
