#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;
unsigned long int n, k;
unsigned long int lr, ll, tofind;

vector<int> arr;
int binSL(unsigned long int tofind) {
    unsigned long int r = arr.size();
    unsigned long int l = -1;
    unsigned long int m = 0;
    while (r - l > 1) {
        m = (r + l) / 2;
        if (arr[m] < tofind) {
            l = m;
        } else {
            r = m;
        }
    }
    if (r == arr.size()) {
        r--;
    }
    if (l == -1) {
        l++;
    }
    if (arr[r] == tofind) {
        return arr[r];
    }
    return -1;
}

int binSR(unsigned long int tofind) {
    unsigned long int r = arr.size();
    unsigned long int l = -1;
    unsigned long int m = 0;
    while (r - l > 1) {
        m = (r + l) / 2;
        if (arr[m] <= tofind) {
            l = m;
        } else {
            r = m;
        }
    }
    if (r == arr.size()) {
        r--;
    }
    if (l == -1) {
        l++;
    }
    if (arr[l] == tofind) {
        return arr[l];
    }
    return -1;
}

int main() {
    freopen("bsearch.in", "r", stdin);
    freopen("bsearch.out", "w", stdout);
    cin >> n;
    arr.resize(n);
    for (unsigned long int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    for (unsigned long int i = 0; i < k; i++) {
        cin >> tofind;
        if (binSL(tofind) == -1 || binSR(tofind) == -1) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    return 0;
}