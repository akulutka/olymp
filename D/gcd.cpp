#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <string>

using namespace std;

int gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return gcd(b, a % b);
	}
}

int main()
{
	//any code
}