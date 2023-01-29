#include<iostream>
#include<queue>
using namespace std;
struct position
{
    int x;
    int y;
};
const int max_size = 1001;  //方格图的最大大小
bool if_visited[max_size][max_size];  //每个点是否访问过，0/1
int if_available[max_size][max_size];  //每个点是否可达以及当点的餐量大小，0代表普通点，-1代表禁止点，>0代表客户点
int dis[max_size][max_size];  //每个点的最近距离

/*
这道题本质上考察的是BFS（宽度优先搜索）思想，但是有一些奇妙的转换其实很难一下子想到。
分析题目容易知道：
    方格图上有一些店、有一些客户、有一些禁止通行的点；
    我们希望配送成本最低化；
    因此对于每个客户，我们都应该选择距离最近的分店进行配送；
    因此问题的核心其实就是在一个有禁止点的方格图当中，两点之间的最短距离（没有阻碍最小距离恒为Δx + Δy）；
    有禁止点怎么做呢？采用BFS：
        首先需要维护一些二维数组代表每个点的信息：
            if_availabel数组代表该点是普通点（0）还是客户点（>0）还是禁止点（-1）；
            if_visited数组代表该点是否已经被访问过（0/1），该点第一次被访问时就标记上，这样避免重复访问，也保持了距离最小。
            （很重要的思想是，第一次访问的时候更新的距离一定是最小的）；
            dis数组代表店铺到该点的最小距离。
        首先将分店的点设为visited，并且dis为0，加入队列q；
        接着开始搜索：
            彻底抛弃一个点前要先进行结算：result += 餐量*距离
            接着进行四个方向的尝试，如果在图中且不是禁止点且没有访问过，就可以加入队列
            直至搜索完毕
这样大体的思路是完成了，但是时间复杂度是很爆炸的，因为每个店和每个客户之间要进行一次全方格图的BFS搜索。
实际上我们可以同时进行扩散。也就是在最开始时把所有的店家的店加入q当中，同时开始BFS，这样进行一次全图搜索，就可以把所有需求解决，时间复杂度就可以接受了

本道题的关键在于想到BFS方法，以及想到多个店家同时开始搜索的思路。非常巧妙！
*/

int main(){
    int n;  //方格图大小
    int m;  //分店数量
    int k;  //客户数量
    int d;  //禁止点数量
    cin >> n >> m >> k >> d;

    //地图初始化
    for (int i = 0; i < max_size; i++)
    {
        for (int j = 0; j < max_size; j++)
        {
            if_visited[i][j] = false;
            if_available[i][j] = 0;
            dis[i][j] = 0;
        }
    }
    
    int a, b, c;
    long long result = 0;
    queue<position> q;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        q.push({a, b});
        if_visited[a][b] = true;
    }
    for (int i = 0; i < k; i++)
    {
        cin >> a >> b >> c;
        if_available[a][b] += c;
    }
    for (int i = 0; i < d; i++)
    {
        cin >> a >> b;
        if_available[a][b] = -1;
    }

    //开始BFS，可以抽象地理解地图上的蔓延
    while(!q.empty()){
        position p = q.front();
        q.pop();
        //先结算
        if (if_available[p.x][p.y] > 0)
        {
            result += if_available[p.x][p.y] * dis[p.x][p.y];
        }
        //向四个方向扩散
        for (int i = 0; i < 4; i++)
        {
            int x = p.x + dx[i];
            int y = p.y + dy[i];
            if (x>=1 && x<=n && y>=1 && y<=n && if_available[x][y] >=0 && !if_visited[x][y])
            {
                if_visited[x][y] = true;
                dis[x][y] = dis[p.x][p.y] + 1;
                q.push({x, y});
            }
        }
    }

    cout<<result<<endl;
    return 0;
}