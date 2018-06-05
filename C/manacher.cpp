#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <string>

using namespace std;

string s, t, s1;
vector<int> z;

void pfix(string str)
{
	z.resize(str.size());
	z[0] = 0;
	int l = 0;
	int r = 0;
	for (int i = 1; i < str.size(); i++)
	{
		z[i] = 0;
		if (i <= r)
		{
			z[i] = min(z[l + (r - i)], r - i);
		}
		while (i - z[i] > 0 && i + z[i] < str.size() - 1 && str[i - z[i] - 1] == str[i + z[i] + 1])
		{
			z[i]++;
		}
		if (i + z[i] > r)
		{
			l = i - z[i];
			r = i + z[i];
		}
	}
}

int main()
{
	freopen("manacher.in", "r", stdin);
	freopen("manacher.out", "w", stdout);
	getline(cin, s);
	pfix(s);
	for (int i = 0; i < z.size(); i++)
	{
		cout << 1 + 2 * z[i] << " ";
	}
	//system("pause");
}