//CSP201412-3  集合竞价

/*
（这道题远比我自己想象当中的简单，这也提示我考试中不妨先按照简单的理解快速写一个答案交上去试试，这次就成功了）
本题大致可以拆分为三个部分：
    1、读取任意多行的记录，并进行相应的存储与处理：
        读取任意多行采用while(getline(cin, s))的形式，这样程序可以不断读取输入直到终止；
        对于读取的每一行s，可以转换为输入流stringstream  ss(s)，然后逐个输入字符串进行相应的处理；
        每一行记录都采用结构体Input进行存储，type区分三种记录的类型并且存储相应的信息，用if_valid标识记录是否有效；
        ***注意***
            这里其实我多想了，我认为取消这一动作应该具有连锁效应：
                比如说第1行是buy类记录，第3行的cancel 1，说明取消第1行的buy。
                但是第5行是cancel 3，那么就会取消3的取消效果，也就是，第1行又有效了。
            但是事实证明是我多想了，本道题没有这么复杂，所有的样例当中cancel的应该都是buy or sell。
    2、实现确定股价->统计成交量的函数：
        这一步实际上也不难，就是给定一个股价p0，确定该股价下的成交量
        遍历每一个记录，对于其中有效的、不为cancel的记录进行统计：
            对于buy订单，p>=po，则buy_num+=s；
            对于sell订单，p<=p0，则sell_num+=s；
        最后min(buy_num, sell_num)就是成交量了。
        这一步的复杂度是O(n)，实际上应该也没有办法改进，因为遍历每条记录是必须的。
    3、寻找使得成交量最大的股价：
        这一步其实也不难，只是一开始以为搜索最佳股价这一步会涉及什么算法思想。
        最开始的想法就是暴力，对于股价0.00到上限10000.00进行间隔为0.01的搜索，但是不确定时间会不会超限；
        不过另一个原因使我放弃了这个方案:
            float的存储似乎无法精确到0.01，比如说0.82 + 0.01肯等于0.8299999
            存储的精度控制并不像输出的精度控制那么简单（当然我觉得应该是可以实现的，只是没往这个方向拓展）
        ***于是提出了一个更好的方法：
            我们可以想象一个股价的一维坐标轴，从0开始，向+∞延申，每一个buy or sell的订单，根据股价坐落在坐标轴上，并存储了股数
            我们的暴力方法就是从0.00开始，以0.01为step，逐个点进行判断，左侧所有的sell与右侧所有的buy都可以累加，然后选出更小的那个作为结果
            事实上我们一定可以把最好的点移动到订单坐落的点上，这并不影响结果***（这是重点！）
            所以结果一定在订单的股价当中产生
            那么我们就只需要逐个尝试订单的股价就好了
            这一步复杂度是O(n)
    总的来说，本解法的时间复杂度是O(n2)，足够通过本题了。
*/
#include<iostream>
#include<string>
#include<bits/stdc++.h>
#include<string.h>
#include<iomanip>
using namespace std;
struct Input
{
    int type;       //0代表买，1代表卖，2代表取消
    float p;        //出价
    long long s;    //股数
    //int cancel_index;      //取消的行号
    bool if_valid;  //0代表不存在的订单或者取消的订单，1代表有效订单
    Input(){
        if_valid = 0;
    }
};
long long calc_num(float p0, Input* inputs, int input_index){  //计算成交量
    long long buy_num = 0, sell_num = 0;
    for (int i = 0; i < input_index; i++)
    {
        if(inputs[i].if_valid == 1){
            if(inputs[i].type != 2){
                if(inputs[i].type == 0){
                    //购买订单
                    if(inputs[i].p >= p0){
                        buy_num += inputs[i].s;
                    }
                }
                else{
                    //售卖订单
                    if(inputs[i].p <= p0){
                        sell_num += inputs[i].s;
                    }
                }
            }
        }
    }
    return min(buy_num, sell_num);
}
int main(){
    Input inputs[5001];
    int input_index = 0;
    string s;
    while(getline(cin, s)){
        stringstream ss(s);
        string token;
        ss >> token;
        if(token[0] == 'c'){  //代表cancel
            int cancel_index;
            ss >> cancel_index;
            //取消订单可能触发一系列的连锁取消行为
            //或者取消订单号码超出当前index
            inputs[input_index].type = 2;
            inputs[input_index].if_valid = 1;
            input_index++;
            inputs[cancel_index-1].if_valid = 0;
        }
        else{  //代表buy or sell
            if(token[0] == 'b'){
                inputs[input_index].type = 0;
                inputs[input_index].if_valid = 1;
                float p;
                long long s;
                ss >> p;
                ss >> s;
                inputs[input_index].p = p;
                inputs[input_index].s = s;
                input_index++;
            }
            else{
                inputs[input_index].type = 1;
                inputs[input_index].if_valid = 1;
                float p;
                long long s;
                ss >> p;
                ss >> s;
                inputs[input_index].p = p;
                inputs[input_index].s = s;
                input_index++;
            }
        }
    }

    float max_p;
    long long max_num = 0;  //最大成交量及其对应的股价
    for (int i = 0; i < input_index; i++)
    {
        if(inputs[i].if_valid == 1){
            if(inputs[i].type != 2){
                float p = inputs[i].p;
                long long tmp_num = calc_num(p, inputs, input_index);
                if(tmp_num > max_num){
                    max_num = tmp_num;
                    max_p = p;
                }
                else if(tmp_num == max_num){
                    max_p = max(p, max_p);
                }
            }
        }
    }
    cout<<fixed<<setprecision(2)<<max_p<<" "<<max_num<<endl;
    return 0;
}