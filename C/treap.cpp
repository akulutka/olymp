#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits.h>

using namespace std;

struct Node {
    int x, y;
    Node *L, *R;
    Node(int x = 0, int y = 0, Node *L = nullptr, Node *R = nullptr) {
        this->x = x;
        this->y = y;
        this->L = L;
        this->R = R;
    }
};

Node *T = nullptr;
int ans = 0;

void split(Node *v, int d, Node* &v1, Node* &v2) {
    if (v == nullptr) {
        v1 = v2 = nullptr;
        return;
    }
    if (v->x < d) {
        split(v->R, d, v->R, v2);
        v1 = v;
    } else {
        split(v->L, d, v1, v->L);
        v2 = v;
    }
}

Node* merge(Node *v1, Node *v2) {
    if (v1 == nullptr) return v2;
    if (v2 == nullptr) return v1;
    if (v1->y > v2->y) {
        v1->R = merge(v1->R, v2);
        return v1;
    } else {
        v2->L = merge(v1, v2->L);
        return v2;
    }
}

void add(int x) {
    Node *v1, *v2, *vx;
    vx = new Node(x, rand());
    split(T, x, v1, v2);
    T = merge(merge(v1, vx), v2);
}

void del(int x) {
    Node *v1, *v2, *v3, *v4;
    split(T, x, v1, v2);
    split(v2, x + 1, v3, v4);
    T = merge(v1, v4);
}

int req(int x, Node *X) {
    if (X == nullptr)
        return ans;
    if (X->x == x) {
        ans = x;
        return x;
    }
    if (X->x > x) {
        ans = X->x;
        req(x, X->L);
    }
    if (X->x < x) {
        req(x, X->R);
    }
    return ans;
}

int main() {
    int n = 0, res = 0;
    char cmd = '\0';
    char pcmd = '\0';
    int v = 0;
    srand(time(NULL));
    freopen("treap.in", "r", stdin);
    freopen("treap.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> cmd >> v;
        if (cmd == '?') {
            ans = -1;
            res = req(v, T); //get the least element, which is greater than v or display -1 if it doesn't exist
            cout << res << '\n';
        } else {
            if (pcmd == '?') {
                if (res == -1)
                    res = 0;
                v = (v + res) % 1000000000; //generate a new element and add it to the treap
            }
            add(v);
        }
        pcmd = cmd;
    }
    return 0;
}