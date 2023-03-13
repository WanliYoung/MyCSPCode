#include<iostream>
using namespace std;
int skip_num[4];  //每个人跳过次数
bool if_seven(int x)
{
    //数字x是否：包含7或者是7的倍数
    if (x % 7 == 0)  //是7的倍数
    {
        return true;
    }
    else  //不是7的倍数
    {
        int tmp;
        while (x > 0)
        {
            tmp = x % 10;
            x /= 10;
            if (tmp == 7)
            {
                return true;
            }
        }
    }
    return false;
}
int main()
{
    int n;
    cin >> n;  //报出n个数之后结束
    int count = 0;  //报数数目
    int number = 0;
    int flag = -1;  // 0 1 2 3代表甲乙丙丁
    while (count < n)
    {
        number++;
        flag++;
        flag = flag % 4;
        if (if_seven(number))
        {
            skip_num[flag]++;
        }
        else
        {
            count++;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        cout << skip_num[i] << endl;
    }
    
    return 0;
}