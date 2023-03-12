#include<iostream>
using namespace std;
struct Node
{
    int x, y;  //坐标
    char type;  //类别
};
const int maxn = 1001;
Node nodes[maxn];
int n, m;

bool query(int t0, int t1, int t2){
    //直线是否能完美分割所有点
    int first = t0 + t1 * nodes[1].x + t2 * nodes[1].y;  
    char flagz, flagf;  //表示大于0的类的名称
    if (first > 0)
    {
        flagz = nodes[1].type;
        if (flagz == 'A')
        {
            flagf = 'B';
        }
        else
        {
            flagf = 'A';
        }
    }
    else
    {
        if (nodes[1].type == 'A')
        {
            flagz = 'B';
            flagf = 'A';
        }
        else
        {
            flagz = 'A';
            flagf = 'B';
        }
    }
    int value;
    for (int i = 2; i <= n; i++)
    {
        value = t0 + t1 * nodes[i].x + t2 * nodes[i].y;
        if (value > 0 && flagz == nodes[i].type)
        {
            continue;
        }
        else if (value < 0 && flagf == nodes[i].type)
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

int main(){
    cin >> n >> m;  //点数和查询数目
    for (int i = 1; i <= n; i++)
    {
        cin >> nodes[i].x >> nodes[i].y >> nodes[i].type; 
    }
    int t0, t1, t2;
    for (int i = 0; i < m; i++)
    {
        cin >> t0 >> t1 >> t2;
        if (query(t0, t1, t2))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}