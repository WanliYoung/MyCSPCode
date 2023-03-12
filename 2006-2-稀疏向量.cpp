//CSP202006-2  稀疏向量
/*
题目意思蛮简单的，总体来说就是计算两个同维度的稀疏向量的内积
其中稀疏向量采取更省内存的存储方式

一开始想到一个比较暴力的方法：
    每个维度对应一个状态，0代表没有数，1代表有一个数，2代表有2两个数
    遍历向量a，b：
        对于每个出现的向量索引index，其状态数+1
    最后只需要对状态数==2的维度进行计算就可以
    实际上感觉复杂度也不高
    但是维度最大可能是1e9，显然不可能用数组存储

题解：
其实这个题解的思路个人感觉有点像归并排序（其实我可能忘了归并怎么写了，但是还记得一些思想）：
    已知我们有两个向量u、v，以稀疏向量的形式存储：
        queue<tupple>, tupple={index, value}，并且按照index升序排序
        (为什么用queue存储，看例子就知道了)
    用实际例子模拟一下计算过程吧：
        对于10维向量u、v
        u = {(4,5), (7,-3), (10, 1)}
        v = {(1, 10), (4,20), (5,30), (7,40)}
        假设二者以queue存储
        首先pop出队列首部：(4,5) (1,10)
        显然不能计算内积，并且较大的index=4，那么v就应该不断地pop元素，直到出现index>=4的元素
        直到(4,5) (4,20)，ans = 100;
        这时候应该一起pop元素，得到(7,-3) (5,30)显然也不能计算
        较大的index=7，v仍然需要弹出直到index>=7
        得到(7,-3) (7,40) ans-=-120=20
        然后应该一起弹出，但是下一步v已经空了，没必要继续计算了
        输出最终结果-20

    简单来说：
        两个队列u、v，一起弹出队首元素，先比较index：
            状态1：u.index < v.index
                那么就应该记录此时的v.index，不断弹出u中元素，直到u.index >= v.index
            状态2：u.index > v.index
                那么就应该记录此时的u.index，不断弹出v中元素，直到v.index >= u.index
            状态3：u.index == v.index
                那么应该ans += u.value * v.value，并且u、v都要弹出元素
        不断地循环
        过程中一定要时时判断二者是否有人空了，空了就结束即可

    复杂度O(a + b)

    最终AC。
*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct tupple
{
    long long index;
    int value;
};
queue<tupple> u, v;

int main(){
    long long n;
    int a, b;
    cin >> n >> a >> b;
    long long index;
    int value;
    for (int i = 0; i < a; i++)
    {
        cin >> index >> value;
        u.push({index, value});
    }
    for (int i = 0; i < b; i++)
    {
        cin >> index >> value;
        v.push({index, value});
    }
    //开始计算内积
    long long ans = 0, ptr;
    int flag;
    tupple now_u = u.front(), now_v = v.front();
    u.pop();
    v.pop();
    if (now_u.index == now_v.index)
    {
        ans += now_u.value * now_v.value;
        flag = 3;
    }
    else
    {
        if (now_u.index < now_v.index)
        {
            ptr = now_v.index;
            flag = 1;  //表示u要继续吐
        }
        else
        {
            ptr = now_u.index;
            flag = 2;  //表示v要继续吐
        }
    }

    while (!u.empty() || !v.empty())
    {
        if (flag == 1)
        {
            //u不断吐
            while (now_u.index < ptr)  //直到等于或者超越
            {
                if (u.empty())  //u已经没了
                {
                    goto label;  //结束计算
                }
                //还有
                now_u = u.front();
                u.pop();
            }
            if (now_u.index == ptr)
            {
                //值得计算
                ans += now_u.value * now_v.value;
                //一起继续吐
                flag = 3;
            }
            else
            {
                //u已经超过v了，轮到v吐了
                flag = 2;
                ptr = now_u.index;
            }
        }
        else if (flag == 2)
        {
            //v不断吐
            while (now_v.index < ptr)  //直到等于或者超越
            {
                if (v.empty())  //v已经没了
                {
                    goto label;  //结束计算
                }
                //还有
                now_v = v.front();
                v.pop();
            }
            if (now_v.index == ptr)
            {
                //值得计算
                ans += now_u.value * now_v.value;
                //一起继续吐
                flag = 3;
            }
            else
            {
                //v已经超过u了，轮到u吐了
                flag = 1;
                ptr = now_v.index;
            }
        }
        else if (flag == 3)
        {
            //需要一起吐
            if (u.empty() || v.empty())
            {
                goto label;  //有一个空了就结束
            }
            else
            {
                now_u = u.front(), now_v = v.front();
                u.pop();
                v.pop();
                if (now_u.index == now_v.index)
                {
                    ans += now_u.value * now_v.value;
                    flag = 3;
                }
                else
                {
                    if (now_u.index < now_v.index)
                    {
                        ptr = now_v.index;
                        flag = 1;  //表示u要继续吐
                    }
                    else
                    {
                        ptr = now_u.index;
                        flag = 2;  //表示v要继续吐
                    }
                }
            }
        }
    }
label:
    cout << ans;

    return 0;
}