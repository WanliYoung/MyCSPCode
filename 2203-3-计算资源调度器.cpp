//CSP202203-3  计算资源调度器

/*
又是一道大模拟题。
个人感觉大模拟题其实不算难，基本不怎么涉及到算法的思想，
很多时候只要把题目信息梳理清楚，把对象和联系分析清楚，
按部就班地顺着题目捋下去就没问题。
但是大模拟题对STL的要求比较高，map、set、vector、sort一定要熟练使用，
比如一开始本题排序部分采用自己写的（最熟悉的冒泡排序），只能拿80%的分数，
换上sort之后就AC了。
其实我目前接触的CSP的模拟题暴力都可以AC，或者本身考察的也不是算法知识点，感觉主要是信息处理能力。

回到本题。其实题目描述的情景也不难（看似字数非常多）：
    有m个分区，把分区理解成一个计算机集群，每个分区包含若干计算节点；
    有n个计算节点，分布在m个集群中，每个计算节点属于且只属于一个分区；
    有一些计算任务需要发放到计算节点上：
        每个任务都有其所属的应用类型；
    题目描述的任务需求就是：
        给你一系列计算任务，你根据实时的分区和节点情况进行任务分配；
        而具体的分配要求不用非常清楚，对着文字敲条件就行
    
    所以关键就是创建好类和类间关系：
        Node类表示计算节点：
            所属分区；
            运行的任务类型；
            运行的任务数量；
        Area类表示分区：
            其中的节点列表；
            其中运行的任务类型；
        这样两个类就可以清楚描述当前数据中心的情况了。

        计算任务不需要具体创建，因为计算任务就是实时给你的，然后你判断加到哪个点上，加进去之后就不管了。

    一个关于g的for循环内嵌套一个关于f的for循环：
        对于每一个任务，
        依照题目条件依次判断那几个条件：
            无非就是要求在哪个分区，要和某类应用在一个分区，不能和某类应用在一个节点
        按部就班进行判断就好了

        判断完有一个结果列表需要排序：
            计算任务少的在前面；序号小的在前面
            注意，一开始这里没用sort，只能拿80分
            sort就AC了
    
    所以说还是耐心把题目梳理好就行，注意细节。
    虽然过程不算特别困难，但是我还是做了比较久，考场上AC恐怕还是很难。
*/

#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;

const int maxn = 1001;
const int maxm = 1001;

//节点结构体
struct Node
{
    int AreaNum;  //所属区域
    int TaskNum;  //计算任务数量
    vector<int> AppTypes;  //包含的应用类型
    Node(){
        TaskNum = 0;
    }
};
Node nodes[maxn];  //所有节点

//可用区结构体
struct Area
{
    vector<int> Nodes;  //包含的节点序号
    vector<int> AppTypes;  //包含的应用类型
};
Area areas[maxm];  //所有区域

bool find(int x, vector<int> arr)
{
    for(int i = 0; i < arr.size(); i++){
        if(x == arr[i]){
            return true;
        }
    }
    return false;
}

bool cmp(int i, int j)
{
    if (nodes[i].TaskNum < nodes[j].TaskNum)
    {
        return true;
    }
    else if (nodes[i].TaskNum == nodes[j].TaskNum)
    {
        if (i <= j)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else{
        return false;
    }
}

int main(){
    int n, m;  //节点数、区域数
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int area;
        cin >> area;
        nodes[i].AreaNum = area;
        areas[area].Nodes.push_back(i);  //互相联系
    }
    //节点和可用区都初始化完毕了，开始放入计算任务

    int g;
    cin >> g;
    for (int i = 1; i <= g; i++)
    {
        int f, na, pa, paa, paar;
        long long a;
        cin >> f >> a >> na >> pa >> paa >> paar;
        for (int j = 1; j <= f; j++)  //f个任务要一个一个来
        {
            vector<int> resultNodes;  //可用的计算节点

            //计算节点亲和性要求
            if (na != 0)  //要运行在可用区na的计算节点上
            {
                resultNodes = areas[na].Nodes;
            }
            else
            {
                for (int k = 1; k <= n; k++)
                {
                    resultNodes.push_back(k);  //全进去
                }
            }

            if (resultNodes.size() == 0)
            {
                cout << 0 << " ";
                continue;
            }
            

            //计算任务亲和性要求
            if (pa != 0)  //要和pa应用在一个可用区运行
            {
                //如果na!=0，就直接看区的应用就好了，不用一个一个check
                if (na != 0)
                {
                    if (!find(pa, areas[na].AppTypes))
                    {
                        cout<<0<<" ";
                        continue;
                    }
                }
                else
                {
                    resultNodes.clear();
                    //一个区一个区的来
                    for (int k = 1; k <= m; k++)
                    {
                        if (find(pa, areas[k].AppTypes))
                        {
                            for (int h = 0; h < areas[k].Nodes.size(); h++)
                            {
                                resultNodes.push_back(areas[k].Nodes[h]);
                            }   
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else
            {
                ;
            }

            if (resultNodes.size() == 0)
            {
                cout << 0 << " ";
                continue;
            }

            //计算任务反亲和性要求
            vector<int> temp = resultNodes;  //先记录下来，以免反亲和性删除光了还可以恢复
            if (paa != 0)  //不能和含pa应用的计算节点一起
            {
                for (int k = 0; k < resultNodes.size(); k++)
                {
                    if (find(paa, nodes[resultNodes[k]].AppTypes))
                    {
                        resultNodes.erase(resultNodes.begin() + k);  //不能一起工作
                        k--;
                    }
                }
            }
            else
            {
                ;
            }
            
            //看看会不会删光了
            if (resultNodes.size() == 0 && paar)  //删光了,一定满足，没余地了
            {
                cout << 0 << " ";
                continue;  //直接下一个计算任务
            }
            else if (resultNodes.size() == 0 && !paar) //删光了，并且还是尽量满足
            {
                if (paa == 0)
                {
                    cout << 0 << " ";
                    continue;
                }
                else
                {
                    resultNodes = temp;  //用没反亲和性的
                    if (resultNodes.size() == 0)
                    {
                        cout << 0 << " ";
                        continue;
                    }
                }
            }
            
            //没有删光，过滤结束，进入排序阶段
            sort(resultNodes.begin(), resultNodes.end() , cmp);
            cout << resultNodes[0] << " ";  //输出第一个就好
            nodes[resultNodes[0]].TaskNum++;
            nodes[resultNodes[0]].AppTypes.push_back(a);
            areas[nodes[resultNodes[0]].AreaNum].AppTypes.push_back(a);
        }
        cout << endl;
    }
    return 0;
}