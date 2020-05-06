#include <bits/stdc++.h>
using namespace std;

int main() {
    auto fpow = [&](int64_t a, int64_t b, int64_t p) {
        int64_t res = 1;
        while (b > 0) {
            if (b & 1) res = (__int128)res * a % p;
            a = (__int128)a * a % p;
            b >>= 1;
        }
        return res;
    };

    auto IsPrime = [&](int64_t n) {
        static vector<int64_t> kCheck = {
            2, 325, 9375, 28178, 450775, 9780504, 1795265022
        };

        auto Check = [&](int64_t a, int64_t u, int64_t n, int t) {
            a = fpow(a, u, n);
            if (a == 0) return true;
            if (a == 1 || a == n - 1) return true;
            for (int i = 0; i < t; ++i) {
                a = (__int128)a * a % n;
                if (a == 1) return false;
                if (a == n - 1) return true;
            }
            return false;
        };

        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        int64_t u = n - 1;
        int t = 0;
        for (; !(u & 1); u >>= 1, t++);
        for (auto i : kCheck) {
            if (!Check(i, u, n, t)) return false;
        }
        return true;
    };

    auto Factorize = [&](int64_t n) {
        map<int64_t, int> cnt;

        auto f = [&](int64_t x, int64_t n , int p) {
            return ((__int128)x * x % n + p) % n;
        };

        auto PollardRho = [&](auto self, int64_t n) {
            if (n == 1) return;
            if (IsPrime(n)) {
                cnt[n] += 1;
                return;
            }
            if (n % 2 == 0) {
                cnt[2] += 1;
                self(self, n / 2);
                return;
            }
            int64_t x = 2, y = 2, d = 1, p = 1;
            while (true) {
                if (d != n && d != 1) {
                    self(self, n / d);
                    self(self, d);
                    break;
                }
                if (n == d) p++;
                x = f(x, n, p);
                y = f(f(y, n, p), n, p);
                d = __gcd(abs(x - y), n);
            }
        };
        PollardRho(PollardRho, n);
        vector<pair<int64_t, int>> res;
        for (auto it : cnt) {
            res.emplace_back(it.first, it.second);
        }
        return res;
    };

    int n, m;
    cin >> n >> m;
    vector<int64_t> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    int q;
    cin >> q;

    auto ExtGcd = [&](auto self, int64_t a, int64_t b) {
        if (!b) return make_tuple(a, (int64_t)1, (int64_t)0);
        auto [d, x, y] = self(self, b, a % b);
        return make_tuple(d, y, x - (a / b) * y);
    };

    auto Inv = [&](int64_t a, int64_t m) {
        assert(__gcd(a, m) == 1);
        auto [d, x, y] = ExtGcd(ExtGcd, a, m);
        x %= m;
        x += m;
        x %= m;
        assert((__int128)x * a % m == 1);
        return x;
    };

    while (q--) {
        int64_t v;
        cin >> v;
        auto pc = Factorize(v);
        vector<int> x(pc.size()), y(pc.size());
        vector<int64_t> na(a.begin(), a.end());
        vector<int64_t> nb(b.begin(), b.end());
        for (int i = 0; i < pc.size(); ++i) {
            for (int j = 0; j < n; ++j) {
                while (na[j] % pc[i].first == 0) {
                    x[i]++;
                    na[j] /= pc[i].first;
                }
            }
            for (int j = 0; j < m; ++j) {
                while (nb[j] % pc[i].first == 0) {
                    y[i]++;
                    nb[j] /= pc[i].first;
                }
            }
        }
        int64_t up = 1, dn = 1;
        for (int i = 0; i < n; ++i) {
            up = (__int128)up * na[i] % v;
        }
        for (int i = 0; i < m; ++i) {
            dn = (__int128)dn * nb[i] % v;
        }
        bool z = false;
        for (int i = 0; i < pc.size(); ++i) z |= x[i] < y[i];
        if (z) {
            cout << "DIVISION BY ZERO\n";
            continue;
        }
        for (int i = 0; i < pc.size(); ++i) {
            up = (__int128)up * fpow(pc[i].first, x[i] - y[i], v) % v;
        }
        up = (__int128)up * Inv(dn, v) % v;
        cout << up << "\n";
    }
    return 0;
}

