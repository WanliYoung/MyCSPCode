#include<iostream>
using namespace std;
int main()
{
    int N;
    cin >> N;  //带着N元钱
    int five_num = N / 50;
    int five_left = N % 50;
    int three_num = five_left / 30;
    int three_left = five_left % 30;
    int num = three_left / 10;
    int ans = five_num * 7 + three_num * 4 + num;
    cout << ans;
    return 0;
}