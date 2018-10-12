#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int SIZE = 100228;
const ll inf = 1e12;

int n;
int vdata[SIZE];
vector<int> gr[SIZE];

int l;
int first[SIZE];
int d[SIZE];
vector<int> euler;
int lcat[8 * SIZE];

int down[SIZE];
int up[SIZE];
int len[SIZE];
int w[SIZE];
vector<int> vert[SIZE];
vector<ll> t[SIZE];

int dfs(int v, int p) {
    d[v] = (p == -1 ? 0 : d[p] + 1);
    first[v] = euler.size();
    euler.push_back(v);
    w[v] = 1;
    for (size_t u = 0; u < gr[v].size(); ++u) {
		int i = gr[v][u];
        if (i != p) {
            w[v] += dfs(i, v);
            euler.push_back(v);
        }
    }
    down[v] = v;
    up[v] = p;
    len[v] = 1;
    vert[v].push_back(v);
    for (size_t u = 0; u < gr[v].size(); ++u) {
		int i = gr[v][u];
        if (i != p && w[i] * 2 >= w[v]) {
            down[v] = down[i];
            up[down[v]] = p;
            len[down[v]]++;
            vert[down[v]].push_back(v);
            break;
        }
    }
    return w[v];
}

inline int Min(int u, int v) {
    return d[u] < d[v] ? u : v;
}

void buildlca(int v, int l, int r) {
    if (l == r - 1) {
        lcat[v] = euler[l];
        return;
    }
    int m = (l + r) / 2;
    buildlca(2 * v + 1, l, m);
    buildlca(2 * v + 2, m, r);
    lcat[v] = Min(lcat[2 * v + 1], lcat[2 * v + 2]);
}

int minlca(int v, int l, int r, int askl, int askr) {
    if (askl >= r || l >= askr) {
        return n;
    }
    if (l >= askl && r <= askr) {
        return lcat[v];
    }
    int m = (l + r) / 2;
    return Min(minlca(2 * v + 1, l, m, askl, askr),
               minlca(2 * v + 2, m, r, askl, askr));
}

inline int lca(int u, int v) {
    u = first[u];
    v = first[v];
    if (u > v) {
        swap(u, v);
    }
    return minlca(0, 0, l, u, v + 1);
}

void buildhld(int v, int l, int r, int i) {
    if (l == r - 1) {
        t[i][v] = vdata[vert[i][l]];
        return;
    }
    int m = (l + r) / 2;
    buildhld(2 * v + 1, l, m, i);
    buildhld(2 * v + 2, m, r, i);
    t[i][v] = max(t[i][2 * v + 1], t[i][2 * v + 2]);
}

ll maxhld(int v, int l, int r, int askl, int askr, int i) {
    if (l >= askr || r <= askl) {
        return -inf;
    }
    if (l >= askl && r <= askr) {
        return t[i][v];
    }
    int m = (l + r) / 2;
    return max(maxhld(2 * v + 1, l, m, askl, askr, i),
               maxhld(2 * v + 2, m, r, askl, askr, i));
}

void addhld(int v, int l, int r, int pos, int val, int i) {
    if (l == r - 1) {
        t[i][v] += val;
        return;
    }
    int m = (l + r) / 2;
    if (pos < m) {
        addhld(2 * v + 1, l, m, pos, val, i);
    } else {
        addhld(2 * v + 2, m, r, pos, val, i);
    }
    t[i][v] = max(t[i][2 * v + 1], t[i][2 * v + 2]);
}

inline void addvertex(int v, ll val) {
    addhld(0, 0, len[down[v]], d[down[v]] - d[v], val, down[v]);
}

ll maxway(int u, int v) {
    if (down[u] == down[v]) {
        return maxhld(0, 0, len[down[u]], d[down[u]] - d[u], d[down[v]] - d[v] + 1, down[u]);
    }
    return max(maxhld(0, 0, len[down[u]], d[down[u]] - d[u], len[down[u]], down[u]), maxway(up[down[u]], v));
}

/*inline ll maxway(int u, int v) {
    ll ans = -inf;
    while (down[u] != down[v]) {
        ans = max(ans, maxhld(0, 0, len[down[u]], d[down[u]] - d[u], len[down[u]], down[u]));
        u = up[down[u]];
    }
    ans = max(ans, maxhld(0, 0, len[down[u]], d[down[u]] - d[u], d[down[v]] - d[v] + 1, down[u]));
    return ans;
}*/

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        gr[u - 1].push_back(v - 1);
        gr[v - 1].push_back(u - 1);
    }
	euler.reserve(2 * n - 1);
    dfs(0, -1);
    d[n] = n + 1;
    l = 2 * n - 1;
    buildlca(0, 0, l);
    for (int i = 0; i < n; ++i) {
        if(down[i] == i) {
            t[i].resize(4 * len[i]);
            //buildhld(0, 0, len[i], i);
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char type;
        cin >> type;
        if (type == 'I') {
            int v;
            ll val;
            cin >> v >> val;
            v--;
            addvertex(v, val);
        } else {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            int uvlca = lca(u, v);
            cout << max(maxway(u, uvlca), maxway(v, uvlca)) << '\n';
        }
    }
    return 0;
}
