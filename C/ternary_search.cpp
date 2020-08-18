#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
const double eps = 0.001;

double ternary(double l, double r, bool isMin) {
    while (r - l > eps) {
        double y_1;
        double y_2;
        double x1 = (2 * l + r) / 3;
        double x2 = (l + 2 * r) / 3;
        cout << fixed << setprecision(3) << x1 << "\n";
        cout.flush();
        cin >> y_1;
        cout << fixed << setprecision(3) << x2 << "\n";
        cout.flush();
        cin >> y_2;
        if (isMin) {
            if (y_1 <= y_2) {
                r = x2;
            } else {
                l = x1;
            }
        } else {
            if (y_1 <= y_2) {
                l = x1;
            } else {
                r = x2;
            }
        }
    }
    return l;
}

int main() { //guesses the extremum point of bimodal funtion 
    cin.tie(0);
    ios::sync_with_stdio(false);
    double l = 0, r = 0;
    cin >> l >> r;
    double fl, fleps;
    double leps = l + 0.001;
    cout << fixed << setprecision(3) << l << "\n";
    cout.flush();
    cin >> fl;
    cout << fixed << setprecision(3) << leps << "\n";
    cout.flush();
    cin >> fleps;
    if (fleps > fl) {
        double ans = ternary(l, r, false);
        cout << "Obviously, the answer is " << fixed << setprecision(3) << ans << "\n";
    } else {
        double ans = ternary(l, r, true);
        cout << "Obviously, the answer is " << fixed << setprecision(3) << ans << "\n";
    }
    return 0;
}