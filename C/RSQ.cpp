#define _CRT_SECURE_NO_WARNINGS                                                                                                                                                                                                                                   
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;


vector<int> T;

int query(int v, int l, int r, int vL, int vR)
{
	if (r <= vL || vR <= l)
	{
		return 0;
	}
	if (l <= vL && vR <= r)
	{
		return T[v];
	}
	int vC = (vL + vR) / 2;
	return query(2 * v + 1, l, r, vL, vC) + query(2 * v + 2, l, r, vC, vR);
}

void update(int v, int i, int dt, int vL, int vR)
{
	if (i < vL || i >= vR)
		return;
	T[v] += dt;
	if (vR - vL <= 1)
	{
		return;
	}
	int vC = (vR + vL) / 2;
	update(2 * v + 1, i, dt, vL, vC);
	update(2 * v + 2, i, dt, vC, vR);
}

int main()
{
	freopen("RSQ.in", "r", stdin);
	freopen("RSQ.out", "w", stdout);
	int n, m, tmp, tmp1, tmp2;
	cin >> n;
	T.resize(4 * n);
	tmp = -1;
	while (tmp != 0)
	{
		cin >> tmp;
		switch (tmp)
		{
		case 1:
			cin >> tmp1 >> tmp2;
			update(0, tmp1 - 1, tmp2, 0, n); //arr[tmp1 - 1] increases by tmp2
			break;
		case 2:
			cin >> tmp1 >> tmp2;
			cout << query(0, tmp1 - 1, tmp2, 0, n) << "\n"; //what is the sum of region (arr[tmp1]; arr[tmp2])
			break;
		case 0:
			exit(0);
			break;
		}
	}
	system("pause");
	return 0;
}