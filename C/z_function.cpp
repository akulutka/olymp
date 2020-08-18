#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <string>

using namespace std;

string s;
vector<int> z;

void zfix(string str) {
    z.resize(str.size());
    z[0] = str.size();
    int l = 0;
    int r = 0;
    for (int i = 1; i < str.size(); i++) {
        z[i] = 0;
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < str.size() && str[i + z[i]] == str[z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
}

int main() {
    freopen("z-function.in", "r", stdin);
    freopen("z-function.out", "w", stdout);
    getline(cin, s);
    zfix(s);
    for (int i = 0; i < z.size(); i++) {
        cout << z[i] << " ";
    }
}