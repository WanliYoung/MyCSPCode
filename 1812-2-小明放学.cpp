#include<iostream>
using namespace std;
int main()
{
    int r, y, g;
    cin >> r >> y >> g;
    int total = r + y + g;  //一轮的时间
    int n;
    cin >> n;
    long long pass_time = 0;  //记录消耗的时间
    int k, t;
    for (int i = 0; i < n; i++)
    {
        cin >> k >> t;
        if (k == 0)  //经过一段路
        {
            pass_time += t;
        }
        else //经过红绿灯
        {
            if (k == 1)  //出发的时候是红灯，还剩t秒
            {
                long long left = t - pass_time;
                if (left == 0)
                {
                    //刚好绿灯，不做处理
                    continue;
                }
                else if (left > 0)
                {
                    //还是红灯，继续等待
                    pass_time += left;
                }
                else  //红灯过了
                {
                    left *= -1;  //先变成正数
                    left = left % total;  
                    if (left >=0 && left < g)  //是绿灯，直接过
                    {
                        continue;
                    }
                    else if (left >= g && left < (g+y))  //黄灯，等着
                    {
                        pass_time += ((g+y) - left) + r;
                    }
                    else  //红灯
                    {
                        pass_time += r - (left - (g+y));
                    }
                }
            }
            else if (k == 2)  //出发的时候是黄灯
            {
                long long left = t - pass_time;
                if (left == 0)
                {
                    //刚好红灯，直接加
                    pass_time += r;
                }
                else if (left > 0)
                {
                    //还是黄灯，继续等待
                    pass_time += (left + r);
                }
                else  //黄灯过了
                {
                    left *= -1;  //先变成正数
                    left = left % total;  
                    if (left >=0 && left < r)  //是红灯
                    {
                        pass_time += (r - left);
                    }
                    else if (left >= r && left < (r+g))  //绿灯，过
                    {
                        continue;
                    }
                    else  //黄灯
                    {
                        pass_time += r + ((r+g+y) - left);
                    }
                }
            }
            else  //出发的时候是绿灯
            {
                long long left = t - pass_time;
                if (left == 0)
                {
                    //刚好黄灯，直接加
                    pass_time += r + y;
                }
                else if (left > 0)
                {
                    //还是绿灯，过
                    continue;
                }
                else  //绿灯过了
                {
                    left *= -1;  //先变成正数
                    left = left % total;  
                    if (left >=0 && left < y)  //是黄灯
                    {
                        pass_time += (y - left) + r;
                    }
                    else if (left >= y && left < (y+r))  //红灯
                    {
                        pass_time += r - (left - y);
                    }
                    else  //绿灯
                    {
                        continue;
                    }
                }
            }
        }
    }
    cout << pass_time;  //所用时间
    return 0;
}