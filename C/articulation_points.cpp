#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <string>
#include <set>

using namespace std;

typedef set<int>::const_iterator sit;
typedef pair<int, int> pint;

vector<vector<pint>> G;
vector<int> visited;
vector<int> up;
vector<int> tin;
int timeG = 0;
set<int> sP;
vector<int> res;
int n = 0, m = 0;
int root = -1;

void dfs(int v, int p = -1) {
    int cnt = 0;
    if (visited[v])
        return;
    visited[v] = true;
    up[v] = tin[v] = timeG++;
    for (auto u : G[v]) {
        if (u.first == p)
            continue;
        if (!visited[u.first]) {
            ++cnt;
            dfs(u.first, v);
            up[v] = min(up[v], up[u.first]);
            if (up[u.first] >= tin[v]) {
                if (v != root) {
                    sP.insert(v + 1);
                }
            }
        } else {
            up[v] = min(up[v], tin[u.first]);
        }
    }
    if (v == root && cnt > 1) {
        sP.insert(v + 1);
    }
}

int main() {
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);
    int a, b;
    cin >> n >> m;
    G.resize(n);
    visited.resize(n);
    tin.resize(n);
    up.resize(n);
    for (int i = 1; i <= m; i++) {
        cin >> a >> b;
        G[a - 1].push_back(pint(b - 1, i));
        G[b - 1].push_back(pint(a - 1, i));
    }
    for (int i = 0; i < visited.size(); i++) {
        if (!visited[i]) {
            root = i;
            dfs(i);
        }
    }
    for (sit it = sP.begin(); it != sP.end(); it++) {
        res.push_back(*it);
    }
    cout << res.size() << "\n";
    sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    return 0;
}