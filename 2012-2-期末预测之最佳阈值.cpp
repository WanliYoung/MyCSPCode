#include<iostream>
using namespace std;
const int maxt = 1e8 + 2;
int b[maxt];  //差分数组
int main(){
    int m;
    cin >> m;
    int y, result;
    for (int i = 1; i <= m; i++)
    {
        cin >> y >> result;
        if (result)  //及格了
        {
            //0~y的阈值预测正确数都+1
            b[0]++;
            b[y+1]--;
        }
        else  //没及格
        {
            //y+1~maxt预测正确数+1
            b[y+1]++;
        }
    }
    //计算cnt数组
    int sum = b[0];
    int ans = 0, max_num = sum;
    for (int i = 1; i < maxt; i++) 
    {
        sum = sum + b[i];
        if (sum >= max_num)
        {
            ans = i;
            max_num = sum;
        }
    }
    cout << ans;
    return 0;
}