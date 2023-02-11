//CSP201512-2  消除类游戏

/*
这道题暴力解就可以了。
对于n*m的棋盘，每一个都有1~9的数字代表不同颜色的棋子，
同一行或者同一列连续三个及以上相同数字就都消除为0，
题目特别强调了行列同时消除的可能性。
所以就决定用暴力直接逐行逐列地去找，
初始化board[n][m]代表棋盘，if_del[n][m]对应棋盘上每个点是否删除：
    ifdel[i][j] == 1代表需要消除，反之代表不消除（这样可以处理重合的情况）
逐行判断：
    每一行从第1列开始，到第m-2列结束，每次都连着判断后续的三位数，如果都相同，就把if_del置为1
    就算是大于3个的连续情况也可以正常处理
    时间复杂度O(n*m)
逐列判断与上相似
最后根据if_del的数值决定输出0还是原始数值
完成。
*/
#include<iostream>
using namespace std;
int main(){
    int n, m;
    cin >> n >> m;  // 棋盘的行列数
    int** board = new int* [n + 1];
    bool** if_del = new bool* [n + 1];
    for (int i = 1; i <= n; i++)
    {
        board[i] = new int [m + 1];
        if_del[i] = new bool [m + 1];
        for (int j = 1; j <= m; j++)
        {
            cin >> board[i][j];
            if_del[i][j] = 0;
        }
    }

    //棋盘初始化完毕之后开始消除
    //感觉还是直接暴力好了
    //先看行
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m-2; j++)
        {
            if(board[i][j] == board[i][j+1] && board[i][j] == board[i][j+2])
            if_del[i][j] = if_del[i][j+1] = if_del[i][j+2] = 1;
        }
    }
    //再看列
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n-2; j++)
        {
            if(board[j][i] == board[j+1][i] && board[j][i] == board[j+2][i])
            if_del[j][i] = if_del[j+1][i] = if_del[j+2][i] = 1;
        }
    }

    //最后执行删除
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if(if_del[i][j])
            {
                cout<<0<<" ";
            }
            else
            {
                cout<<board[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    return 0;
}