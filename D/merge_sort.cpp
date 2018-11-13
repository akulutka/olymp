#include <iostream>
#include <cstdlib>

using namespace std;

typedef int ArrType;

const int N = 10000;

ArrType A[N];

void my_merge(ArrType A[],
	ArrType L[], int LSize,
	ArrType R[], int RSize);

void merge_sort(ArrType A[], const int ASize)
{
	if (ASize <= 1) return;

	const int middle = ASize / 2;
	ArrType Left[middle];
	ArrType Right[ASize - middle];
	for (int i = 0; i < middle; ++i)
		Left[i] = A[i];
	for (int i = middle; i < ASize; ++i)
		Right[i - middle] = A[i];

	merge_sort(Left, middle);
	merge_sort(Right, ASize - middle);
	my_merge(A, Left, middle, Right, ASize - middle);
}

void my_merge(ArrType A[],
	ArrType L[], int LSize,
	ArrType R[], int RSize)
{
	int i = 0, j = 0, k = 0;
	while (i < LSize && j < RSize)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			i++; k++;
		}
		else
		{
			A[k] = R[j];
			j++; k++;
		}
		while (i < LSize)
		{
			A[k] = L[i];
			i++; k++;
		}
		while (j < RSize)
		{
			A[k] = R[j];
			j++; k++;
		}
	}
}

int main()
{
	int size = 0;
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cin >> A[i];
	}
	merge_sort(A, size);
	return 0;
}