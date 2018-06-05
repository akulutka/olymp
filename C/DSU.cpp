#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> h;
vector<int> p;
int s;

int	getRoot(int v)
{
	if (p[v] == v)
		return v;
	return p[v] = getRoot(p[v]);
}

void unite(int a, int b)
{
	int pa = getRoot(a);
	int pb = getRoot(b);
	if (h[pa] < h[pb])
	{
		p[pa] = pb;
	}
	else
	{
		p[pb] = pa;
		if (h[pb] == h[pa])
		{
			h[pa]++;
		}
	}
}

int main()
{
	string str;
	int a, b;
	FILE * in = freopen("disjoint.in", "r", stdin);
	FILE * out = freopen("disjoint.out", "w", stdout);
	while (!feof(in))
	{
		cin >> str;
		if (feof(in))
		{
			str = "";
		}
		switch (str[0])
		{
		case 'R': //RESET command, creates s DSUs
			cin >> s;
			h.resize(s, 1);
			p.resize(s);
			for (int i = 0; i < p.size(); i++)
			{
				p[i] = i;
			}
			cout << "RESET DONE\n";
			break;
		case 'J': //JOIN command, joins system a to system b
			cin >> a >> b;
			if (getRoot(a) == getRoot(b))
			{
				cout << "ALREADY " << a << " " << b << "\n";
			}
			else
				unite(a, b);
			break;
		case 'C': //CHECK command, if a and b are related to the same set
			cin >> a >> b;
			if (getRoot(a) == getRoot(b))
				cout << "YES\n";
			else
				cout << "NO\n";
			break;
		}
	}
	return 0;
}