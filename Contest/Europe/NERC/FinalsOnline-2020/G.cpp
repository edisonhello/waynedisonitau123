#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

bool same(double a, double b) {
    return abs(a - b) < eps;
}

struct P {
    double x, y;
    P() = default;
    P(double x, double y) : x(x), y(y) {}
    double operator^ (P b) { return x * b.y - y * b.x; }
    P operator+ (P b) { return P(x + b.x, y + b.y); }
    P operator- (P b) { return P(x - b.x, y - b.y); }
    P operator/ (double b) { return P(x / b, y / b); }
    double operator* (P b) { return x * b.x + y * b.y; }
    double abs() { return hypot(x, y); }
};

struct L {
    P pa, pb;
    double a, b, c;
    L() = default;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb), pa(pa), pb(pb) {}
    double get_ratio(P p) { return (p - pa) * (pb - pa) / ((pb - pa).abs() * (pb - pa).abs()); }
};

bool parallel(L x, L y) {
    return same(x.a * y.b, x.b * y.a);
}

P Intersect(L x, L y) {
    return P(-x.b * y.c + x.c * y.b, x.a * y.c - x.c * y.a) / (-x.a * y.b + x.b * y.a); 
}

int main() {
    constexpr int kP = 1'000'000'000 + 7;
    vector<int> fac(4'000'000, 1);
    vector<int> inv(4'000'000, 1);

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kP;
            a = 1LL * a * a % kP;
            n >>= 1;
        }
        return res;
    };

    for (int i = 1; i < 4'000'000; ++i) {
        fac[i] = 1LL * fac[i - 1] * i % kP;
        inv[i] = fpow(fac[i], kP - 2);
    }

    auto Get = [&](int n, int k) -> int {
        if (n < k || k < 0) return 0;
        return 1LL * fac[n] * inv[k] % kP * inv[n - k] % kP;
    };

    int q; cin >> q; while (q--) {
        P a, b, c;
        cin >> a.x >> a.y;
        cin >> b.x >> b.y;
        cin >> c.x >> c.y;
        L la(a, b);
        L lb(b, c);
        L lc(c, a);

        int ans = 0;
        for (int i = 0; i < 2000000; ++i) {
            P pa(-i - 2000000, i - 2000000);
            P pb = pa + P(2000000, 2000000);

            L l(pa, pb);

            vector<double> ter;
            
            for (L ll : {la, lb, lc}) {
                if (parallel(l, ll)) continue;
                P px = Intersect(l, ll);
                double r = ll.get_ratio(px);
                if (r < -eps || r > 1 + eps) continue;

                ter.push_back(px.x + i);
            }

            if (ter.empty()) continue;

            // while (true) {
            //     bool dup = false;
            //     for (int i = 1; i < ter.size(); ++i) {
            //         if (abs(ter[i] - ter[0]) < eps) {
            //             dup = true;
            //         }
            //     }
            //     if (dup) {
            //         swap(ter[0], ter[ter.size() - 1]);
            //         ter.pop_back();
            //     }
            // }
            // assert(ter.size() == 2u);

            sort(ter.begin(), ter.end());

            int st = ceil(ter[0]), ed = floor(ter.back());
            int L = st, R = ed;
            ans += Get(ed + i + 1, i + 1);
            ans %= kP;
            ans += kP - Get(st + i, i + 1);
            ans %= kP;
            // cerr << "crx " << j << " in " << st << ' ' << ed << endl;
        }
        cout << ans << "\n";
    }
}

