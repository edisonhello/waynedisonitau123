#include <bits/stdc++.h>
using namespace std;

int r[505];
double x[505];

int main() {
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) cin >> r[i];
    for (int i = 2; i <= n; ++i) {
        double xx = 0;
        for (int j = 1; j < i; ++j) {
            int tr = r[i] + r[j];
            int sr = abs(r[i] - r[j]);
            double xd = sqrt(tr * tr - sr * sr);
            xx = max(xx, x[j] + xd);
        }
        x[i] = xx;
    }
    double xmn = 1e9, xmx = -1e9;
    for (int i = 1; i <= n; ++i) {
        xmn = min(xmn, x[i] - r[i]);
        xmx = max(xmx, x[i] + r[i]);
    }
    cout << fixed << setprecision(12) << xmx - xmn << '\n';
}

