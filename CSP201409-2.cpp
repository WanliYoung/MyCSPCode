//CSP201409-2  画图
#include<iostream>
using namespace std;
int main(){
    int n;
    cin >> n;  //矩形的数目
    int matrix[100][100];  //整个坐标轴
    for (int i = 1; i <= 100; i++)
    {
        for (int j = 1; j <= 100; j++)
        {
            matrix[i][j] = 0;
        }
        
    }
    for (int i = 1; i <= n; i++)
    {
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        for (int j = x1+1; j <= x2; j++)
        {
            for (int k = y1+1; k <= y2; k++)
            {
                matrix[j][k] = 1;
            }
        }
    }
    int sum = 0;
    for (int i = 1; i <= 100; i++)
    {
        for (int j = 1; j <= 100; j++)
        {
            if(matrix[i][j] == 1){
                sum++;
            }
        }
        
    }
    cout<<sum<<endl;
    return 0;
}