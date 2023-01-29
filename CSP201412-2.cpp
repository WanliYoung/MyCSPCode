//CSP201412-2  Z字形扫描
/*
其实这题就是找规律和技巧，没什么算法知识可言。
最初读题的时候有点被欺骗到，以为输出数时和图中画的Z字形一样，
一会要向水平方向走，一会要向对角线走，一会斜向上，一会斜向下，
感觉非常复杂，似乎需要很多临界判断。
其实不然。
我们可以把输出数想象成矩阵逐个把元素吐出的过程。
其实就是一排又一排对角线吐出元素，从以对角线为单位的角度看就很清晰了。
总共是2*n-1个对角线，每个对角线上元素坐标和又是一致的，从0到2*n-2。
可以观察到奇数排的对角线是斜向下（Δx=1，Δy=-1）；
偶数排的对角线是斜向上（Δx=-1，Δy=1）；
所以递进的差值我们也找到了。
接下来就是确定起始点的坐标了，需要考虑两个分界条件：
    1、奇数排还是偶数排；
    2、序号是否小于n
    总共会分出四种情况
确定了起始点和递进规律，只需要确保输出的点一定位与方阵当中即可
*/
#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int** matrix = new int*[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin>>matrix[i][j];
        }
    }
    cout<<matrix[0][0]<<" ";
    if(n != 1){
        for (int i = 1; i <= 2*n-3; i++)
        {
            int x, y, delx, dely, mod;
            mod = i % 2;  //1代表奇数，0代表偶数
            delx = (-2) * (1-mod) + 1;  //奇数1，偶数-1
            dely = (-2) * mod + 1;  //奇数-1，偶数1
            if (mod == 1)
            {
                //奇数次
                if(i < n){
                    //从(0, i)到(i, 0)
                    x = 0;
                    y = i-x;
                }
                else{
                    y = n-1;
                    x = i-y;
                }
            }
            else{
                //偶数次
                if(i < n){
                    y = 0;
                    x = i-y;
                }
                else{
                    x = n-1;
                    y = i-x;
                }
            }
            while (x>=0 && x<n && y>=0 && y<n)
            {
                cout<<matrix[x][y]<<" ";
                x += delx;
                y += dely;
            } 
        }
        cout<<matrix[n-1][n-1]<<endl;
    }
    return 0;
}