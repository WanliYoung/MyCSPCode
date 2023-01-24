#include<iostream>
using namespace std;
struct times
{
    int number;
    int times;
};
int main(){
    int n;
    cin>>n;
    int* s = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin>>s[i];
    }
    times* t = new times[n];
    for (int i = 0; i < n; i++)
    {
        t[i].number = 0;
        t[i].times = 0;
    }
    int t_index = 0;
    for (int i = 0; i < n; i++)
    {
        int flag = false;
        for (int j = 0; j < n; j++)
        {
            if(s[i] == t[j].number){
                t[j].times += 1;
                flag = true;
                break;
            }
        }   
        if(!flag){
            t[t_index].number = s[i];
            t[t_index].times += 1;
            t_index++;
        }
    }
    int max_times_num;
    int max_times = 0;
    for (int i = 0; i < n; i++)
    {
        if (t[i].times == max_times)
        {
            if (t[i].number < max_times_num)
            {
                max_times_num = t[i].number;
            }
        }
        else if(t[i].times > max_times){
            max_times_num = t[i].number;
            max_times = t[i].times;
        }
    }
    cout<<max_times_num<<endl;
    return 0;
}