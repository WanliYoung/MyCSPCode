//CSP201412-4  最优灌溉

/*
这道题应该比较好联想到连通图构建最小生成树：
    有n个麦田，其中第1个麦田有水源，麦田之间用水渠连接就可以通水，麦田可以作为中转点
    给m个可以修建的水渠（及其费用），选择最小的修渠费用使得所有麦田得到灌溉
    其实n个麦田对应n个点，水渠对应m条边，构建最小生成树使得连通
那么问题就是如何实现最小生成树了，我们采用Kruskal算法（贪心的思想）：
    先把m条边按照权重从小到大进行排序；
    逐个取出边，若加入该边不会使得图中出现环路，则加入该边；
    直到图中边的数目达到n-1条，则形成最小生成树。
1、边的排序：
    这个比较好办，采用各种排序都可以，但是要注意时间复杂度，O(m2)的复杂度会时间超限
2、逐个取出边看是否可以加入，难点在于如何判断是否会成环，所以采用***并查集***：
    并查集首先要维护一个大小为n的数组father，father[i]表示节点i的父节点
    实现一个函数find_father，其功能是寻找给定节点的根节点：
        如果某个节点的father是自己，那么它就是根节点，返回之
        否则，就不是根节点，就递归调用find_father(father[node])
    再实现一个函数unite，功能是判断两个节点是否可以合并：
        首先找到node1和node2对应的根节点father1、father2
        如果father1 == father2，说明二者属于同一根节点下，那么可以通过根节点作为中转连接，此时如果加入边，那么就会成环，返回false
        反之，说明两个节点对应的支系独立，那么可以加入边进行合并：
            father[father1] = father2;
            同时返回true

    逐个取出边，通过unite边的两点进行判断，如果是true则edge_num++, result+=x
        反之跳过该边
    直到edge_num == n
    打印result
*/
#include<iostream>
#include<algorithm>
using namespace std;

struct edge
{
    int a;
    int b;
    int c;
};
class Kruskal{
public:
    int* father;

    Kruskal(int n){
        father = new int[n + 1];
        for (int i = 1; i <= n; i++)
        {
            father[i] = i;
        }
    }
    int find_father(int node){
        if (father[node] == node)  //自己就是自己的father，说明是根节点了
        {
            return node;
        }
        else{
            return find_father(father[node]);
        }
    }
    bool unite(int node1, int node2){
        int father1 = find_father(node1);
        int father2 = find_father(node2);
        if (father1 == father2)
        {
            //说明已经连接了
            return false;
        }
        else{
            father[father1] = father2;
            return true;
        }
    }
};
bool compare(edge a, edge b){
    return a.c < b.c;
}
int main(){
    int n, m;  //麦田的片数和可以建立的水渠数量
    cin>>n>>m;
    edge* edges = new edge[m];
    for (int i = 0; i < m; i++)
    {
        cin>>edges[i].a>>edges[i].b>>edges[i].c;
    }
    
    //用Kruskal建立最小生成树
    sort(edges, edges+m, compare);
    Kruskal kr(n);
    int edge_num = 0;
    int result = 0;
    for (int i = 0; i < m; i++)
    {
        if (edge_num == n-1)
        {
            break;
        }
        if(kr.unite(edges[i].a, edges[i].b)){
            edge_num += 1;
            result += edges[i].c;
        }
    }
    cout<<result<<endl;
    return 0;
}