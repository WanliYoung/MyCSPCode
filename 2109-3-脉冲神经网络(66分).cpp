#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

const int maxT = 1e5, maxN = 1e3, maxS = 1e3, maxP = 1e3, maxD = 10;

struct TC  //突触
{
    int s;  //源
    int t;  //目标
    double w;  //脉冲强度
    int D;  //传播时间
    //应该负责传输
    vector<double> left_times;
};
TC tcs[maxS];

struct SJY  //神经元
{
    double v, u;  //变量
    double a, b, c, d;  //常量
    int mc_times = 0;
    double I;
    vector<int> in_tcs_id;
    vector<int> out_tcs_id;
};
SJY sjys[maxN];

struct MCY  //脉冲源
{
    int r;
    vector<int> out_tcs_id;
};
MCY mcys[maxP];

static unsigned long Next = 1;

int myrand(void) {
    Next = Next * 1103515245 + 12345;
    return ((unsigned)(Next/65536) % 32768);
}

int main(){
    int N, S, P, T;
    cin >> N >> S >> P >> T;
    double dt;  //时间间隔
    cin >> dt;
    int cin_num = 0;
    int RN;
    double v, u, a, b, c, d;
    while (cin_num < N)
    {
        cin >> RN;
        cin >> v >> u >> a >> b >> c >> d;
        for (int i = 0; i < RN; i++)
        {
            sjys[cin_num+i].v = v;
            sjys[cin_num+i].u = u;
            sjys[cin_num+i].a = a;
            sjys[cin_num+i].b = b;
            sjys[cin_num+i].c = c;
            sjys[cin_num+i].d = d;
        }
        cin_num += RN;
    }
    
    for (int i = 0; i < P; i++)
    {
        cin >> mcys[i].r;
    }

    for (int i = 0; i < S; i++)
    {
        cin >> tcs[i].s >> tcs[i].t >> tcs[i].w >> tcs[i].D;
        if (tcs[i].s < N)
        {
            sjys[tcs[i].s].out_tcs_id.push_back(i);
        }
        else
        {
            mcys[tcs[i].s - N].out_tcs_id.push_back(i);
        }
        sjys[tcs[i].t].in_tcs_id.push_back(i);
    }
    
    //输入完毕，神经元、脉冲源、突触均初始化完毕，接下来开始传播

    int now_rand;
    for (double t = dt; t <= T*dt; t+=dt)
    {
        //cout << "第" << t << "时刻: " << endl;
        if (t > dt)  //从第二轮开始要算传播时间了
        {
            for (int i = 0; i < S; i++)
            {
                for (int j = 0; j < tcs[i].left_times.size(); j++)
                {
                    tcs[i].left_times[j] -= 1;
                    //如果小于等于0说明这一轮到了，否则还在传播
                    //cout << "突触" << i << "脉冲" << j << "时间: " << tcs[i].left_times[j] << endl;
                }
            }
        }
    
        //cout<<now_rand<<endl;
        //看每个脉冲源是否发出脉冲
        for (int i = 0; i < P; i++)
        {
            now_rand = myrand();
            if (mcys[i].r > now_rand)
            {
                for (int j = 0; j < mcys[i].out_tcs_id.size(); j++)
                {
                    int tc_id = mcys[i].out_tcs_id[j];
                    tcs[tc_id].left_times.push_back(tcs[tc_id].D);
                    //cout << "脉冲源" << i << "通过突触" << tc_id << "向神经元" << tcs[tc_id].t << "发送强度" << tcs[tc_id].w << endl;
                }  
            }
        }

        //计算每个神经元的状态
        for (int i = 0; i < N; i++)
        {
            //先计算接受的强度
            double I = 0;
            //遍历连接突触
            for (int j = 0; j < sjys[i].in_tcs_id.size(); j++)
            {
                int tc_id = sjys[i].in_tcs_id[j];
                for (int k = 0; k < tcs[tc_id].left_times.size(); k++)
                {
                    if (tcs[tc_id].left_times[k] <= 0)
                    {
                        I += tcs[tc_id].w;
                        tcs[tc_id].left_times.erase(tcs[tc_id].left_times.begin());
                    }
                    else
                    {
                        break;
                    }
                }
            }
            //cout<<"神经元"<<i<<"接受强度"<<I<< " ";
            //计算完强度，开始更新数值
            double nu, nv;
            double u = sjys[i].u, v = sjys[i].v, a = sjys[i].a, b = sjys[i].b;
            nv = v + dt * (0.04 * v * v + 5 * v + 140 - u) + I;
            nu = u + dt * a * (b * v - u);
            //cout<<"神经元"<<i<<"新v"<<nv<<endl;
            //cout<<"神经元"<<i<<"新u"<<nu<<endl;
            if (nv >= 30)  //要发射脉冲
            {
                for (int j = 0; j < sjys[i].out_tcs_id.size(); j++)
                {
                    int tc_id = sjys[i].out_tcs_id[j];
                    tcs[tc_id].left_times.push_back(tcs[tc_id].D);
                    //cout << "神经元" << i << "通过突触" << tc_id << "向神经元" << tcs[tc_id].t << "发送强度" << tcs[tc_id].w << endl;
                }
                nv = sjys[i].c;
                nu = nu + sjys[i].d;
                sjys[i].mc_times++;
                //cout<<"神经元"<<i<<"新v"<<nv<<endl;
                //cout<<"神经元"<<i<<"新u"<<nu<<endl;
            }
            sjys[i].u = nu;
            sjys[i].v = nv;
        }
    }
    
    double max_v = sjys[0].v, min_v = sjys[0].v;
    int max_mc_times = sjys[0].mc_times, min_mc_times = sjys[0].mc_times;

    for (int i = 1; i < N; i++)
    {
        if (sjys[i].v > max_v)
        {
            max_v = sjys[i].v;
        }
        else if (sjys[i].v < min_v)
        {
            min_v = sjys[i].v;
        }
        if (sjys[i].mc_times > max_mc_times)
        {
            max_mc_times = sjys[i].mc_times;
        }
        else if (sjys[i].mc_times < min_mc_times)
        {
            min_mc_times = sjys[i].mc_times;
        }
    }
    
    cout << fixed << setprecision(3) << min_v << " " << max_v << endl;
    cout << min_mc_times << " "<< max_mc_times;


    return 0;
}