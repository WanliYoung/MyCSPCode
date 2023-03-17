#include<iostream>
using namespace std;
const int maxn = 2001;
int n;
struct Times  //装车的时间区间
{
    int begin;
    int end;
};
Times ab[maxn], cd[maxn];

int main()
{
    cin >> n;  //时间段的数量
    for (int i = 1; i <= n; i++)
    {
        cin >> ab[i].begin >> ab[i].end;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> cd[i].begin >> cd[i].end;
    }

    //现在要求两人的重合时间长度，感觉是个双指针问题
    long long ans = 0;
    int ptrab = 1, ptrcd = 1;
    while (ptrab <= n && ptrcd <= n)  //有一个算完了就没必要了
    {
        while (ptrab <= n && ab[ptrab].end <= cd[ptrcd].end)
        {
            //计算一下
            if (ab[ptrab].end <= cd[ptrcd].begin)  //没有重合
            {
                ans += 0;  
            }
            else  //有重合
            {
                ans += ab[ptrab].end - max(cd[ptrcd].begin, ab[ptrab].begin);  //需要确定下限
            }
            //计算完换下一段
            ptrab++;
            if (ptrab > n)  //已经到头了，就直接结束
            {
                goto label;
            }
        }
        
        while (ptrcd <= n && cd[ptrcd].end < ab[ptrab].end)
        {
            //计算一下
            if (cd[ptrcd].end <= ab[ptrab].begin)  //没有重合
            {
                ans += 0;  
            }
            else  //有重合
            {
                ans += cd[ptrcd].end - max(ab[ptrab].begin, cd[ptrcd].begin);
            }
            //计算完换下一段
            ptrcd++;
            if (ptrcd > n)  //已经到头了，就直接结束
            {
                goto label;
            }
        }
    }
label:
    cout << ans;
    return 0;
}