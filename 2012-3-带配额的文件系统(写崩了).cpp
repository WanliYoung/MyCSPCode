#include<iostream>
#include<vector>
#include<cstring>
#include<iomanip>
using namespace std;
class Directory;

struct File
{
    Directory* parent;
    string name;
    int size;
};

class Directory
{
public:
    string name;
    Directory* parent;  //唯一的双亲目录
    vector<Directory*> childrenD;  //孩子目录
    vector<File*> childrenF;  //孩子文件
    int LDd;  //目录配额
    int LRd;  //后代配额
    int self_size;  //自己包含的文件大小之和
    int child_size;  //后代文件大小之和
    Directory(){
        parent = NULL;
        LDd = 0;
        LRd = 0;
        self_size = 0;
        child_size = 0;
    }
};

vector<string> extrFilePath(string file_path)  //拆分路径
{
    vector<string> result;
    int i = 1;  //直接从1开始判断吧，毕竟0是/
    string tmp = "";
    string store = "";
    if (file_path[i] == '\0')
    {
        return result;
    }
    
    while (file_path[i] != '\0')
    {   
        if (file_path[i] == '/')
        {
            result.push_back(store);
            store = "";
        }
        else
        {
            tmp = file_path[i];
            store.append(tmp);  //追加
        }
        i++;
    }
    result.push_back(store);  
    
    return result;
}

Directory usable[1000];  //可以使用的
int index;
File fusable[1000];
int findex;

