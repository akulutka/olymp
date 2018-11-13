#include <iostream>
#include <cstdlib>

using namespace std;

typedef int ArrType;
const int N = 10000;
ArrType A[N];

void qsort(ArrType A[], int ASize)
{
    if (ASize <= 1) return;
    int sep = A[rand() % ASize];
    int i = 0;
    int k = ASize - 1;
    while (i < k)
    {
        while (A[i] < sep) i++;
        while (A[k] >= sep) k--;
        if (i < k) swap(A[i], A[k]);
    }
    int nLeft = i;
    k = ASize - 1;
    while (i < k)
    {
        while (A[i] == sep) i++;
        while (A[k] != sep) k--;
        if (i < k) swap(A[i], A[k]);
    }
    int nSep = i - nLeft;
    int nRight = ASize - nLeft - nSep;
    ArrType *B = A + nLeft + nSep;
    qsort(A, nLeft);
    qsort(B, nRight);
}

int main()
{
	int size = 0;
	cin >> size;
	for (int i = 0; i < size; i++)
	{
		cin >> A[i];
	}
	qsort(A, size);
	return 0;
}