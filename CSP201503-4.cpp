//CSP201503-4  网络延时

/*
首先这道题是为了迎合题意才提出电脑和交换机这两个概念的
实际上电脑和交换机都是节点，它们之间的连接就是边，总体构成一棵树
题目需要我们寻找的就是距离最长的节点对。
这道题自己一开始想了一个错误的解法，也记录一下错误的原因：
    对于一棵树，最远的距离一定在叶子节点之间产生（***这就是错误的结论）
    就对于叶子节点之间寻找距离的最大值就好了
    对于两个叶子节点，寻找距离：
        维护一个队列，每找一个父节点就往里面加，如果碰到相同的节点，那么就说明找到了中转
    双重循环搜索得到最大距离。

    这个思路一开始就错了，因为最大距离不一定是叶子到叶子，极端例子比如一脉相承，最后分了两个，其实是根下来最长

正解：
    实际上这是一个比较典型的问题——寻找树的直径（树的直径就是距离最长的节点对）
    需要引入一个定理：
        从树的任意一个节点出发，其最远的点一定是直径的端点。
    定理的证明就不细说了，网络上很多。主要思想是反证法，大体可以分为：
        出发点在直径上；
        出发点不在直径上，但是到最远点的路径和直径相交；
        出发点不在直径上，且到最远点的路径和直径不相交（但是一定能通过另一个路连接）
    有了定理作为支撑，
    整体的思路就是从任意一个点（根节点）出发BFS到最远的点u（BFS最后的点一定最远）
        第一次BFS不需要记录深度
    u一定是直径的一端，再从u开始BFS，一定会到直径另一端v
        第二次BFS要记录深度
    
    至于BFS具体如何实现就不写了，直接记录过了。
    大体就是用队列和两个数组vis、depth（dis）。
*/
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

const int maxn = 20000 + 5;
vector<int> G[maxn];
bool vis[maxn];
int depth[maxn];

int main(){
    //初始化
    memset(vis, false, sizeof(vis));
    memset(depth, 0, sizeof(depth));

    int n, m;  //交换机数目，电脑数目
    cin>>n>>m;

    for (int i = 2; i <= n + m; i++)
    {
        int father;
        cin >> father;  //i节点的父节点
        G[i].push_back(father);
        G[father].push_back(i);  //互相连接
    }

    queue<int> Q;

    //第一次BFS，从根节点开始，不需要统计距离，最后一个点就是最远的点
    Q.push(1);
    vis[1] = true;
    int now;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for (int i = 0; i < G[now].size(); i++)
        {
            //把与now相连的未访问过的节点加入队列
            if(vis[G[now][i]]){
                continue;
            }
            Q.push(G[now][i]);
            vis[G[now][i]] = true;
        }
    }

    //第一次BFS结束，此时Q空了，now是直径的端点
    memset(vis, false, sizeof(vis));
    Q.push(now);
    vis[now] = true;
    depth[now] = 0;
    while(!Q.empty()){
        now = Q.front();
        Q.pop();
        for (int i = 0; i < G[now].size(); i++)
        {
            //把与now相连的未访问过的节点加入队列
            if(vis[G[now][i]]){
                continue;
            }
            Q.push(G[now][i]);
            vis[G[now][i]] = true;
            depth[G[now][i]] = depth[now] + 1;
        }
    }
    
    cout<<depth[now]<<endl;
    return 0;
}