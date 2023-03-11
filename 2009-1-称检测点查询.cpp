#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
const int maxn = 200;
struct Position
{
    int dis;
    int index;
};
Position positions[maxn];  //距离的平方
bool cmp(Position i, Position j)
{
    return ((i.dis < j.dis) || (i.dis == j.dis && i.index <= j.index));
}
int main() {
    int n, x, y;
    cin >> n >> x >> y;
    int xi, yi;
    for (int i = 0; i < n; i++)
    {
        cin >> xi >> yi;
        positions[i].dis = pow((x - xi), 2) + pow((y - yi), 2);
        positions[i].index = i + 1;
    }
    sort(positions, positions+n, cmp);
    for (int i = 0; i < 3; i++)
    {
        cout << positions[i].index << endl;
    }
    return 0;
}