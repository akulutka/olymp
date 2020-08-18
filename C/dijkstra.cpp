#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits.h>

using namespace std;

vector<vector<pair<int, int>>> G;
int s = 0;
int n = 0;
int f = 0;
int tmp = 0;
int tmp2 = -1;
vector<bool> used;
vector<int> dist;
vector<int> way;
vector<int> wayR;

void relax(int x) {
    for (auto p : G[x]) {
        int i = p.first;
        int cost = p.second;
        if (dist[i] > dist[x] + cost) {
            dist[i] = dist[x] + cost;
            way[i] = x;
        }
    }
}

int getMin() {
    int minv = -1;
    int mind = INT_MAX / 2;
    for (int i = 0; i < n; i++) {
        if (!used[i] && dist[i] < mind) {
            minv = i;
            mind = dist[i];
        }
    }
    return minv;
}

void search(int start) {
    dist[start] = 0;
    while (true) {
        int x = getMin();
        if (x == -1)
            break;
        relax(x);
        used[x] = true;
    }
}

int main() {
    freopen("dijkstra.in", "r", stdin);
    freopen("dijkstra.out", "w", stdout);
    cin >> n >> s >> f; //size of graph, start vertex, finish vertex
    G.resize(n);
    used.resize(n);
    dist.resize(n);
    way.resize(n);
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX / 2;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            if (tmp != -1) {
                pair<int, int> p;
                p.first = j;
                p.second = tmp;
                G[i].push_back(p);
            }
        }
    }
    search(s - 1);
    if (dist[f - 1] != INT_MAX / 2) {
        tmp2 = f - 1;
        while (tmp2 != s - 1) {
            wayR.push_back(tmp2 + 1);
            tmp2 = way[tmp2];
        }
        wayR.push_back(s);
        reverse(wayR.begin(), wayR.end());
        for (auto i : wayR) {
            cout << i << " "; //display the shortest way from s to f
        }
    } else {
        cout << -1;
    }
    return 0;
}