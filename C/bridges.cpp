#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <limits.h>
#include <string>
#include <set>

using namespace std;

typedef pair<int, int> pint;
typedef pair<pint, int> pint2;

vector<vector<pair<int, int>>> G;
vector<int> visited;
vector<int> up;
vector<int> tin;
int timeG = 0;
int res = 0;
vector<int> br;
vector<pint2> br2;
int n = 0, m = 0;

void dfs(int v, int p = -1) {
    if (visited[v])
        return;
    visited[v] = true;
    up[v] = tin[v] = timeG++;
    for (auto u : G[v]) {
        if (u.first == p)
            continue;
        if (!visited[u.first]) {
            dfs(u.first, v);
            up[v] = min(up[v], up[u.first]);
            if (up[u.first] > tin[v]) {
                res++;
                br2.push_back(pint2(u, v));
            }
        } else {
            up[v] = min(up[v], tin[u.first]);
        }
    }
}

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
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
            dfs(i);
        }
    }
    for (int i = 0; i < br2.size(); i++) {
        int c = 0;
        for (int j = 0; j < G[br2[i].first.first].size(); j++) {
            if (br2[i].second == G[br2[i].first.first][j].first) {
                c++;
                if (c > 1) {
                    break;
                }
            }
        }
        if (c == 1) {
            br.push_back(br2[i].first.second);
        }
    }
    cout << br.size() << "\n";
    sort(br.begin(), br.end());
    for (int i = 0; i < br.size(); i++) {
        cout << br[i] << " ";
    }
    return 0;
}