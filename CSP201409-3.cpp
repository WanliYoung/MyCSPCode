//CSP201409-3  字符串匹配
/*
总体思路不难，归根结底还是看一个字符串是否包含另一个字符串：
    所以只需要逐位放入小字符串就好了
    再增加对于大小写是否敏感的判断，是否敏感对应不同的匹配方式
*/
#include<iostream>
#include<string>
using namespace std;
int ifInclude(string S, string cinS, int ifsen){
    if (cinS.size() < S.size())
    {
        return false;
    }
    else{
        for (int i = 0; i <= cinS.size() - S.size(); i++)
        {
            int j = 0;
            if(ifsen){  //大小写敏感
                while(S[j] != '\0' && cinS[i + j] == S[j]){
                    j++;
                }
            }
            else{  //大小写不敏感  a 97 A 65 差32
                while(S[j] != '\0' && (cinS[i+j] == S[j] || (cinS[i+j]+32) == S[j] || (cinS[i+j]-32) == S[j])){
                    j++;
                }
            }
            if (j == S.size())
            {
                return true;
            }
        }
    }
    return false;
}
int main(){
    string S;
    cin >> S;  //输入字符串
    int ifsen;  //大小写敏感的选项，0表示不敏感，1表示敏感
    cin >> ifsen;
    int n;  //行数
    cin >> n;
    string* cinS = new string[n];  //输入的文字
    int* ifinclude = new int[n];  //是否包含该字符串
    for (int i = 0; i < n; i++)
    {
        cin >> cinS[i];
        ifinclude[i] = ifInclude(S, cinS[i], ifsen);
    }
    for (int i = 0; i < n; i++)
    {
        if (ifinclude[i])
        {
            cout<<cinS[i]<<endl;
        }   
    }
    return 0;
}