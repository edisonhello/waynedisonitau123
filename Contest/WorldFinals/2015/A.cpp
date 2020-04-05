#include <bits/stdc++.h>
using namespace std;

int main() {
    int p, a, b, c, d, n;
    cin >> p >> a >> b >> c >> d >> n;
    double v = -1e9, res = 0;
    for (int i = 1; i <= n; ++i) {
        double price = p * (sin(a * i + b) + cos(c * i + d) + 2);
        res = max(res, v - price);
        v = max(v, price);
    }
    cout << fixed << setprecision(10) << res << "\n";
}

