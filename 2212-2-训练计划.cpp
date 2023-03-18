#include<iostream>
#include<math.h>
#include<vector>
using namespace std;
int n, m;
const int maxn = 366, maxm = 101;
int rely[maxm];  //依赖关系
int t[maxm];  //所需时间
int fast[maxm];
int late[maxm];
vector<int> relied[maxm];  //被谁依赖

void calc_rely(int index)
{
	if (relied[index].empty())  //不被人依赖就结束
	{
		return;
	}
	else
	{
		//被人依赖
		for (int i = 0; i < relied[index].size(); i++)
		{
			fast[relied[index][i]] = fast[index] + t[index];
			calc_rely(relied[index][i]);  //递归计算
		}
	}
}

int calc_late(int index)
{
	//计算某个index的最晚开始时间
	int res;
	if (relied[index].empty())  //不被人依赖，最晚就可以是到最后一天训练完成
	{
		res = n - t[index] + 1;
		//late[index] = res;
		return res;
	}
	else
	{
		//有人依赖我
		int min = 400, tmp;
		for (int i = 0; i < relied[index].size(); i++)
		{
			tmp = calc_late(relied[index][i]);
			if (tmp < min)
			{
				min = tmp;
			}
		}
		//需要在tmp之前完成训练
		//late[index] = tmp - t[index];
		return (min - t[index]);
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> rely[i];
		if (rely[i])
		{
			relied[rely[i]].push_back(i);
		}
	}
	for (int i = 1; i <= m; i++) {
		cin >> t[i];
	}

	//开始计算最早开始时间和最晚开始时间
	for (int i = 1; i <= m; i++)
	{
		if (rely[i] == 0) {
			//不依赖谁，最早开始时间是1
			fast[i] = 1;
			//计算依赖他的人
			calc_rely(i);
		}
	}
	//计算完最早开始时间
	//70%数据不需要最晚开始时间
	for (int i = 1; i <= m; i++) {
		cout << fast[i] << " ";
	}

	int flag = true;

	//接下来计算最晚开始时间
	for (int i = 1; i <= m; i++)
	{
		late[i] = calc_late(i);
		if (late[i] <= 0 || late[i] < fast[i])
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		cout << endl;
		for (int i = 1; i <= m; i++) {
			cout << late[i] << " ";
		}
	}
	return 0;
}