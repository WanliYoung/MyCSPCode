#include<iostream>
#include<string>
using namespace std;
int main(){
    string s;
    cin>>s;
    int* a = new int[9];
    a[0] = s[0] - 48;
    for (int i = 2; i <= 4; i++)
    {
        a[i-1] = s[i] - 48;
    }
    for (int i = 6; i <= 10; i++)
    {
        a[i-2] = s[i] - 48;
    }
    int sum = 0;
    for (int i = 0; i <= 8; i++)
    {
        sum += (i + 1) * a[i];
    }
    int code = sum % 11;
    char cinCode = s[12];
    char comCode;
    if(code < 10){
        comCode = code + 48;
    }
    else{
        comCode = 'X';
    }
    if (cinCode == comCode)
    {
        cout<<"Right"<<endl;
    }
    else{
        s[12] = comCode;
        cout<<s<<endl;
    }
    
    return 0;
}