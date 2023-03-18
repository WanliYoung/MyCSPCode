#include<iostream>
#include<math.h>
#include<vector>
#include<cmath>
using namespace std;
double Q[8][8], M[8][8], Mn[8][8];  //8*8的量化矩阵
int r[8][8];
int n, T;  //扫描数据个数，任务
double pi = acos(-1);

double get_u(double u)
{
	if (u)
	{
		return 1;
	}
	else
	{
		return pow(0.5, 0.5);
	}
}

double get_value(double i, double j, double u, double v)
{
	double ans;
	double au = get_u(u), av = get_u(v);
	double Muv = M[(int)u][(int)v];
	double cos1 = cos((pi / 8) * (i + 0.5) * u);
	double cos2 = cos((pi / 8) * (j + 0.5) * v);
	ans = au * av * Muv * cos1 * cos2;
	return ans;
}

int main()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cin >> Q[i][j];
		}
	}
	cin >> n >> T;

	if (n == 0)  //没有输入数据
	{

	}
	else if (n >= 1)
	{
		cin >> M[0][0];
		int cin_num = 1;
		int dir_flag = 1;  //标识向下走还是向上走 -1代表下：x+=1,y-=1;1代表上：x-=1,y+=1
		int b_i = 0, b_j = 1;  //开始的下标
		if (n == 1)
		{
			goto label;
		}
		for (int i = 1; i <= 7; i++)  //刚开始是7趟
		{
			for (int j = 1; j <= i + 1; j++)
			{
				if (cin_num < n)
				{
					cin >> M[b_i][b_j];
					cin_num++;
				}
				else
				{
					goto label;
				}
				b_i += dir_flag * 1;
				b_j += dir_flag * (-1);
			}
			if (b_j == -1)  //超出左边了
			{
				b_j = 0;
				dir_flag *= -1;
			}
			if (b_i == -1)  //超出上边了
			{
				b_i = 0;
				dir_flag *= -1;
			}
		}
		//把左半边输入完了
		if (cin_num >= n)
		{
			goto label;
		}
		b_i = 7, b_j = 1;
		dir_flag = -1;  //向上
		for (int i = 1; i <= 6; i++)  //刚开始是7趟
		{
			for (int j = 1; j <= 8 - i; j++)
			{
				if (cin_num < n)
				{
					cin >> M[b_i][b_j];
					cin_num++;
				}
				else
				{
					goto label;
				}
				b_i += dir_flag * 1;
				b_j += dir_flag * (-1);
			}
			//返回去
			b_i -= dir_flag * 1;
			b_j -= dir_flag * (-1);
			if (b_j == 7)  //超出左边了
			{
				b_i += 1;
				dir_flag *= -1;
			}
			if (b_i == 7)  //超出上边了
			{
				b_j += 1;
				dir_flag *= -1;
			}
		}
		if (cin_num < n)
		{
			cin >> M[7][7];
		}
		else
		{
			goto label;
		}

	label:  //输入结束
		int nothing = 0;
	}
	

	if (T == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << M[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}

	//与量化矩阵相乘
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			M[i][j] = M[i][j] * Q[i][j];
		}
	}

	if (T == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << M[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}

	//接下来需要处理得到最终的结果了
	double ans;
	for (double i = 0; i < 8; i++)
	{
		for (double j = 0; j < 8; j++)
		{
			ans = 0;
			//cout << "----" << endl;;
			for (double u = 0; u < 8; u++)
			{
				for (double v = 0; v < 8; v++)
				{
					ans += get_value(i, j, u, v);
					//cout << get_value(i, j, u, v) << endl;
				}
			}
			//cout << "----" << endl;
			ans /= 4.0;
			Mn[(int)i][(int)j] = ans;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Mn[i][j] += 128;
			r[i][j] = round(Mn[i][j]);
			if (r[i][j] > 255)
			{
				r[i][j] = 255;
			}
			if (r[i][j] < 0)
			{
				r[i][j] = 0;
			}
		}
	}

	if (T == 2)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				cout << r[i][j] << " ";
			}
			cout << endl;
		}
		return 0;
	}
	return 0;
}