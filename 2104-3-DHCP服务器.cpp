/*
其实这道题在模拟题里面并不算难，因为做题的时间断断续续，思路也老是断，就不写整道题的题解了
这道题的得分过程:50->70->100
一开始只拿了50分：
    错误的原因很傻，因为REQ和DIS对于过期时间的设置是一样的，我在copy代码的时候漏掉了Tdef的情况，所以只有50分
70分版本1：
    第一次70分的报错是运行错误，那很显然就是数组越界了
    应该是报文ip的值超出了N，但是我明明做出了判断
    结果发现很傻逼地写错了判断条件if(ip < 1 && ip > N)，所以直接进入else了，就会越界，实际上是||
70分版本2：
    前面两个错误都比较傻逼，改过来也很容易，但是改完之后还是70分，显示错误
    这个bug找了很久
    最后发现是REQ报文的处理，在判断ip范围合理之后，应该判断其占用者为发送主机
    这一步其实很简单，直接看ip_client[ip] == sender，但是不知道为什么我第一遍写错了，写的很怪，就不写了

最后AC。
其实这道题完全顺着题目信息做就可以，给的信息足够丰富了
*/

#include<iostream>
#include<cstring>
using namespace std;
const long long maxN = 10005;
class Server
{
public:
    string name;
    long long ip_num;
    long long Tdef;  //默认过期时间长度
    long long Tmax, Tmin;  //过期时间长度上限、下限
    //需要维护的数据
    long long ip_state[maxN];  
    //地址的状态: 0()未分配、1(待分配)、2(占用)、3(过期)
    string ip_client[maxN];  //ip地址的占用者
    long long ip_overdue[maxN];  //ip的过期时刻

    Server(string name, long long ip_num, long long Tdef, long long Tmax, long long Tmin)
    {
        this->name = name;
        this->ip_num = ip_num;
        this->Tdef = Tdef;
        this->Tmax = Tmax;
        this->Tmin = Tmin;
        //相关数据初始化
        for (int i = 1; i <= this->ip_num; i++)
        {
            this->ip_state[i] = 0;
            this->ip_client[i] = "";
            this->ip_overdue[i] = 0;
        }
    }
};

int main(){
    long long N, Tdef, Tmax, Tmin;
    string H;
    cin >> N >> Tdef >> Tmax >> Tmin >> H;
    Server server(H, N, Tdef, Tmax, Tmin);  //初始化服务器
    string sender, receiver, type;
    long long t, ip, overdue_time;
    long long n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> t;  //报文接收时刻
        cin >> sender >> receiver >> type >> ip >> overdue_time;
        //根据接收到的报文进行相应地处理和设置
        //实际只会接收到DIS和REQ

        //还需要根据当前时间更新服务器的状态
        for (int j = 1; j <= server.ip_num; j++)
        {
            if (server.ip_overdue[j] <= t)
            {
                if (server.ip_state[j] == 1)
                {
                    server.ip_state[j] = 0;  //变为未分配
                    server.ip_client[j] = "";
                    server.ip_overdue[j] = 0;
                }
                else if (server.ip_state[j] == 2)
                {
                    server.ip_state[j] = 3;  //状态为过期
                    server.ip_overdue[j] = 0;
                }
            }
        }
        

        if (type == "DIS" && receiver == "*")
        {
            long long depart_ip;  //分配的ip
            bool if_occup = false; //是否有占用者为发送主机的ip
            bool if_no_occup = false;  //是否有状态为未分配的 IP 地址
            bool if_overdue = false;  //是否有状态为过期的 IP 地址
            for (int j = 1; j <= server.ip_num; j++)
            {
                if (server.ip_client[j] == sender && server.ip_state[j] != 0)
                {
                    depart_ip = j;
                    if_occup = true;
                    break;
                }
            }
            if (!if_occup)
            {
                for (int j = 1; j <= server.ip_num; j++)
                {
                    if (server.ip_state[j] == 0)  //未分配
                    {
                        depart_ip = j;
                        if_no_occup = true;
                        break;
                    }
                }
                if (!if_no_occup)
                {
                    for (int j = 1; j <= server.ip_num; j++)
                    {
                        if (server.ip_state[j] == 3)  //过期
                        {
                            depart_ip = j;
                            if_overdue = true;
                            break;
                        }
                    }
                    if (!if_overdue)
                    {
                        //都不满足，不处理该报文
                        continue;
                    }
                } 
            }
            //这时候有一个可以分配的ip
            server.ip_state[depart_ip] = 1;
            server.ip_client[depart_ip] = sender;
            if (overdue_time == 0)
            {
                server.ip_overdue[depart_ip] = t + server.Tdef;
            }
            else
            {
                long long time_len = overdue_time - t;  //过期时间
                if (time_len > server.Tmax)
                {
                    server.ip_overdue[depart_ip] = t + server.Tmax;
                }
                else if (time_len < server.Tmin)
                {
                    server.ip_overdue[depart_ip] = t + server.Tmin;
                }
                else
                {
                    server.ip_overdue[depart_ip] = overdue_time;
                }
            }
            //发送报文
            cout << server.name << " " << sender << " " << "OFR " << depart_ip << " " << server.ip_overdue[depart_ip] << endl;
        }
        else if (type == "REQ" && receiver != "*")
        {
            //先检查自己是不是接收主机
            if (server.name != receiver)  //不是接收主机
            {
                for (int j = 1; j <= server.ip_num; j++)
                {
                    if (server.ip_client[j] == sender && server.ip_state[j] == 1)
                    {
                            server.ip_state[j] = 0;
                            server.ip_client[j] = "";
                            server.ip_overdue[j] = 0;
                    }
                }
                continue;
            }
            else  //是接收主机
            {
                if (ip < 1 || ip > server.ip_num)
                {
                    //不在地址池内，发送NAK报文
                    cout << server.name << " " << sender << " " << "NAK " << ip << " " << 0 << endl;
                }
                else if (server.ip_client[ip] != sender)  //直接看占用者是不是它就好了
                {
                    cout << server.name << " " << sender << " " << "NAK " << ip << " " << 0 << endl;
                }
                else
                {
                    //需要进一步处理
                    server.ip_state[ip] = 2;
                    if (overdue_time == 0)
                    {
                        server.ip_overdue[ip] = t + server.Tdef;
                    }
                    else
                    {
                        long long time_len = overdue_time - t;  //过期时间
                        if (time_len > server.Tmax)
                        {
                            server.ip_overdue[ip] = t + server.Tmax;
                        }
                        else if (time_len < server.Tmin)
                        {
                            server.ip_overdue[ip] = t + server.Tmin;
                        }
                        else
                        {
                            server.ip_overdue[ip] = overdue_time;
                        }
                    }
                    //发送ACK报文
                    cout << server.name << " " << sender << " " << "ACK " << ip << " " << server.ip_overdue[ip] << endl;
                }
            }                                                                                     
        }
        else
        {
            ;
        }
    }
    
    return 0;
}