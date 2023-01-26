#include<iostream>
using namespace std;
struct windows
{
    int x1;
    int y1;
    int x2;
    int y2;
};
struct click
{
    int x;
    int y;
};
bool ifin(windows w, click c){
    if(w.x1 <= c.x && w.x2 >= c.x && w.y1 <= c.y && w.y2 >= c.y){
        return true;
    }else{
        return false;
    }
}
int main(){
    int N, M;
    cin>>N>>M;
    windows* w = new windows[N + 1];
    for (int i = 1; i <= N; i++)
    {
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        w[i].x1 = x1;
        w[i].y1 = y1;
        w[i].x2 = x2;
        w[i].y2 = y2;
    }
    click* c = new click[M + 1];
    for (int i = 1; i <= M; i++)
    {
        int x,y;
        cin>>x>>y;
        c[i].x = x;
        c[i].y = y;
    }
    int* rank = new int [N + 1];
    for (int i = 1; i <= N; i++)
    {
        rank[i] = N - i + 1;
    }
    for (int i = 1; i <= M; i++)
    {
        int x,y;
        x = c[i].x;
        y = c[i].y;
        int flag = false;
        for (int j = 1; j <= N; j++)
        {
            if(ifin(w[rank[j]], c[i])){
                cout<<rank[j]<<endl;
                int tmp = rank[j];
                for (int k= j; k > 1; k--)
                {
                    rank[k] = rank[k-1];
                }
                rank[1] = tmp;
                flag = true;
                break;
            }
        }
        if (!flag)
        {
            cout<<"IGNORED"<<endl;
        }
    }
    return 0;
}