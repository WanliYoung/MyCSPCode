#include<iostream>
#include<cstring>
using namespace std;
const int maxn = 1001;
bool if_in[maxn];  //索引对应的小朋友是否还在局内
int main()
{
    int n, k;
    cin >> n >> k;
    int left_num = n;  //剩余的人数
    int count_num = 0;  //报的数
    for (int i = 1; i <= n; i++)
    {
        if_in[i] = true;
    }
    int flag = 1;
    while (left_num > 1)  //只要大于1就会继续游戏
    {
        while (!if_in[flag])
        {
            flag++; //给下一个人
            flag = flag % n;  //不能超过n个人的范围
            if (!flag)
            {
                flag = n;
            }
        }
        //找到报数的人了
        count_num++;
        if (count_num % k == 0 || count_num % 10 == k)
        {
            //出局
            left_num--;
            if_in[flag] = false;
        }
        //不管怎样，都要继续传递
        flag++;
        flag = flag % n;  //不能超过n个人的范围
        if (!flag)
        {
            flag = n;
        }
        //只管放不管是否有效
    }
    for (int i = 1; i <= n; i++)
    {
        if (if_in[i])
        {
            cout << i << endl;
            break;
        }
    }
    return 0;
}