//CSP201503-3  节日

/*
这道题其实也没什么难度，其实最不想做的就是这种日期题了，顺着题目叙述写就行了，暴力解法
首先算1850到y年前的总天数，然后算1月1日到a月1日的天数
定位y年a月1日是星期几
接着就可以计算a月第b个星期c是几号，分为两种情况：
    1、c在1日的星期之后
    1、c在1日的星期之前
计算完输出就行了
*/
#include<iostream>
using namespace std;
bool ifrun(int year){
    if (year % 400 == 0)
    {
        return true;
    }
    else{
        if (year % 4 == 0 && year % 100 != 0)
        {
            return true;
        }
        else{
            return false;
        }
    }
}
int main(){
    int a, b, c, y1, y2;
    cin>>a>>b>>c>>y1>>y2;
    int year_num = 2050 - 1850 + 1;
    int* DayNumOfYear = new int[year_num];
    for (int i = 0; i < year_num; i++)
    {
        if (ifrun(i + 1850))
        {
            DayNumOfYear[i] = 366;
        }
        else{
            DayNumOfYear[i] = 365;
        }
    }
    for (int y = y1; y <= y2; y++)
    {
        int DayNumOfMonth[] = {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };
        if (ifrun(y))
        {
            DayNumOfMonth[1] += 1;
        }
        
        int daynum = 0;  //前面的那些年一共多少天
        for (int j = 1850; j < y; j++)
        {
            daynum += DayNumOfYear[j-1850];
        }
        for (int j = 0; j < a-1; j++)
        {
            daynum += DayNumOfMonth[j];
        }
        
        int leftday = daynum % 7;
        int dayof1_1 = 2 + leftday;  //y年a月的1号是星期几
        if(dayof1_1 > 7){
            dayof1_1 = dayof1_1 % 7;
        }
        //看第b个星期c和第1个星期d差几天
        int deltaday = 0;
        if (c >= dayof1_1)
        {
            deltaday += (b-1) * 7;
            deltaday += c - dayof1_1;
        }
        else{
            deltaday += 7 - dayof1_1 + 1;
            deltaday += (b-1) * 7;
            deltaday += c - 1;
        }
        int final_day = 1 + deltaday;
        if (final_day > DayNumOfMonth[a - 1])
        {
            cout<<"none"<<endl;
        }
        else{
            cout<<y<<"/";
            if (a < 10)
            {
                cout<<"0";
            }
            cout<<a<<"/";
            if (final_day < 10)
            {
                cout<<"0";
            }
            cout<<final_day<<endl;
        }  
    }
    return 0;
}