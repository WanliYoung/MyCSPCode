#include<iostream>
using namespace std;
int main()
{
    int score, ans = 0;  //每一次的得分，总得分
    int flag = 0;  //标识之前有没有跳到中心
    for (int i = 1; i <= 30; i++)  //最多30个
    {
        cin >> score;
        if (score == 0)
        {
            //游戏结束
            break;
        }
        else if (score == 1)
        {
            ans += 1;
            flag = 0;
        }
        else if (score == 2)
        {
            if (flag)
            {
                flag += 2;
                ans += flag;
            }
            else
            {
                flag = 2;
                ans += flag;
            }
        }
    }
    cout << ans;
    return 0;
}