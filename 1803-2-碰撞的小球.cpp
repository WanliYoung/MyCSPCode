#include<iostream>
#include<algorithm>
using namespace std;
struct Ball
{
    int index, position;
};
bool cmp(Ball b1, Ball b2)
{
    return b1.position < b2.position;  //一定不重叠
}
int main()
{
    int n, L, t;
    cin >> n >> L >> t;  
    int* a = new int [n];  //n个点的初始位置
    Ball* balls = new Ball[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        balls[i].index = i;
        balls[i].position = a[i];
        a[i] += t;  //经过时间t之后
        //换算
        int left = a[i] % L;
        int times = a[i] / L;  //奇数代表向左，偶数代表向右
        if (times % 2 == 0)
        {
            a[i] = left;
        }
        else
        {
            a[i] = L - left;
        }
    }
    //对a排个序
    sort(a, a+n);  //默认升序
    sort(balls, balls+n, cmp);
    int* r = new int[n];
    for (int i = 0; i < n; i++)
    {
        r[balls[i].index] = a[i];
    }
    
    for (int i = 0; i < n; i++)
    {
        cout << r[i] << " ";
    }
    
    //问题是输入并不是按序的
    /*
    时间t其实就是每个小球走过的路程
    由于小球的碰撞实际上就是速度就换，我们可以理解成两个小球穿过了对方
    这意味着只有碰壁才会改变方向，其实球间碰撞不影响位置分布
    当然前提是不考虑小球编号问题
    只是求时间t之后n个球的分布状态
    但是因为小球不会互相穿过，所以一定是从左往右排列的
    */
   
    
    return 0;
}