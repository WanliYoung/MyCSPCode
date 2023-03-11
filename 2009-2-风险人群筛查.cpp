//还是先用暴力理解题目意思
//暴力完全没问题，但是之前写了一个版本错了，不知道错在哪里
#include<iostream>
using namespace std;
int main(){
    int n, k, t, xl, yd, xr, yu;
    cin >> n >> k >> t >> xl >> yd >> xr >> yu;

    int pass_num = 0;
    int stay_num = 0;
    int sum = 0;
    bool pass_flag, stay_flag;
    int x, y;

    for (int i = 1; i <= n; i++)
    {
        sum = 0;
        pass_flag = false;
        stay_flag = false;
        for (int j = 1; j <= t; j++)
        {
            cin >> x >> y;
            if (x >= xl && x <= xr && y >= yd && y <= yu)
            {
                sum++;
                pass_flag = true;
                if (sum == k)
                {
                    stay_flag = true;
                }
            }
            else
            {
                sum = 0;
            }
        } 
        if (pass_flag)
        {
            pass_num++;
        }
        if (stay_flag)
        {
            stay_num++;
        } 
    }
    cout << pass_num << endl;
    cout << stay_num << endl;
    
    return 0;
}