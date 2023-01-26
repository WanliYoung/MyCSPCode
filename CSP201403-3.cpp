#include<iostream>
#include<string>
#include<string.h>
using namespace std;
struct option
{
    char name;
    bool ifargs = false;
    char* args = NULL;
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
    for (int k = 1; k <= N; k++)
    {
        char cmd[256];
        cin.getline(cmd, 256);
        char* token;
        token = strtok(cmd, split);
        token = strtok(NULL, split);
        bool need_args = false;
        option* last_op_ptr;
        option com_op[128];
        int com_op_num = 0;
        while (token != NULL)
        {
            if(token[0] == '-'){  //有可能是选项
                char option = token[1];
                int flag = false;  //先假设不是选项
                for (int i = 0; i < option_num; i++)
                {
                    if(op[i].name == option){  //是已有的选项
                        //考虑当前是不是需要参数而非选项
                        if (need_args == true)
                        {
                            goto label;
                        }
                        int com_flag = false;  //有没有出现过
                        for (int j = 0; j < com_op_num; j++)
                        {
                            if(com_op[j].name == option){
                                com_flag = true;
                                if(com_op[j].ifargs == true){
                                    //出现过，需要参数
                                    need_args = true;
                                    last_op_ptr = &com_op[j];
                                }else{
                                    //出现过，不需要参数
                                    need_args = false;
                                }
                                break;
                            }
                        }
                        if(!com_flag){  //此前没有出现过
                            com_op[com_op_num] = op[i];
                            need_args = com_op[com_op_num].ifargs;
                            if(com_op[com_op_num].ifargs == true){  //需要参数
                                last_op_ptr = &com_op[com_op_num];
                            }
                            com_op_num++;
                        }
                        flag = true;
                        break;
                    }
                }
                if(!flag){  //不是选项，作为参数
                    goto label;
                }
            }else{  //一定是参数
                label:
                if (!need_args)
                {  //不需要参数
                    goto break_label;
                }else{  //需要参数
                    //更新参数
                    char tmp[128];
                    int t = 0;
                    while (token[t] != '\0')
                    {
                        tmp[t] = token[t];
                        t++;
                    }
                    tmp[t] = '\0';
                    last_op_ptr->args = tmp;
                }
                need_args = false;
            }
            token = strtok(NULL, split);
        }
        if(need_args){
            com_op_num--;
        }
        break_label:
        cout<<"Case "<<k<<":";
        //升序输出选项
        sort_ops(com_op, com_op_num);
        for (int i = 0; i < com_op_num; i++)
        {
            cout<<" -"<<com_op[i].name;
            if (com_op[i].ifargs && com_op[i].args != NULL)
            {
                cout<<" "<<com_op[i].args;
            }
        }
        cout<<endl;
    }
    return 0;
}