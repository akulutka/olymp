#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int>T;
vector<int>C;

void push(int v)
{
	C[2 * v + 1] += C[v];
	C[2 * v + 2] += C[v];
	C[v] = 0;
}

void addsegm(int v, int l, int r, int val, int vL, int vR)
{
	if (r <= vL || vR <= l)
		return;
	if (l <= vL && vR <= r)
	{
		C[v] += val;
		return;
	}
	push(v);
	int vC = (vL + vR) / 2;
	addsegm(2 * v + 1, l, r, val, vL, vC);
	addsegm(2 * v + 2, l, r, val, vC, vR);
	T[v] = T[2 * v + 1] + T[2 * v + 2] + C[2 * v + 1] * (vC - vL) + C[2 * v + 2] * (vR - vC);
}

long long query(int v, int l, int r, int vL, int vR)
{
	if (r <= vL || vR <= l)
		return 0;
	if (l <= vL && vR <= r)
		return ((long long)T[v]) + ((long long)C[v] * (vR - vL));
	push(v);
	int vC = (vL + vR) / 2;
	long long ans = query(2 * v + 1, l, r, vL, vC) + query(2 * v + 2, l, r, vC, vR);
	T[v] = T[2 * v + 1] + T[2 * v + 2] + C[2 * v + 1] * (vC - vL) + C[2 * v + 2] * (vR - vC);
	return ans;
}

int main()
{
	int n, q;
	int a, b, c, d;
	cin >> n >> q;
	T.resize(4 * n);
	C.resize(4 * n);
	for (int i = 0; i < q; i++)
	{
		cin >> a;
		if (a == 1)
		{
			cin >> b >> c >> d;
			addsegm(0, b, c, d, 0, n); //Add to [b; c] d
		}
		else
		{
			cin >> b >> c;
			cout << query(0, b, c, 0, n) << "\n"; //Get sum from [b; c]
		}
	}
	//system("pause");
	return 0;
}