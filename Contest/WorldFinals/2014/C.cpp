#include <bits/stdc++.h>
using namespace std;

struct Fraction {
    int64_t a, b;

    Fraction(int64_t a) : a(a), b(1) {}
    Fraction(int64_t a, int64_t b) : a(a), b(b) {  Reduce(); }

    void Reduce() {
        if (b < 0) {
            a = -a;
            b = -b;
        }
        int64_t g = __gcd(abs(a), abs(b));
        a /= g;
        b /= g;
    }

    bool operator<(const Fraction &f) const {
        return a * f.b < b * f.a;
    }

    bool operator==(const Fraction &f) const {
        return a * f.b < b * f.a;
    }

    bool operator>(const Fraction &f) const {
        return a * f.b > b * f.a;
    }
    bool operator>=(const Fraction &f) const {
        return a * f.b >= b * f.a;
    }
};

int main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];
    for (int i = 0; i < n; ++i) {
        x[i] *= 6;
        y[i] *= 6;
    }
    int64_t area = 0;
    for (int i = 0; i < n; ++i) {
        int64_t cross = 1LL * x[i] * y[(i + 1) % n] - 1LL * x[(i + 1) % n] * y[i];
        area += cross;
    }
    assert(area % 2 == 0);
    area /= 2;
    if (area < 0) {
        vector<int> nx(n), ny(n);
        for (int i = 0; i < n; ++i) {
            nx[(n - i) % n] = x[i];
            ny[(n - i) % n] = y[i];
        }
        x = nx;
        y = ny;
        area = -area;
    }
    int64_t sx = 0, sy = 0;
    for (int i = 0; i < n; ++i) {
        int64_t cross = (1LL * x[i] * y[(i + 1) % n] - 1LL * x[(i + 1) % n] * y[i]) / 2;
        int xc = (x[i] + x[(i + 1) % n]) / 3;
        int yc = (y[i] + y[(i + 1) % n]) / 3;
        sx += cross * xc;
        sy += cross * yc;
    }
    int xl = 1e9, xr = -1e9;
    for (int i = 0; i < n; ++i) {
        if (y[i] == 0) {
            xl = min(xl, x[i]);
            xr = max(xr, x[i]);
        }
    }

    Fraction lb(0);
    Fraction rb(2'000'000'000);

    if (xl < x[0]) {
        Fraction b(area * xl - sx, x[0] - xl);
        lb = max(lb, b);
    } else if (xl > x[0]) {
        Fraction b(area * xl - sx, x[0] - xl);
        rb = min(rb, b);
    } else {
        if (area * xl > sx) {
            cout << "unstable\n";
            return 0;
        }
    }

    if (xr < x[0]) {
        Fraction b(xr * area - sx, x[0] - xr);
        rb = min(rb, b);
    } else if (xr > x[0]) {
        Fraction b(xr * area - sx, x[0] - xr);
        lb = max(lb, b);
    } else {
        if (sx > xr * area) {
            cout << "unstable\n";
            return 0;
        }
    }

    if (lb > rb) {
        cout << "unstable\n";
        return 0;
    }

    int64_t a = (lb.a) / (36 * lb.b);
    int64_t b = (rb.a + 36 * rb.b - 1) / (36 * rb.b);

    if (rb >= Fraction(2'000'000'000)) {
        cout << a << " .. " << "inf\n";
    } else {
        cout << a << " .. " << b << "\n";
    }
    return 0;
}

