//CSP202206-2  寻宝！大冒险！

/*
这一题的要求比我想象中的简单，直接暴力做就满分了，提交之前一直以为暴力求解会超时，所以这再次提醒我了，在考场上先试试暴力能不能解再说
题目大意就是有一张非常大的地图（可能10^9*10^9级别），上面有n棵树；
有一张局部地图为藏宝图，其[0][0]位置一定是树的位置；
判断有几棵树可以作为藏宝图的[0][0]，并使得整个藏宝图与原始地图完全重合。
（感觉描述的不是特别清楚，看题也不难理解）
暴力的解法：
    1、首先就是对n棵树遍历，看是否满足条件  复杂度O(n)
    2、能否满足条件就看是否可以重合：
        从[0][0]到[S][S]进行循环，藏宝图的每个位置看其是否有树  复杂度O(S^2)
        并且根据原始图的[x+i][y+j]上是否有树进行对比  复杂度O(n)
        如果每个点都满足条件，说明这棵树ok；只要有一个点不满足，就直接return false。
综上，本道题的复杂度应该是O(n^2 * S^2)，非常暴力的解法。
所幸n<=10000,s<=50，所以可以AC。
这道题最大的数是L(10^9)，所以千万不能初始化整幅原始地图，一定要用n棵树代替。
*/
#include<iostream>
using namespace std;
struct Position
{
    int x;
    int y;
};
bool find(Position* trees, int n, Position p){
    for (int i = 0; i < n; i++)
    {
        if(trees[i].x == p.x && trees[i].y == p.y){
            return true;
        }
    }
    return false;
}
bool check(int treeIndex, Position* trees, int n, int** CanBaoTu, int S, int L){
    //判断第treeIndex棵树是否符合条件
    int x = trees[treeIndex].x;
    int y = trees[treeIndex].y;
    if (x > L-S || y > L-S)
    {
        //可以直接判断不符合条件
        return false;
    }
    for (int i = 0; i <= S; i++)
    {
        for (int j = 0; j <= S; j++)
        {
            int result = CanBaoTu[i][j];
            bool exist = find(trees, n, {x+i, y+j});
            if (result == 1 && exist)
            {
                continue;
            }
            else if (result == 0 && !exist)
            {
                continue;
            }
            else{
                return false;
            }
        }
    }
    return true;
}
int main(){
    int n, S;  //树的数量和藏宝图大小
    long long L;  //绿化图大小
    cin >> n >> L >> S;

    Position* trees = new Position[n];
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        trees[i].x = x;
        trees[i].y = y;
    }

    int** CanBaoTu = new int* [S + 1];
    for (int i = S; i >= 0; i--)
    {
        CanBaoTu[i] = new int [S + 1];
        for (int j = 0; j <= S; j++)
        {
            cin >> CanBaoTu[i][j];
        }
    }
    
    int result = 0;
    for (int i = 0; i < n; i++)
    {
        if (check(i, trees, n, CanBaoTu, S, L))
        {
            result++;
        }
    }
    
    cout << result;

    return 0;
}