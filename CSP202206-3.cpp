//CSP202206-3 角色授权

//只拿到90分，最后一个点会超时，暂时没想到解决方案
//参考的题解都能AC，思路都一样的

#include<iostream>
#include<cstring>
#include<map>
#include<set>
using namespace std;

struct Role  //角色结构体
{
    set<string> ops;
    set<string> src_types;
    set<string> src_names;
};
map<string, Role> Roles;

struct Group
{
    set<string> roles;
};
map<string, Group> Groups;

struct User
{
    set<string> roles;
    set<string> groups;

    bool check (string op, string src_type, string src_name)
    {
        //查看直接关联的角色
        for (auto iter : roles)
        {
            if (Roles[iter].ops.count("*") || Roles[iter].ops.count(op))  // 存在操作符
            {
                if (Roles[iter].src_types.count("*") || Roles[iter].src_types.count(src_type))  // 存在资源种类
                {
                    if (Roles[iter].src_names.empty() || Roles[iter].src_names.count(src_name))
                    {
                        return true;
                    }
                }
            }
        }
        /*
        set<string>::iterator iter = roles.begin();
        while (iter != roles.end())
        {
            if (Roles[*iter].ops.count("*") || Roles[*iter].ops.count(op))  // 存在操作符
            {
                if (Roles[*iter].src_types.count("*") || Roles[*iter].src_types.count(src_type))  // 存在资源种类
                {
                    if (Roles[*iter].src_names.empty() || Roles[*iter].src_names.count(src_name))
                    {
                        return true;
                    }
                }
            }
            iter++;
        }*/
        //通过用户组看关联的角色

        for (auto iter : groups)
        {
            if (Groups.count(iter))
            {
                for (auto iter2 : Groups[iter].roles)
                {
                    if (Roles[iter2].ops.count("*") || Roles[iter2].ops.count(op))  // 存在操作符
                    {
                        if (Roles[iter2].src_types.count("*") || Roles[iter2].src_types.count(src_type))  // 存在资源种类
                        {
                            if (Roles[iter2].src_names.empty() || Roles[iter2].src_names.count(src_name))
                            {
                                return true;
                            }
                        }
                    }
                }
                
            }
        }
        
        /*
        iter = groups.begin();
        while (iter != groups.end())
        {
            if (Groups.count(*iter))
            {
                set<string>::iterator iter2 = Groups[*iter].roles.begin(); 
                while (iter2 != Groups[*iter].roles.end())
                {
                    if (Roles[*iter2].ops.count("*") || Roles[*iter2].ops.count(op))  // 存在操作符
                    {
                        if (Roles[*iter2].src_types.count("*") || Roles[*iter2].src_types.count(src_type))  // 存在资源种类
                        {
                            if (Roles[*iter2].src_names.empty() || Roles[*iter2].src_names.count(src_name))
                            {
                                return true;
                            }
                        }
                    }
                    iter2++;
                }
            }
            iter++;
        }*/
        return false;
    }
};
map<string, User> users;

int main(){
    int n, m, q;
    cin >> n >> m >> q;

    //输入角色信息
    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> name;
        int nv, no, nn;
        //Role role;
        cin >> nv;
        for (int j = 0; j < nv; j++)
        {
            string op;
            cin >> op;
            Roles[name].ops.emplace(op);
            //role.ops.insert(op);  // 加入操作
        }
        cin >> no;
        for (int j = 0; j < no; j++)
        {
            string src_type;
            cin >> src_type;
            Roles[name].src_types.emplace(src_type);
            //role.src_types.insert(src_type);
        }
        cin >> nn;
        for (int j = 0; j < nn; j++)
        {
            string src_name;
            cin >> src_name;
            Roles[name].src_names.emplace(src_name);
            //role.src_names.insert(src_name);
        }
        //Roles.insert(pair<string, Role>(name, role));
    }

    //输入角色关联信息
    for (int i = 0; i < m; i++)
    {
        string role_name;
        cin >> role_name;
        int ns;
        cin >> ns;  //对象数量
        char flag;
        for (int j = 0; j < ns; j++)
        {
            cin >> flag;  //u or g
            if (flag == 'u')  //加入授权用户
            {
                string user_name;
                cin >> user_name;
                users[user_name].roles.emplace(role_name);
            }
            else  //加入授权用户组
            {
                string group_name;
                cin >> group_name;
                Groups[group_name].roles.emplace(role_name);
            }
        }
    }

    //输入待授权行为
    for (int i = 0; i < q; i++)
    {
        string user_name;
        cin >> user_name;
        int ng;
        cin >> ng;  //所属的用户组数目
        for (int j = 0; j < ng; j++)
        {
            string group_name;
            cin >> group_name;
            users[user_name].groups.emplace(group_name);
        }
        string op, src_type, src_name;
        cin >> op >> src_type >> src_name;
        cout<<users[user_name].check(op, src_type, src_name)<<endl;
        //注意清除groups
        users[user_name].groups.clear();
    }
    return 0;
}