#include<iostream>
using namespace std;
const int maxL = 256;
int cnt[maxL];
int main(){
    int n, m, L;
    cin >> n >> m >> L;
    int x;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> x;
            cnt[x]++;
        }
    }
    for (int i = 0; i < L; i++)
    {
        cout << cnt[i] << " ";
    } 
    return 0;
}