//CSP201512-3  画图

/*
这题看起来蛮复杂的，其实并不会，只不过开屏一张ACSII码的"CSPRO"有点唬人。
本题我维护两个二维数组，char_board[][]和flag_board[][]，分别存储画布上的字符和判断该位置是否有线段。
主要就是分别实现两个操作———画线段和填充：
    1、画线段：
        画线段比较简单，就根据是x1==x2还是y1==y2，选择是-还是|，用for循环画上
        需要在flag_board上标记
        需要注意的是如果在画|的时候遇到了-或者在画-的时候遇到了|，都需要改成+
        还有很容易错的一点：
            ***如果位置本身是+就别动了，之前犯了错误写成了覆盖，导致只能拿到90分***
    2、填充：
        其实填充这里给的提示非常明显了，就是向四个方向扩展，如果遇到边缘或者线段就停止
        实际上就是bfs可以做（如果不这样提示，只是说填充，恐怕我就想不到bfs了）
        bfs在CSP当中十分常见（这里只是增加一些判断条件），不再赘述
for循环操作上述两个操作就完成了画图
最后输出的时候注意，这里的坐标轴是从左下角开始的，而不是左上角，输出需要注意。
*/

#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct position{
    int x;
    int y;
};

const int maxm = 101, maxn = 101;
int char_board[maxm][maxn];  // 画布
bool flag_board[maxm][maxn]; // 是否有线段

int main(){
    int m, n, q;
    cin >> m >> n >> q;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char_board[i][j] = '.';
            flag_board[i][j] = false;
        }
    }

    int flag;
    for (int i = 0; i < q; i++)
    {
        cin >> flag;
        if (flag == 0)  // 划线操作
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            char c;
            if (x1 == x2)
            {
                c = '|';
                int begin = min(y1, y2);
                int end = max(y1, y2);
                for (int j = begin; j <= end; j++)
                {
                    if (char_board[x1][j] == '-')
                    {
                        char_board[x1][j] = '+';
                    }
                    else if (char_board[x1][j] == '+')
                    {
                        ;
                    }
                    else
                    {
                        char_board[x1][j] = c;
                    }
                    flag_board[x1][j] = true;
                }
            }
            else
            {
                c = '-';
                int begin = min(x1, x2);
                int end = max(x1, x2);
                for (int j = begin; j <= end; j++)
                {
                    if (char_board[j][y1] == '|')
                    {
                        char_board[j][y1] = '+';
                    }
                    else if (char_board[j][y1] == '+')
                    {
                        ;
                    }
                    else
                    {
                        char_board[j][y1] = c;
                    }
                    flag_board[j][y1] = true;
                }
            }
        }
        else  // 填充操作
        {
            int x, y;
            cin >> x >> y;
            char c;
            cin >> c;
            // 其实就是个BFS
            queue<position> q;
            bool vis[maxm][maxn];
            for (int j = 0; j < maxm; j++)
            {
                for (int k = 0; k < maxn; k++)
                {
                    vis[j][k] = false;
                }
            }
            int dx[] = {1, -1, 0, 0};
            int dy[] = {0, 0, 1, -1};

            q.push({x, y});
            vis[x][y] = true;
            char_board[x][y] = c;
            while (!q.empty())
            {
                position now = q.front();
                q.pop();
                for (int j = 0; j < 4; j++)
                {
                    int tmp_x = now.x + dx[j];
                    int tmp_y = now.y + dy[j];
                    if (tmp_x >= 0 && tmp_x < m && tmp_y >=0 && tmp_y < n && !flag_board[tmp_x][tmp_y] && !vis[tmp_x][tmp_y])
                    {
                        q.push({tmp_x, tmp_y});
                        vis[tmp_x][tmp_y] = true;
                        char_board[tmp_x][tmp_y] = c;
                    }
                }
            }
        }
    }

    for (int j = n-1; j >= 0; j--)
    {
        for (int i = 0; i < m; i++)
        {
            cout << (char)char_board[i][j];
        }
        cout<<endl;
    }
    
    
    return 0;
}