#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int N, K;  //N间教室和钥匙，K个老师
const int maxN = 1001, maxK = 1001;
int box[maxN];  //表示钥匙盒子，索引index对应的元素为钥匙编号，0表示空

struct Task  //表示取钥匙的任务
{
    int w, s, c;  //编号、开始时间、结束时间
};
Task tasks[maxK];

bool cmp(Task t1, Task t2)
{
    return ((t1.s < t2.s) || (t1.s == t2.s && t1.w < t2.w));
}

struct Return
{
    int rtn_time;
    int id;
};
Return returns[maxK];

bool cmp_rtn(Return r1, Return r2)
{
    return ((r1.rtn_time < r2.rtn_time) || (r1.rtn_time == r2.rtn_time && r1.id < r2.id));
}


int main()
{
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        box[i] = i;  //初始时钥匙顺序排列
    }
    int rtn_time;
    for (int i = 1; i <= K; i++)
    {
        cin >> tasks[i].w >> tasks[i].s >> tasks[i].c;
        //可以直接记录下归还的计划
        returns[i].rtn_time = tasks[i].s + tasks[i].c;
        returns[i].id = tasks[i].w;
    }
    
    //首先按照取钥匙的时间排个序，时间相等的按照钥匙编号排序
    sort(tasks+1, tasks+K+1, cmp);
    //还钥匙也排个序
    sort(returns+1, returns+K+1, cmp_rtn);

    int ptrt = 1, ptrr = 1;  //借还的双指针
    int task_num = 0, return_num = 0;  //借还的数目

    while (task_num != K || return_num != K)  //只要任务没有处理完
    {
        while (task_num != K && (ptrr > K || tasks[ptrt].s < returns[ptrr].rtn_time))
        {
            //处理当前的借
            //得先找到钥匙
            for (int i = 1; i <= N; i++)
            {
                if (box[i] == tasks[ptrt].w)
                {
                    box[i] = 0;
                    break;
                }
            }
            //cout << "borrow: " << tasks[ptrt].w << endl;
            task_num++;
            ptrt++;
        }
        while (return_num != K && (ptrt > K || returns[ptrr].rtn_time <= tasks[ptrt].s))
        {
            //处理当前的还
            for (int i = 1; i <= N; i++)
            {
                if (box[i] == 0)
                {
                    box[i] = returns[ptrr].id;
                    break;
                }
            }
            //cout << "return: " << returns[ptrr].id << endl;
            return_num++;
            ptrr++;
        } 
    }

    for (int i = 1; i <= N; i++)
    {
        cout << box[i] << " ";
    }

    return 0;
}