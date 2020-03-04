#include <bits/stdc++.h>
using namespace std;

int pw(int b, int n, int m, int a = 1) {
    while (n) {
        if (n & 1) a = 1ll * a * b % m;
        b = 1ll * b * b % m; n >>= 1;
    }
    return a;
}

template <typename T> tuple<T, T, T> extgcd(T a,  T b) {
    if (!b) return make_tuple(a, 1, 0);
    T d, x, y;
    tie(d, x, y) = extgcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

int inv(int x, int m) {
    int y = get<1>(extgcd(x, m));
    y = (y % m + m) % m;
    // cout << "inv " << x << " in mod " << m << " = " << y << endl;
    return y;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    while (n--) {
        int x, y; cin >> x >> y;
        int g = __gcd(x, y);
        // cout << "g = " << g << endl;
        if (g <= 50000) {
            int xx = x / g, yy = y / g;
            if (xx == 1 && yy == 1) {
                cout << 4 << '\n';
                cout << 0 << ' ' << 0 << '\n';
                cout << x - 1 << ' ' << y << '\n';
                cout << 1 << ' ' << 1 << '\n';
                cout << x << ' ' << y - 1 << '\n';
            } else {
                int a = inv(yy, xx); if (a == 0) a = 1;
                int b = (1 + 1ll * a * yy) / xx;
                cout << 3 << '\n';
                cout << 0 << ' ' << 0 << '\n';
                cout << x << ' ' << y << '\n';
                cout << a << ' ' << b << '\n';
            }
        } else {
            cout << 4 << '\n';
            cout << 0 << ' ' << 0 << '\n';
            cout << x - 1 << ' ' << y << '\n';
            cout << x / g << ' ' << y / g << '\n';
            cout << x << ' ' << y - 1 << '\n';
        }
    }
}
