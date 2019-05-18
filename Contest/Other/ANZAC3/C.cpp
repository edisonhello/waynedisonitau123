#include <bits/stdc++.h>
#define y1 asdhj
using namespace std;

int main() {
    long long x, y; scanf("%lld%lld", &x, &y);
    long long x1, y1, x2, y2; scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);

    long long a = x;
    long long b = y;
    if (__gcd(a, b) == 1) {
        cout << "Yes" << endl;
        return 0;
    }

    auto check = [&](long long x, long long y) -> bool {
        return x >= x1 && x <= x2 && y >= y1 && y <= y2;
    };

    long long g = __gcd(a, b);
    if (check(a / g, b / g) && check(a - a / g, b - b / g)) {
        cout << "Yes" << endl;
    } else {
        if (!check(a / g, b / g)) {
            cout << "No" << endl;
            cout << a / g << ' ' << b / g << endl;
        } else {
            long long z = 1;
            for (int d = 60; d >= 0; --d) {
                long long t = z + (1ll << d);
                if (a / g >= 1000000000000000000 / t || 
                    b / g >= 1000000000000000000 / t) continue;
                long long tx = a / g * t;
                long long ty = b / g * t;

                if (check(tx, ty)) z = t;
            }

            cout << "No" << endl;
            cout << a / g * (z + 1) << ' ' << b / g * (z + 1) << endl;
        }
    }
}
