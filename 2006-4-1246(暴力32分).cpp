#include<iostream>
#include<math.h>
#include<cstring>
using namespace std;
int count(string S, string s)
{
    //s在S当中出现了几次
    int ans = 0;
    int len = s.size();
    if (len == 1)
    {
        for (int i = 0; i < S.size(); i++)
        {
            if (S[i] == s[0])
            {
                ans++;
            }
        } 
    }
    else
    {
        for (int i = 0; i < S.size() - len; i++)
        {
            int index = i;
            int s_index = 0;
            while (S[index] == s[s_index] && s_index != len)
            {
                index++;
                s_index++;
            }
            if (s_index == len)
            {
                ans++;
            }
            else{
                continue;
            }
        }
    }
    ans = ans % 998244353;
    return ans;
}
int main()
{
    int n;
    string S;
    cin >> n >> S;
    string s = "1";
    string tmp = "";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < s.size(); j++)
        {
            switch (s[j])
            {
            case '1':
                tmp.append("2");
                break;
            case '2':
                tmp.append("4");
                break;
            case '4':
                tmp.append("16");
                break;
            case '6':
                tmp.append("64");
                break;
            default:
                break;
            }
        }
        s = tmp;
        tmp = ""; 
    }
    cout << count(s, S);
    return 0;
}