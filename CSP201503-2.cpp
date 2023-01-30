#include<iostream>
using namespace std;
struct CountNum
{
    int number;
    int times;
    //构造函数
    CountNum(){
        number = -1;
        times = 0;
    }
};
void mySort(CountNum* c_num, int n){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = n-1; j > i; j--)
        {
            if (c_num[j-1].times < c_num[j].times)
            {
                CountNum tmp;
                tmp = c_num[j];
                c_num[j] = c_num[j-1];
                c_num[j-1] = tmp;
            }
            else if(c_num[j-1].times == c_num[j].times){
                if (c_num[j-1].number > c_num[j].number)
                {
                    CountNum tmp;
                    tmp = c_num[j];
                    c_num[j] = c_num[j-1];
                    c_num[j-1] = tmp;
                }
            }
        }
    }
}
/*
这题非常简单，也没什么算法可言
直接按照题目写就是了
现在的T2应该没这么简单了
最近晚上没剩什么时间，只能写简单题了
*/
int main(){
    int n;
    cin>>n;
    int* cin_num = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin>>cin_num[i];
    }
    CountNum* c_num = new CountNum[n];
    int com_num = 0;
    for (int i = 0; i < n; i++)
    {
        int flag = false;
        for (int j = 0; j < com_num; j++)
        {
            if (c_num[j].number == cin_num[i])
            {
                c_num[j].times++;
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            c_num[com_num].number = cin_num[i];
            c_num[com_num].times++;
            com_num++;
        }
    }
    mySort(c_num, com_num);
    for (int i = 0; i < com_num; i++)
    {
        cout<<c_num[i].number<<" "<<c_num[i].times<<endl;
    }
    return 0;
}