#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<vector<int>>> F;
int n;

int query(int Rx, int Ry, int Rz) {
    int sum = 0;
    while (Rx >= 0) {
        int tRy = Ry;
        while (tRy >= 0) {
            int tRz = Rz;
            while (tRz >= 0) {
                sum += F[Rx][tRy][tRz];
                tRz = (tRz & (tRz + 1)) - 1;
            }
            tRy = (tRy & (tRy + 1)) - 1;
        }
        Rx = (Rx & (Rx + 1)) - 1;
    }
    return sum;
}

void update(int i, int j, int k, int dv) {
    while (i < n) {
        int tj = j;
        while (tj < n) {
            int tk = k;
            while (tk < n) {
                F[i][tj][tk] += dv;
                tk |= (tk + 1);
            }
            tj |= (tj + 1);
        }
        i |= (i + 1);
    }
}

int query3(int xx, int yy, int zz, int xx1, int yy1, int zz1) {
    int sum = 0;
    sum += query(xx1, yy1, zz1);
    sum -= query(xx1, yy - 1, zz1);
    sum -= query(xx1, yy1, zz - 1);
    sum -= query(xx - 1, yy1, zz1);
    sum += query(xx1, yy - 1, zz - 1);
    sum += query(xx - 1, yy1, zz - 1);
    sum += query(xx - 1, yy - 1, zz1);
    sum -= query(xx - 1, yy - 1, zz - 1);
    return sum;
}

int main() {
    int input = -1;
    int xx, yy, zz, val, xx1, yy1, zz1;
    freopen("fenwick3d.in", "r", stdin);
    freopen("fenwick3d.out", "w", stdout);
    cin >> n;
    F.resize(n);
    for (int i = 0; i < F.size(); i++) {
        F[i].resize(n);
        for (int j = 0; j < F[i].size(); j++) {
            F[i][j].resize(n);
        }
    }
    while (input != 3) {
        cin >> input;
        if (input != 3) {
            if (input == 1) {
                cin >> xx >> yy >> zz >> val;
                update(xx, yy, zz, val); //arr[x, y, z] increased by val
            } else {
                cin >> xx >> yy >> zz >> xx1 >> yy1 >> zz1;
                cout << query3(xx, yy, zz, xx1, yy1, zz1) << "\n"; //sum of [arr[x1, y1, z1]; arr[x2, y2, z2]]
            }
        } else {
            break;
        }
    }
    return 0;
}