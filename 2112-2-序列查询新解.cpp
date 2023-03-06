//CSP202112-2  序列查询新解

/*
这道题的代码量并不大，也不是什么比较经典的算法题（可能是，只是我不知道），总体感觉就是思路比较难想，细节处理容易出错
所幸给了三个样例，不然估计AC不了

本题对题目的理解和思路的构建建立在前一题的基础上
所谓序列查询问题：
    给定一个序列A = [A0,A1,A2,...,An]，是由n+1个[0, N)的整数组成的序列，并且升序排列
    查询任务就是给定[0, N)的x，f(x)代表A中小于等于x的最大整数下标
    第一个任务即求sum(A) = f(0) + f(1) + ... + f(N-1)
    
    如果直接循环逐个去算f(i)的话，不仅算f(i)本身费劲，O(N)的循环也不太愉快

    我们应该以A当中的元素为主体计算，也就是对A进行循环  O(n)的复杂度：
        对于A[i](i<n)，实际上对于所有的A[i]<=x<A[i+1], f(x)=i
        因此ans += (A[i+1] - A[i]) * i 

    这样第一题就解决了

再看序列查询新解这道题
具体的题目背景我就不描述了，直接描述需要解决的问题:
    对于0,1,2...,N-1这N个数，前文已述他们有相应的f(i)
    现在，对于每个i，可以计算一个函数值g(i):
        r = N / (n+1)  g(i) = i / r
    现在需要计算|f(i) - g(i)|的总和

    对N个数for循环的话是不可能的，N的量级是1e9
    应该仍然是从A[i]出发
    看样例:
    A = [0,2,5,8]
    r = N / n+1 = 2
    i     0  1  2  3  4  5  6  7  8  9
    f(i)  0  0  1  1  1  2  2  2  3  3
    g(i)  0  0  1  1  2  2  3  3  4  4

    可以看出一定的规律:
        对于i∈[A[i], A[i+1]), f(i) = i
        而g(i)则从0开始，每r个数+1

    我们同样是以A[i]~A[i+1]为整体进行考虑，计算其中的|f(i)-g(i)|
    可以注意到，f(i)是确定值
    同样g(i)也有r个相同值

    以i=1为例，A[1]=2,A[2]=5,考虑2、3、4这四个数的f、g
    f均为1
    g[2]=g[3]=1, g[4]=2

    理论上头和尾同一个g值的元素不一定有r个，但是中间是r个
    对于中间的r个元素的计算直接变成r*|g-f|  从O(r)->O(1)

    头尾具体观察即可

    最后的复杂度变成O(n* max(ΔA[i] / r)显然是可以接受的

    最后也就AC了
*/

#include<iostream>
#include<math.h>
using namespace std;
const int maxn = 1e5+1;
int A[maxn];
int main(){
    long long n;
    long long N;
    cin >> n >> N;
    A[0] = 0;
    long long r = N / (n + 1);
    long long f, g;

    for (int i = 1; i <= n; i++)
    {
        cin >> A[i];
    }

    long long ans = 0;

    for (int i = 0; i <= n; i++)
    {
        long long begin, end;
        if (i < n)
        {
            begin = A[i];
            end = A[i+1] - 1;
        }
        else
        {
            begin = A[i];
            end = N - 1;
        }
        long long f = i;
        long long g_begin = begin / r;
        long long g_end = end / r;
        //头尾应该单独计算
        long long begin_num = min((g_begin + 1) * r - 1, end) - begin + 1;
        ans += begin_num * abs(g_begin - f);
        for (int j = g_begin + 1; j < g_end; j++)
        {
            ans += abs(j - f) * r;
        }
        if (g_begin != g_end)
        {
            long long end_num = end - (g_end * r - 1);
            ans += end_num * abs(g_end - f);
        }
    }
    
    cout << ans << endl;

    return 0;
}