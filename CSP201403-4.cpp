#include<iostream>
#include<math.h>
using namespace std;
const int inf = 256;  //超过这个数就说明不可达
struct position{
    long long x;
    long long y;
};
bool ifavai(position p1, position p2, long long r){
    double distance = sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
    if (distance <= 1.0 * r)
    {
        return true;
    }
    else{
        return false;
    }
}
//寻找当前的图顶点1到顶点2的最短距离
int djs(int** matrix, int num, int n, int k){
    int source = 1;
    int* dis = new int[num + 1];
    int* vis = new int[num + 1];
    int* sp_routers_num = new int [num + 1];
    for (int i = 1; i <= num; i++)
    {
        dis[i] = inf;
        vis[i] = false;
        sp_routers_num[i] = 0;
    }
    dis[source] = 0;
    for (int i = 1; i <= num-1; i++)
    {
        int node = -1;
        for (int j = 1; j <= num; j++)
        {
            if (!vis[j] && (node == -1 || dis[j] < dis[node]))
            {
                node = j;
            }
        }
        vis[node] = true;  //加入到集合当中
        if (node == 2)  //到2就好了
        {
            return dis[node];
        }
        //对邻接点进行松弛
        if (node > n)
        {
            for (int j = 1; j <= num; j++)
            {
                if (dis[j] > dis[node] + matrix[node][j])  //需要松弛
                {
                    if (sp_routers_num[j] < k)
                    {
                        dis[j] = dis[node] + matrix[node][j];
                        sp_routers_num[j]++;
                    }
                }
            }   
        }
        else{
            for (int j = 1; j <= num; j++)
            {
                dis[j] = min(dis[j], dis[node] + matrix[node][j]);
            }    
        }
    }
    return dis[2];
}
/*
1、掌握dijkstra算法的代码实现：
    输入邻接矩阵（代表图）和源点，返回源点到每个点的最短路径。
    需要维护两个数组
    dis（代表当前每个点到源点的最短距离，dis[source]=0，其余初始化为inf）
    和vis（代表每个点是否加入集合当中，初始化为false）。
    for循环（n-1）次，将n-1个点加入vis代表的集合即可：
        每一次循环先找到当前未访问过的距离最近的点作为node，
        接着对其邻接节点进行松弛。
    这样就实现了dijkstra算法。

2、本道题实际上是dijkstra算法的变式：
    输入n个已有的路由器和m个可以使用的路由器（最多选择其中的k个），寻找1到2的最短路径
    非常重要的思想就是假设所有的路由器都可以使用，进行dijkstra算法，搜索1到2的最短路径
    但是注意限制，需要维护一个新的数组sp_routers_num（代表每个点当前搜索到的最短路径使用的空闲路由器的数量，初始化为0）
    主要修改的就是松弛部分：
        如果当前的node是前n个确定的路由器，那么进行正常的松弛即可；
        如果是后m个可变的路由器，进行松弛时，一定要判断某个节点j用到的sp_routers_num[j]是否达到上限k：
            如果没有达到，就可以用它松弛，如果已经达到上限就需要用其他节点松弛了
*/
int main(){
    int n,m,k;
    long long r;
    cin>>n>>m>>k>>r;
    int all_pos_num = n + m;  //路由器的上限数目
    position* routers = new position[all_pos_num + 1];
    //已有的路由器1~n
    for (int i = 1; i <= n; i++)
    {
        cin>>routers[i].x>>routers[i].y;
    }
    //可添加的路由器n+1 ~ n+m
    for (int i = n + 1; i <= n + m; i++)
    {
        cin>>routers[i].x>>routers[i].y;
    }
    //假设所有路由器都可用
    int** matrix = new int* [all_pos_num + 1];
    for (int i = 1; i <= all_pos_num; i++)
    {
        matrix[i] = new int [all_pos_num];
    }
    for (int i = 1; i <= all_pos_num; i++)
    {
        for (int j = 1; j <= all_pos_num; j++)
        {
            if(ifavai(routers[i], routers[j], r)){ //路由器ij可达
                matrix[i][j] = 1;
            }
            else{
                matrix[i][j] = inf;
            }
        }   
    }
    int result = djs(matrix, all_pos_num, n, k);
    cout<<result - 1<<endl;
    return 0;
}