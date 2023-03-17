/*
就不写题解了，反正逐渐把问题拆解，一步一步来
化学方程式->表达式=表达式
表达式->化学式+化学式......
化学式->数字、元素、括号

其实难点就在于括号，尤其是括号的嵌套，其实有点像算术表达式
用栈来处理括号问题
遇到(及之后的元素就入栈
遇到)就一直算，直到(
如果栈不是空的，还得装回去
如果栈空了，就放到结果当中
*/
#include<iostream>
#include<cstring>
#include<map>
#include<stack>
using namespace std;
int n;  //化学方程式数量
string S;  //输入的化学方程式

struct YS  //化学元素
{
    string ys;
    long long num;

    YS()
    {
        
    }
    YS(string ys, long long num)
    {
        ys = ys;
        num = num;
    }
};
YS touse[1000000];
int to_use_ptr = 0;


//已经把问题拆解为单个化学式的计算了
void calcHXS(string hxs, map<string, long long>& result)  //计算化学式
{
    int num = 0;  //最前面的系数
    int i = 0;
    if (hxs[i] >= '1' && hxs[i] <= '9')  //看看是不是数字开头
    {
        //数字开头还得处理一下，毕竟不一定只有一位
        while (hxs[i] >= '0' && hxs[i] <= '9')
        {
            num *= 10;
            num += hxs[i] - '0';
            i++;
        }
    }
    else
    {
        num = 1;  //默认1
    }

    //不管怎么样，i都指向了具体元素
    stack<YS> p;  //用栈来解决
    bool flag = false;  //标识是不是在括号内
    string ys;
    while (i < hxs.size())
    {
        ys = "";
        if (hxs[i] == '(')  //压栈
        {
            touse[to_use_ptr].ys = '(';  //左括号
            p.push(touse[to_use_ptr]);
            i++;
            to_use_ptr++;
            flag = true;
        }
        else if (hxs[i] >= 'A' && hxs[i] <= 'Z')
        {
            ys += hxs[i];
            if (!flag)  //不在括号内，自由身
            {
                if (hxs[i+1] >= 'a' && hxs[i+1] <= 'z')  //紧跟着小写
                {
                    ys += hxs[i+1];
                    i++;
                }
                i++;
                //统一处理
                int number = 0;
                if (hxs[i] >= '1' && hxs[i] <= '9')  //后面跟着数字，可以结算了
                {
                    while (hxs[i] >= '0' && hxs[i] <= '9')
                    {
                        number *= 10;
                        number += hxs[i] - '0';
                        i++;
                    }
                }
                else if (hxs[i] == '\0')  //已经是末尾了
                {
                    number = 1;
                }
                else if (hxs[i] >= 'A' && hxs[i] <= 'Z')  //新的元素
                {
                    number = 1;
                }
                else if (hxs[i] == '(') 
                {
                    number = 1;
                }
                //直接往map里放了
                result[ys] += num * number;  //如果有就是+，如果没有也会创建
            }
            
            //如果前面有(，说明不是自由身的话，那就找到截止点然后入栈，但是括号里面可能也有数字哦
            else
            {
                //其实大部分情况和前面是一样的
                if (hxs[i+1] >= 'a' && hxs[i+1] <= 'z')  //紧跟着小写
                {
                    ys += hxs[i+1];
                    i++;
                }
                i++;
                //统一处理
                long long number = 0;
                if (hxs[i] >= '1' && hxs[i] <= '9')  //后面跟着数字，可以结算了
                {
                    while (hxs[i] >= '0' && hxs[i] <= '9')
                    {
                        number *= 10;
                        number += hxs[i] - '0';
                        i++;
                    }
                }
                else if (hxs[i] == '\0')  //已经是末尾了
                {
                    number = 1;
                }
                else if (hxs[i] >= 'A' && hxs[i] <= 'Z')  //新的元素
                {
                    number = 1;
                }
                else if (hxs[i] == ')') 
                {
                    number = 1;
                }
                else if (hxs[i] == '(')
                {
                    number = 1;
                }
                touse[to_use_ptr].ys = ys;
                touse[to_use_ptr].num = number;
                
                p.push(touse[to_use_ptr]);  //先压入栈中
                to_use_ptr++;
            }
        }
        else if (hxs[i] == ')')  //要对栈中元素进行结算了
        {
            //先看看这个组合有多少个
            i++;
            long long knum = 0; //组合的数量
            if (hxs[i] >= '1' && hxs[i] <= '9')  //后面跟着数字，可以结算了
            {
                while (hxs[i] >= '0' && hxs[i] <= '9')
                {
                    knum *= 10;
                    knum += hxs[i] - '0';
                    i++;
                }
            }
            else
            {
                knum = 1;
            }
            //为了避免多层嵌套，拿一个栈来装
            stack<YS> tmp_p;  //临时栈
            YS t;
            //开始出栈吧
            while (p.top().ys != "(")
            {
                touse[to_use_ptr] = p.top();
                touse[to_use_ptr].num = p.top().num * knum;
                tmp_p.push(touse[to_use_ptr]);  //弹出来就装进去
                p.pop();
                to_use_ptr++;
            }
            p.pop();
            //如果此时栈不是空的
            if (!p.empty())  //说明还有（
            {
                //装回去
                while (!tmp_p.empty())
                {
                    touse[to_use_ptr] = tmp_p.top();
                    p.push(touse[to_use_ptr]);
                    tmp_p.pop();
                    to_use_ptr++;
                }
            }
            else  //栈空了，说明处理完了，把tmp_p处理就行
            {
                flag = false;
                while (!tmp_p.empty())
                {
                    t = tmp_p.top();
                    result[t.ys] += t.num * num;
                    tmp_p.pop();
                }
            }
        }
    }
    

}

map<string, long long> calcExp(string ex)  //计算表达式，n是表达式元素数目
{
    map<string, long long> result;
    string tmp = "";
    for (int i = 0; i < ex.size(); i++)
    {
        if (ex[i] != '+')
        {
            tmp += ex[i];
        }
        else
        {
            calcHXS(tmp, result);  //放进去计算一下
            tmp = "";
        }
    }
    //最后还差一个化学式没有计算
    calcHXS(tmp, result); 
    return result;
}

void judgeEqual(string S)  //判断方程式是否配平
{
    //先把方程式根据=划分为左右两个表达式
    string ex1 = "", ex2 = "";
    //先找到=
    int equalIndex;
    for (int i = 0; i < S.size(); i++)
    {
        if (S[i] == '=')
        {
            equalIndex = i;
            break;
        }
    }
    for (int i = 0; i < equalIndex; i++)
    {
        ex1 += S[i];
    }
    for (int i = equalIndex+1; i < S.size(); i++)
    {
        ex2 += S[i];
    }

    map<string, long long> l, r;  //包含什么元素，元素有多少个
    l = calcExp(ex1);
    r = calcExp(ex2);

    //看看两个map是否相等
    if (l == r)
    {
        cout << "Y" << endl;
    }
    else
    {
        cout << "N" << endl;
    }
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> S;
        judgeEqual(S);
    }
}