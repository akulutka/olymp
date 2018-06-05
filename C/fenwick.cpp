#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> F;
int n;

int query(int R)
{
	return R < 0 ? 0 : F[R] + query((R & (R + 1)) - 1);
}

int query(int L, int R)
{
	return query(R) - query(L - 1);
}

void update(int i, int dv)
{
	while (i < n)
	{
		F[i] += dv;
		i |= (i + 1);
	}
}

int main()
{
	int input = -1;
	int a, b;
	freopen("fenwick.in", "r", stdin);
	freopen("fenwick.out", "w", stdout);
	cin >> n;
	F.resize(n);
	while (input != 0)
	{
		cin >> input;
		if (input != 0)
		{
			cin >> a >> b;
			if (input == 1)
			{
				update(a - 1, b); //arr[a-1] increased by b
			}
			else
			{
				cout << query(a - 1, b - 1) << "\n"; //sum of [arr[a - 1]; arr[b - 1]]
			}
		}
		else
			break;
	}
	//system("pause");
	return 0;
}