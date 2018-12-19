#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;
class rinv//矩阵类
{
private:
	int n;
	double **a;
public:
	rinv(int nn)//构造函数
	{
		int i;
		n = nn;
		a = new double*[n];
		for (i = 0; i<n; i++) a[i] = new double[n + 8];
	}
	void input();
	void inv();
	void output();
	~rinv()//析构函数
	{
		int i;
		for (i = 0; i<n; i++) { delete[] a[i]; }
		delete[] a;
	}
};


void rinv::input()//输入函数
{
	int i, j;
	char str1[20];
	cout << "输入文件名：";
	cin >> str1;
	ifstream fin(str1);
	if (!fin)
	{
		cout << "\n不能打开这个文件" << str1 << endl; exit(1);
	}
	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			fin >> a[i][j];
	fin.close();
}


void rinv::inv()//矩阵求逆
{
	int *is, *js, i, j, k;
	double d, p;
	is = new int[n];
	js = new int[n];
	for (k = 0; k<n; k++)
	{
		d = 0.0;
		for (i = k; i<n; i++)
			for (j = k; j<n; j++)
			{
				p = fabs(a[i][j]);
				if (p>d) { d = p; is[k] = i; js[k] = j; }
			}
		if (d + 1.0 == 1.0)
		{
			delete[] is, js;
			cout << "\nA为奇异矩阵!没有逆矩阵。" << endl;
			exit(1);
		}
		if (is[k] != k)//全选主元
			for (j = 0; j<n; j++)
			{
				p = a[k][j]; a[k][j] = a[is[k]][j]; a[is[k]][j] = p;
			}
		if (js[k] != k)
			for (i = 0; i<n; i++)
			{
				p = a[i][k]; a[i][k] = a[i][js[k]]; a[i][js[k]] = p;
			}
		a[k][k] = 1.0 / a[k][k];
		for (j = 0; j<n; j++)
			if (j != k) a[k][j] = a[k][j] * a[k][k];
		for (i = 0; i<n; i++)
			if (i != k)
				for (j = 0; j<n; j++)
					if (j != k) a[i][j] = a[i][j] - a[i][k] * a[k][j];
		for (i = 0; i<n; i++)
			if (i != k) a[i][k] = -a[i][k] * a[k][k];
	}
	for (k = n - 1; k >= 0; k--)
	{
		if (js[k] != k)
			for (j = 0; j<n; j++)
			{
				p = a[k][j]; a[k][j] = a[js[k]][j]; a[js[k]][j] = p;
			}
		if (is[k] != k)
			for (i = 0; i<n; i++)
			{
				p = a[i][k]; a[i][k] = a[i][is[k]]; a[i][is[k]] = p;
			}
	}
	delete[] is, js;
}


void rinv::output()
{
	int i, j;
	char str2[20];
	cout << "输出文件名：";
	cin >> str2;
	ofstream fout(str2);
	if (!fout)
	{
		cout << "\n不能打开这个文件" << str2 << endl; exit(1);
	}
	for (i = 0; i<n; i++)
	{
		for (j = 0; j<n; j++)
		{
			fout << "    " << a[i][j];
			cout << "    " << a[i][j];
		}
		fout << endl; cout << endl;
	}
	fout.close();
}


int main()//主函数
{
	rinv c(4);
	c.input();
	c.inv();
	c.output();
	return 0;
}
