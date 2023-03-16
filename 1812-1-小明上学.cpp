#include<iostream>
using namespace std;
int main()
{
    int r, y, g;
    cin >> r >> y >> g;
    int n;
    cin >> n;
    int k, t;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> k >> t;
        if (k == 0)
        {
            ans += t;
        }
        else
        {
            if (k == 3)  //绿灯
            {
                continue;
            }
            else if (k == 2)  //黄灯，要等待
            {
                ans = ans + t + r;
            }
            else //红灯
            {
                ans += t;
            }
        }
    }
    cout << ans << endl;
    return 0;
}