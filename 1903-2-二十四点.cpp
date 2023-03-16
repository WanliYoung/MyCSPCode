#include<iostream>
#include<stack>
using namespace std;
void judge(string s)
{
    //给一个字符串判断是不是
    //只要维护一个数字栈就行，遇到+-就入栈，遇到x/就计算，减法转换为加法
    stack<int> p;  //数字栈
    int i = 0;
    while (i < 7)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            //数字直接压栈
            p.push(s[i] - '0');
            i++;
        }
        else if (s[i] == '+')
        {
            //加法忽略
            i++;
        }
        else if (s[i] == '-')
        {
            //减法变加法
            int num = s[i+1] - '0';
            num = -1 * num;
            p.push(num);
            i+=2;
        }
        else if (s[i] == 'x')
        {
            //乘法直接解决
            int num1 = p.top();  //出栈一个
            p.pop();
            int num2 = s[i+1] - '0';
            num1 = num1 * num2;
            p.push(num1);
            i+=2;
        }
        else if (s[i] == '/')
        {
            //除法直接解决
            int num1 = p.top();  //出栈一个
            p.pop();
            int num2 = s[i+1] - '0';
            num1 = num1 / num2;
            p.push(num1);
            i+=2;
        }
        else
        {
            ;
        }
    }
    
    //把栈清空
    int sum = 0, num;
    while (!p.empty())
    {
       num = p.top();
       p.pop();
       sum += num; 
    }
    if (sum == 24)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}
int main()
{
    int n;
    string s;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        judge(s);
    }
    return 0;
}