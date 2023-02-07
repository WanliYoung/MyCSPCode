//CSP202209-3  防疫大数据

/*
一道大模拟题：典型的题干信息量比较大，实际不需要什么算法思想，把题目内容捋清楚就好
题目大意：
    我们需要一个疫情风险检测系统；
    在连续的n天当中，每天的夜里都会输入：用户漫游信息、风险地区信息
    需要根据这些信息生成风险用户名单。

阅读题干之后可以了解到，我们其实就是需要维护两块信息：
    风险地区列表（存储若干地区，每个地区从哪天开始成为风险区，还有多少天时间）
    用户漫游信息表（每个用户去过哪些区域，最近一次去是什么时候）

根据每天输入的数据来更新这两块信息，并理利用最新的信息做出决策（生成风险用户列表）

需要两个结构体：
    DangerRegion存储地区信息，需要存储begin_d和left_d(初始化为-1，代表不是风险区)
    User存储用户信息，包括两个数字regions和date，对应某日到达某地区，同时需要存储到达地区数目number

需要注意，由于地区和用户数目都是1000000000量级的，数组无法存储，一定要使用**map**(因为虽然最多有这么多，但是不会同时出现)

所以就是进行n次的循环，模拟每天输入数据
先输入当天获取的风险地区，并且更新风险地区表；
再输入m行用户漫游信息，更新到访地区数组；

接着就是利用这两块信息做出决策生成风险用户名单了：
    遍历每一个出现的用户，判断ta是不是风险用户：
        对于每一个用户，逐个遍历ta去过的地区：
            如果使得该用户为风险用户，直接break；
            否则继续看下一个地区。

            至于判断条件，就按照题目叙述的那样写就行：
                首先u用户到r地区的时间d要在当天的7日内
                并且[d1, i]要被begin_day和end_day包裹

这样每天的风险用户就生成完毕了

但是一定要注意，要更新风险地区表，把left_d进行相应的缩减
*/

#include<iostream>
#include<map>
using namespace std;
struct DangerRegion  //危险地区
{
    int left_d;  //作为风险地区的剩余时间
    int begin_d;
    DangerRegion(){
        left_d = -1;  //代表不是风险地区
    }
};
map<long long, DangerRegion> drs;

struct User
{
    int regions[100000];  //去过的地区
    int date[100000];  //相应的日期
    int number;
    User(){
        number = 0;
    }
};
map<long long, User> users;

int main(){
    int n;  //天数
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        //输入每一天的数据
        int r, m;  //风险地数目、漫游数目
        cin >> r >> m;
        for (int j = 0; j < r; j++)
        {
            long long region;
            cin >> region;
            if (drs.count(region) == 0)
            {
                //没出现过
                DangerRegion dr;
                dr.begin_d = i;
                dr.left_d = 7;
                drs.insert(pair<long long, DangerRegion>(region, dr));
            }
            else{
                //出现过
                if (drs[region].left_d == -1)
                {
                    drs[region].begin_d = i;
                    drs[region].left_d = 7;
                }
                else{
                    drs[region].left_d = 7;  //续上日期
                }
            }
        }
        
        //输入用户数据
        for (int j = 0; j < m; j++)
        {
            long long d, u, r;
            cin >> d >> u >> r;
            if (users.count(u) == 0)
            {
                //没出现过
                User user;
                users.insert(pair<long long, User>(u, user));
            }
            int flag = false;  //表示是否记录去过地区r
            for (int k = 0; k < users[u].number; k++)
            {
                if (users[u].regions[k] == r)
                {
                    flag = true;
                    if (users[u].date[k] < d)
                    {
                        users[u].date[k] = d;
                    }
                    break;
                }
            }
            if(!flag){
                users[u].regions[users[u].number] = r;
                users[u].date[users[u].number] = d;
                users[u].number++;
            }
        }

        cout<<i<<" ";

        //开始生成风险用户名单
        map<long long, User>::iterator Iter;
        for(Iter = users.begin(); Iter != users.end(); Iter++){
            if (Iter->second.number == 0)  //哪都没去过
            {
                continue;
            }
            else{
                for (int k = 0; k < Iter->second.number; k++)
                {
                    if (Iter->second.date[k] <= i - 7)
                    {
                        continue;
                    }
                    else{
                        int d1 = Iter->second.date[k];
                        int d = i;
                        int begin_day = drs[Iter->second.regions[k]].begin_d;
                        int end_day = i + drs[Iter->second.regions[k]].left_d - 1;
                        if(begin_day <= d1 && end_day >= d){
                            cout<<Iter->first<<" ";
                            break;
                        }
                    }
                }
            }
        }

        cout<<endl;

        //所有的东西处理完要开始更新数据了

        map<long long, DangerRegion>::iterator iter;
        for(iter = drs.begin(); iter != drs.end(); iter++){
            if (iter->second.left_d != -1)
            {
                iter->second.left_d--;
            }
        }
    }
    return 0;
}