#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> H;
int Hsize = 0;

void SiftUp(int v)
{
	if (v == 0)
		return;
	if (H[v] > H[(v - 1) / 2])
	{
		swap(H[v], H[(v - 1) / 2]);
		SiftUp((v - 1) / 2);
	}
}

void SiftDown(int v)
{
	int max = v;
	if (2 * v + 1 < Hsize && H[2 * v + 1] > H[max])
	{
		max = 2 * v + 1;
	}
	if (2 * v + 2 < Hsize && H[2 * v + 2] > H[max])
	{
		max = 2 * v + 2;
	}
	if (v != max)
	{
		swap(H[v], H[max]);
		SiftDown(max);
	}
	else
	{
		H.pop_back();
	}
}

void popMax()
{
	swap(H[0], H[Hsize - 1]);
	Hsize--;
	SiftDown(0);
}

int main()
{
	string str;
	int tmp;
	FILE * in = freopen("heap.in", "r", stdin);
	FILE * out = freopen("heap.out", "w", stdout);
	while (!feof(in))
	{
		cin >> str;
		if (feof(in))
		{
			str = "";
		}
		switch (str[0])
		{
		case 'A': //ADD command, adds element tmp to the heap
			cin >> tmp;
			Hsize++;
			H.push_back(tmp);
			SiftUp(Hsize - 1);
			break;
		case 'C': //CLEAR command, clears the heap
			H.clear();
			Hsize = 0;
			break;
		case 'E': //EXTRACT command, extracts the maximum (H[0])
			if (Hsize > 0)
			{
				cout << H[0] << "\n";
				popMax();
			}
			else
				cout << "CANNOT\n"; //heap is empty
			str = "";
			break;
		}
		cout.flush();
		cin.tie();
	}
	//system("pause");
	return 0;
}