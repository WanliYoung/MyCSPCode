//惯例先上暴力
//我靠，暴力就AC了，再次感悟：
//上来先用暴力，AC最好，没AC也能保一部分分数，最次的情况也深入理解题目意思了

/*
题目大意：
    有n个坐标(x, y)，代表该处有垃圾
    坐标不重复，且x, y要用long long表示
    我们需要考虑建立回收站：
        回收站必须在垃圾点当中产生
        垃圾点上下左右四个位置必须有垃圾才能作为候选回收站
        对于候选回收站：
            根据其四个对角上有x处垃圾赋x分(0~4)
    最后输出0~4分对应的垃圾点数目

简单的想法：
    其实简单的想法是存储一个全局的地图
    (x, y)处有垃圾就在(x, y)上置1
    判断的时候直接根据坐标上的数值判断有没有垃圾
    这种方法是空间换时间
    查询时间复杂度O(1)
    但是存储空间复杂度O(max * max)
    注意坐标轴绝对值数量级1e9，根本存储不了
    所以只能用时间换空间

暴力题解：
    输入n个坐标，只存储这n个坐标
    遍历n个坐标：  O(n)
        对于每个坐标(x, y)
        先判断其上下左右四个点是否有垃圾：
            采用的办法是去存储垃圾点的容器里找有没有符合坐标的元素
            复杂度O(n)
        如果不满足，直接下一个
        如果满足，开始评分
        同样判断对角四个点是否有垃圾，有一处就+1  复杂度O(n)
        对于候选节点，放入一个新的容器
    遍历候选容器: O(n)
        对于每个节点，在其score对应的数组下标上+1

    最后输出结果即可。

    最终复杂度O(n^2)，n最大是1000，可以接受
*/
#include<iostream>
#include<vector>
using namespace std;
const int maxn = 1001;
int n;
struct Position
{
    long long x, y;
    int score;
    Position(){
        score = 0;
    }
};
Position positions[maxn];
vector<Position> wl;  //候选列表
bool myfind(int x, int y)
{
    for (int i = 1; i <= n; i++)
    {
        if ((positions[i].x == x) && (positions[i].y == y))
        {
            return true;
        }
    }
    return false;
}
int score_num[5];
int main()
{
    cin >> n;  //垃圾点个数
    for (int i = 1; i <= n; i++)
    {
        cin >> positions[i].x >> positions[i].y;
    }
    int x, y;
    //开始计算
    for (int i = 1; i <= n; i++)
    {
        x = positions[i].x;
        y = positions[i].y;
        if (myfind(x, y+1)&&myfind(x, y-1)&&myfind(x-1, y)&&myfind(x+1, y))
        {
            //计算四个对角有几处存在垃圾
            if (myfind(x-1, y-1))
            {
                positions[i].score++;
            }
            if (myfind(x-1, y+1))
            {
                positions[i].score++;
            }
            if (myfind(x+1, y-1))
            {
                positions[i].score++;
            }
            if (myfind(x+1, y+1))
            {
                positions[i].score++;
            }
            wl.push_back(positions[i]);
        }
    }
    for (int i = 0; i < wl.size(); i++)
    {
        score_num[wl[i].score]++;
    }
    for (int i = 0; i < 5; i++)
    {
        cout << score_num[i] << endl;
    }
    return 0;
}