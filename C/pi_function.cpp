#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <string>

using namespace std;

string s;
vector<int> pi;

void prefix(string str) {
    pi.resize(str.size());
    pi[0] = 0;
    for (int i = 1; i < str.size(); i++) {
        int k = pi[i - 1];
        while (k > 0 && str[k] != s[i]) {
            k = pi[k - 1];
        }
        if (str[k] == str[i]) {
            pi[i] = k + 1;
        } else {
            pi[i] = 0;
        }
    }
}

int main() {
    freopen("prefix.in", "r", stdin);
    freopen("prefix.out", "w", stdout);
    getline(cin, s);
    prefix(s);
    for (int i = 0; i < pi.size(); i++) {
        cout << pi[i] << " ";
    }
}