int main(){
    //初始化
    index = 0;
    findex = 0;
    Directory root;  //根目录
    int n;
    cin >> n;
    char cmd_type;
    string file_path;
    int file_size, LD, LR;
    vector<string> files;
    string file_name;
    for (int i = 0; i < n; i++)
    {
        cin >> cmd_type;  //命令类型: C、R、Q
        if (cmd_type == 'C')
        {
            cin >> file_path >> file_size;
            files = extrFilePath(file_path);
            Directory* tmp = &root;  //指向root
            for (int j = 0; j < files.size() - 1; j++)
            {
                //看看有没有重名目录
                bool Dflag = false;  //假设没有
                for (int k = 0; k < tmp->childrenD.size(); k++)
                {
                    if (files[j] == tmp->childrenD[k]->name)
                    {
                        Dflag = true;
                        tmp = tmp->childrenD[k];  //更换
                        break;
                    }
                }
                if (!Dflag)  //没有找到
                {
                    //看有没有重名文件
                    for (int k = 0; k < tmp->childrenF.size(); k++)
                    {
                        //cout << tmp->childrenF[k]->name << endl;
                        if (files[j] == tmp->childrenF[k]->name)
                        {
                            //cout << "this1" << endl;
                            //有重名普通文件，直接失败
                            cout << "N" << endl;
                            goto label;  //直接结束本命令
                        }
                    }
                    //说明没有重名普通文件,那就创建
                    usable[index].name = files[j];
                    usable[index].parent = tmp;  //和父亲建立联系
                    tmp->childrenD.push_back(&usable[index]);  //加入孩子节点当中
                    tmp = &usable[index];  //更换
                    index++;
                }
            }
            //循环结束，tmp已经是最底层的目录了
            file_name = files[files.size()-1];
            //看看有没有现存目录
            for (int j = 0; j < tmp->childrenD.size(); j++)
            {
                if (tmp->childrenD[j]->name == file_name)
                {
                    //cout << "this2" << endl;
                    cout << "N" << endl;
                    goto label;
                }
            }
            //说明没有相同的目录
            //看看有没有相同的文件
            bool Fflag = false;
            for (int j = 0; j < tmp->childrenF.size(); j++)
            {
                if (tmp->childrenF[j]->name == file_name)
                {
                    //有相同的文件则改大小
                    //注意目录的额度也会变
                    file_size = file_size - tmp->childrenF[j]->size;
                    //cout << "child_size" << tmp->child_size << endl;
                    //cout << "need - " << tmp->childrenF[j]->size << endl;
                    int tmp_size = tmp->childrenF[j]->size;
                    //tmp->child_size -= tmp_size;
                    //tmp->self_size -= tmp_size;
                    //cout << "child_size" << tmp->child_size << endl;
                    //tmp->childrenF[j]->size = file_size;
                    //tmp->child_size += tmp->childrenF[j]->size;
                    //tmp->self_size += tmp->childrenF[j]->size;
                    //cout << "child_size" << tmp->child_size << endl;
                    Fflag = true;
                    break;
                }
            }
            if (!Fflag)  //没找到
            {
                tmp->childrenF.push_back(&fusable[index]);
                fusable[index].size = file_size;
                fusable[index].name = file_name;
                fusable[index].parent = tmp;
                index++;
            }
            //能走到这一步都说明文件修改成功了
            //检查是否满足配额tmp从下到上
            tmp->self_size += file_size;
            tmp->child_size += file_size;
            if ((tmp->LDd && tmp->self_size > tmp->LDd) || (tmp->LRd && tmp->child_size > tmp->LRd))
            {
                //cout << "this3" << endl;
                cout << "N" << endl;
                goto label;
            }
            //说明自己这一层没超
            //cout << "test" << tmp->child_size << endl;
            tmp = tmp->parent;  //换上
            while (tmp != NULL)
            {
                tmp->child_size += file_size;
                //cout << "test" << tmp->child_size << endl;
                if ((tmp->LDd && tmp->self_size > tmp->LDd) || (tmp->LRd && tmp->child_size > tmp->LRd))
                {
                    //cout << tmp->LDd <<endl;
                    //cout << "this4" << endl;
                    cout << "N" << endl;
                    goto label;
                }
                tmp = tmp->parent;
            }
            //能走到这一步说明完全没问题
            cout << "Y" << endl;
        }
        else if (cmd_type == 'R')
        {
            cin >> file_path;
            files = extrFilePath(file_path);
            Directory* tmp = &root;  //指向root
            for (int j = 0; j < files.size() - 1; j++)
            {
                //看看有没有重名目录
                bool Dflag = false;  //假设没有
                for (int k = 0; k < tmp->childrenD.size(); k++)
                {
                    if (files[j] == tmp->childrenD[k]->name)
                    {
                        Dflag = true;
                        tmp = tmp->childrenD[k];  //更换
                        break;
                    }
                }
                if (!Dflag)  //没有找到
                {
                    cout << "Y" << endl;
                    goto label;
                }
            }
            //所有都找到了
            file_name = files[files.size()-1];
            int delt_size = 0;
            //看看是哪一类
            bool Fflag = false;  //有没有对应文件
            for (int j = 0; j < tmp->childrenF.size(); j++)
            {
                if (tmp->childrenF[j]->name == file_name)
                {
                    //有相同的文件删除
                    tmp->self_size -= tmp->childrenF[j]->size;
                    tmp->child_size -= tmp->childrenF[j]->size;
                    tmp->childrenF.erase(tmp->childrenF.begin()+j);
                    Fflag = true;
                    delt_size = - tmp->childrenF[j]->size;
                    break;
                }
            }
            if (!Fflag)  //没找到，看目录
            {
                bool Dflag = false;
                for (int j = 0; j < tmp->childrenD.size(); j++)
                {
                    if (tmp->childrenD[j]->name == file_name)
                    {
                        tmp->child_size -= tmp->childrenD[j]->child_size;
                        //cout<< "child size" << tmp->childrenD[j]->child_size<<endl;
                        tmp->childrenD.erase(tmp->childrenD.begin()+j);
                        Dflag = true;
                        delt_size = -1 *  tmp->childrenD[j]->child_size;
                        //cout<< "delete size "<< delt_size<<endl;
                        break;
                    }
                }
            }
            cout << "Y" << endl;  //默认能执行成功
            //向上传播
            tmp = tmp->parent;
            while (tmp != NULL)
            {
                tmp->child_size += delt_size;
                tmp = tmp->parent;
            }
        }
        else if (cmd_type == 'Q')
        {
            cin >> file_path >> LD >> LR;
            files = extrFilePath(file_path);
            Directory* tmp = &root;  //指向root
            if (files.size() != 0)
            {
                for (int j = 0; j < files.size(); j++)
                {
                    //看看有没有重名目录
                    bool Dflag = false;  //假设没有
                    for (int k = 0; k < tmp->childrenD.size(); k++)
                    {
                        if (files[j] == tmp->childrenD[k]->name)
                        {
                            Dflag = true;
                            tmp = tmp->childrenD[k];  //更换
                            break;
                        }
                    }
                    if (!Dflag)  //没有找到
                    {
                        cout << "this+" << endl;
                        cout << "N" << endl;
                        goto label;
                    }
                }
            }
            //对配额进行修改
            if ((LD && tmp->self_size > LD) || (LR && tmp->child_size > LR))
            {
                //cout << "this-" << endl;
                //cout << "LR" << LR << "size" << tmp->child_size << endl;
                cout << "N" << endl;
                goto label;
            }
            else
            {
                tmp->LDd = LD;
                tmp->LRd = LR;
                cout << "Y" << endl;
            }
        }
label: int l;
    }
    
    return 0;
}