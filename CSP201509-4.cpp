//CSP201509-4  高速公路

/*
这题完全是参考别人的代码写的（甚至还理解了蛮久的）
有空再自己写一遍题解
这里放两个链接：
    CSDN：https://blog.csdn.net/weixin_43843835/article/details/88381828?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522167593492816800192243890%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=167593492816800192243890&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduend~default-2-88381828-null-null.142^v73^insert_down4,201^v4^add_ask,239^v1^insert_chatgpt&utm_term=%E6%B1%82%E5%BC%BA%E8%BF%9E%E9%80%9A%E5%88%86%E9%87%8Ftarjan%E7%AE%97%E6%B3%95&spm=1018.2226.3001.4187
    bilibili：https://www.bilibili.com/video/BV19J411J7AZ?p=5&vd_source=9d8000465f487fa8d1bdc7f47736df48
基本上这两个结合着看就可以理解了
*/
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<stack>
using namespace std;

const int maxn = 10001;  //点数
int index, num;  //顺序、强连通分量的数目
stack<int> s;  //栈
bool instack[maxn];
int dfn[maxn];
int low[maxn];

vector<int> edges[maxn];
vector<int> result[maxn];

void tarjan(int u){
    index++;
    dfn[u] = index;
    low[u] = index;
    instack[u] = true;
    s.push(u);
    for (int i = 0; i < edges[u].size(); i++)
    {
        int v = edges[u][i];
        if (!dfn[v])  // 完全没访问过
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(instack[v])  // 访问过，且在栈中
        {
            low[u] = min(low[u], low[v]);  //***注意这里哦***
        }
    }
    if (dfn[u] == low[u])  // 说明是连通分量的起点，弹到它为止
    {
        num++;
        int node;
        do
        {
            node = s.top();
            s.pop();
            result[num].push_back(node);
            instack[node] = false;
        } while (node != u);
    }   
}

int calc(int num){
    //根据强连通分量的节点数，计算互相可达点对
    return (num * (num - 1) / 2);
}

int main(){
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
    }

    index = 0, num = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(instack, false, sizeof(instack));

    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            tarjan(i);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= num; i++)
    {
        ans += calc(result[i].size());
    }
    
    cout << ans << endl;
    return 0;
}