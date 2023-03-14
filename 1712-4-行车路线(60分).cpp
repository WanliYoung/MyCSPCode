#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int matrix[501][501];  
int djs(int num){
    int source = 1;
    int* dis = new int[num + 1];
    int* vis = new int[num + 1];
    for (int i = 1; i <= num; i++)
    {
        dis[i] = 100001;
        vis[i] = false;
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
        if (node == num)  //到2就好了
        {
            return dis[node];
        }
        //对邻接点进行松弛
        for (int j = 1; j <= num; j++)
        {
            dis[j] = min(dis[j], dis[node] + matrix[node][j]);
        }    
    }
    return dis[num];
}
int main()
{
    //如果不考虑小道，全是大道，那就是求最短路径，djk
    int n, m;
    cin >> n >> m;  //n个点，m条线
    //用邻接矩阵表示
    for (int i = 0; i < 501; i++)
    {
        for (int j = 0; j < 501; j++)
        {
            matrix[i][j] = 100001;  //表示不可达
        }
    }
    
    int t, a, b, c;
    for (int i = 0; i < m; i++)
    {
        cin >> t >> a >> b >> c;
        if (t == 0)  //大道
        {
            matrix[a][b] = c;  //邻接矩阵赋值
            matrix[b][a] = c;
        }
        else  //小道
        {
            matrix[a][b] = c*c;  //邻接矩阵赋值
            matrix[b][a] = c*c;
        }
    }
    
    cout << djs(n);

    return 0;
}