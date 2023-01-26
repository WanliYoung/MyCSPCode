#include<iostream>
#include<string>
#include<string.h>
#include <bits/stdc++.h>
using namespace std;
struct option
{
    char name;
    bool ifargs = false;
    string args;
};
void sort_ops(option* ops, int op_num){
    for (int i = 0; i < op_num - 1; i++)
    {
        for (int j = op_num - 1; j > i ; j--)
        {
            if (ops[j].name < ops[j-1].name)
            {
                option tmp = ops[j];
                ops[j] = ops[j-1];
                ops[j-1] = tmp;
            }
        }
    }
}
char forop[20*128][128];
int forop_index = 0;
int main(){
    //处理选项
    string format;
    getline(cin, format);
    option* op = new option[64];
    int option_num = 0;
    int i = 0;
    while (format[i] != '\0')
    {
        if(format[i] != ':' && format[i+1] != ':'){  //说明是不带参数的选项
            op[option_num].name = format[i];
            option_num++;
        }else if(format[i] != ':' && format[i+1] == ':'){  //说明是带参数的选项
            op[option_num].name = format[i];
            op[option_num].ifargs = true;
            option_num++;
        }
        //其他一律略过
        i++;
    }
    //处理输入的命令行 
    int N;
    cin>>N;  //命令行个数
    cin.ignore();  //非常重要，清除未消除的\n
    char const *split = " ";
    string s;
    for (int k = 1; k <= N; k++)
    {
        option com_op[128];
        int com_op_num = 0;
        string t;
        getline(cin, s);
        stringstream ss(s);
        ss >> t;
        while (ss >> t)
        {
            string tt;
            if(t.length() == 2){
                if(t[0] == '-'){
                    int find_flag = false;
                    for (int i = 0; i < option_num; i++)
                    {
                        if(op[i].name == t[1]){
                            find_flag = true;
                            //看看是不是出现过
                            int com_flag = false;
                            for (int j = 0; j < com_op_num; j++)
                            {
                                if(com_op[j].name == t[1]){
                                    com_flag = true;
                                    if(com_op[j].ifargs){
                                        if (ss.eof())
                                            goto break_label;
                                        ss >> tt;
                                        com_op[j].args = tt;
                                    }
                                    break;
                                }
                            }
                            if(!com_flag){
                                if(op[i].ifargs){
                                    if (ss.eof())
                                        goto break_label;
                                }
                                com_op[com_op_num] = op[i];
                                if(com_op[com_op_num].ifargs == true){
                                    ss >> tt;
                                    com_op[com_op_num].args = tt;
                                }
                                com_op_num++;
                            }
                            break;
                        }
                    }
                    if(!find_flag){
                        
                        break;
                    }
                }
                else{
                    break;
                }
            }
            else{
                break;
            }
        }
        break_label:
        cout<<"Case "<<k<<":";
        //升序输出选项
        sort_ops(com_op, com_op_num);
        for (int i = 0; i < com_op_num; i++)
        {
            cout<<" -"<<com_op[i].name;
            if (com_op[i].ifargs)
            {
                cout<<" "<<com_op[i].args;
            }
        }
        cout<<endl; 
    }
    return 0;
}