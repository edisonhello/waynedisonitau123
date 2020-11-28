#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;

int main() {
    double d; cin >> d;

    double mx = d;
    mx = max(mx, d * sqrt(2));
    for (int x = 1; x <= floor(d); ++x) {
        double y = sqrt(d * d - x * x);
        if (y <= 1) {
            mx = max(mx, 1.0 + x);
        } else {
            mx = max(mx, x + y);
        }
    }

    cout << fixed << setprecision(12) << mx << '\n';
}

