#define SIZE 100000
#define LOG 20
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> G;
vector<int> euler;
int first[SIZE];
int d[SIZE];
int Log[2 * SIZE];
int sparse[LOG + 1][2 * SIZE];
int n = 0;

void dfs(int v, int p = -1) {
    d[v] = (p == -1 ? 0 : d[p] + 1);
    first[v] = euler.size();
    euler.push_back(v);
    for (int i = 0; i < G[v].size(); i++) {
        if (G[v][i] != p) {
            dfs(G[v][i], v);
            euler.push_back(v);
        }
    }
}

int Min(int a, int b) {
    return d[a] < d[b] ? a : b;
}

void build() {
    int l = 2 * n - 1;
    for (int i = 0; i < 2 * SIZE; i++) {
        Log[i] = (int)log2(i);
    }
    for (int i = 0; i < l; i++) {
        sparse[0][i] = euler[i];
    }
    for (int i = 1; (1 << i) <= l; i++) {
        for (int j = 0; j <= l - (1 << j); j++) {
            sparse[i][j] = Min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int getmin(int l, int r) {
    int len = r - l + 1;
    int level = Log[len];
    return Min(sparse[level][l], sparse[level][r - (1 << level) + 1]);
}

int lca(int u, int v) {
    u = first[u];
    v = first[v];
    if (u > v) {
        swap(u, v);
    }
    return getmin(u, v);
}

int main() {
    int tmp = 0, m = 0, a, b, q; //n vertexes, m edges, q queries
    cin >> n >> m >> q;
    G.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(0);
    build();
    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        a--;
        b--;
        cout << lca(a, b) + 1 << "\n";
    }
}