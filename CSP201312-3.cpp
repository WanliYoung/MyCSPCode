//其实就是暴力列举了所有矩形的面积
#include<iostream>
using namespace std;
int minH(int* arr, int begin, int end){
    int minh = arr[begin];
    for (int i = begin + 1; i <= end; i++)
    {
        if (arr[i] < minh)
        {
            minh = arr[i];
        } 
    }
    return minh;
}
int main(){
    int n;
    cin>>n;  //矩形数量
    int* h = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin>>h[i];  //各个矩形的高度
    }
    //计算最大的矩形面积
    int maxS = 0;
    for (int i = 1; i <= n; i++)  //矩形的宽度
    {
        for (int j = 0; j <= n-i; j++)
        {
            int minh = minH(h, j, j+i-1);
            int s = i * minh;
            if (s > maxS)
            {
                maxS = s;
            }
        }
    }
    cout<<maxS<<endl;
    return 0;
}