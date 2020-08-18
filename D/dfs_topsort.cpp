#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int>> G;
vector<int> tSort;
vector<int> col;
vector<bool> used;
bool hasC = false;

bool dfsC(int v) {
    col[v] = 1;
    for (int i = 0; i < G[v].size(); i++) {
        if (col[G[v][i]] == 0) {
            if (dfsC(G[v][i])) {
                return true;
            }
        } else if (col[G[v][i]] == 1) {
            return true;
        }
    }
    col[v] = 2;
    return false;
}

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        if (!used[G[v][i]]) {
            dfs(G[v][i]);
        }
    }
    tSort.push_back(v + 1);
}

int main() {
    int n, m, a, b;
    bool st = false;
    freopen("topsort.out", "w", stdout);
    freopen("topsort.in", "r", stdin);
    cin >> n >> m; //n vertexes, m edges
    G.resize(n);
    col.resize(n);
    used.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> a >> b; //edge a->b
        G[a - 1].push_back(b - 1);
    }
    for (int i = 0; i < n; i++) {
        if (dfsC(i)) {
            st = true;
            break;
        }
    }
    if (st) {
        cout << "-1";
    } else {
        for (int i = 0; i < n; i++) {
            if (!used[i])
                dfs(i);
        }
        reverse(tSort.begin(), tSort.end());
        for (int i = 0; i < tSort.size(); i++) {
            cout << tSort[i] << " ";
        }
    }
    return 0;
}