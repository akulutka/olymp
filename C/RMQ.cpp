#define _CRT_SECURE_NO_WARNINGS                                                                                                                                                                                                                                   
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits.h>

using namespace std;

typedef pair<int, int> pint; // value + index in arr[]

vector<pair<int, int>> T;

bool operator< (pair<int, int> &l, pair<int, int> &r) {
    return l.first < r.first;
}

pint query(int v, int l, int r, int vL, int vR) {
    pint tmp;
    if (r <= vL || vR <= l) {
        tmp.first = INT_MIN;
        return tmp;
    }
    if (l <= vL && vR <= r) {
        return T[v];
    }
    int vC = (vL + vR) / 2;
    return max(query(2 * v + 1, l, r, vL, vC), query(2 * v + 2, l, r, vC, vR));
}

void update(int v, int i, int val, int vL, int vR) {
    if (i < vL || i >= vR)
        return;
    if (vR - vL <= 1) {
        T[v].first = val;
        T[v].second = i;
        return;
    }
    int vC = (vR + vL) / 2;
    update(2 * v + 1, i, val, vL, vC);
    update(2 * v + 2, i, val, vC, vR);
    T[v] = max(T[2 * v + 1], T[2 * v + 2]);
}

int main() {
    freopen("RMQ.in", "r", stdin);
    freopen("RMQ.out", "w", stdout);
    int n, m, tmp, tmp1;
    cin >> n;
    pint res;
    T.resize(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        update(0, i, tmp, 0, n); //arr[i] increases by tmp
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> tmp >> tmp1;
        res = query(0, tmp - 1, tmp1, 0, n); //get the maximum in region (arr[tmp]; arr[tmp1])
        cout << res.first << " " << res.second + 1 << "\n";
    }
    return 0;
}