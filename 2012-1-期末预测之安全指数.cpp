#include<iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    int sum = 0, w, score;
    for (int i = 1; i <= n; i++)
    {
        cin >> w >> score;
        sum += w * score;
    }
    int ans = max(0, sum);
    cout << ans;
    return 0;
}