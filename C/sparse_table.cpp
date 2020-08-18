#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>

using namespace std;

vector<vector<int>> A;

int query(int l, int r) {
    if (l > r) {
        swap(l, r);
    }
    int len = (r - l + 1);
    int j = (int)(log(len) / log(2));
    return min(A[j][l], A[j][r - (1 << j) + 1]);
}

int main() {
    freopen("sparse.in", "r", stdin);
    freopen("sparse.out", "w", stdout);
    int n, m, a1, u, v, ans;
    cin >> n >> m >> a1 >> u >> v; // m * n - size of table; arr[0][0] = a1; u, v - initial query data
    int depth = (int)(log(n) / log(2)) + 1;
    A.resize(depth);
    for (int i = 0; i < depth; i++) {
        A[i].resize(n);
    }
    A[0][0] = a1;
    for (int i = 1; i < n; i++) {
        A[0][i] = (23 * A[0][i - 1] + 21563) % 16714589;
    }
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i < n; i++) {
            int z = i + (1 << (j - 1));
            if (z < n) {
                A[j][i] = min(A[j - 1][z], A[j - 1][i]);
            } else {
                A[j][i] = A[j - 1][i];
            }
        }
    }
    for (int i = 1; i < m; i++) {
        ans = query(u - 1, v - 1);
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
    }
    cout << u << " " << v << " " << query(u - 1, v - 1) << "\n";
}