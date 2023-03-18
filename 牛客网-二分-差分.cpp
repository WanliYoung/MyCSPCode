#include<iostream>
#include<map>
using namespace std;
const int maxn = 9000000;
map<int, int> m;
int b[maxn];  //差分数组
map<int, int> a;
int main()
{
    int n;
    cin >> n;
    int num;
    char c;
    for(int i = 1; i <= n; i++)
    {
        cin >> num >> c;
        if(c == '.')
        {
            //猜到答案了
            m[num] += 1;
            m[num+1] -= 1;
            //b[num] += 1;
            //b[num+1] -= 1;
        }
        else
        {
            if(c == '+')
            {
                //数字比答案大
                m[0] += 1;
                m[num] -= 1;
                //b[0] += 1;
                //b[num] -= 1;
            }
            else if(c == '-')
            {
                //数字比答案小
                m[num+1] += 1;
                //b[num] += 1;
            }
        }
    }
    //还原数组
    a[0] = m[0];
    int max_time = a[0];
    map<int, int>::iterator it;
    int last_index = 0;
    for(it = m.begin(); it != m.end(); it++)
    {
        if(it->first == 0){
            continue;
        }
        a[it->first] = a[last_index] + it->second;
        if(a[it->first] > max_time)
        {
            max_time = a[it->first];
        }
        last_index = it->first;
    }
    cout << max_time;
    return 0;
}