#include <bits/stdc++.h>
using namespace std;


const double eps = 1e-12;

/* struct fraction {
    long long p, q;
    // this is q / p
    fraction(long long v): p(1), q(v) { reduce(); }
    fraction(long long q, long long p): p(p), q(q) { reduce(); }
    fraction(fraction f): p(f.p), q(f.q) {}
    void reduce() {
        long long g = __gcd(abs(p), abs(q));
        p /= g, q /= g;
        if (p < 0) p = -p, q = -q;
    }
    fraction operator+(const fraction &f) {
        fraction res(q * f.p + f.q * p, p * f.p);
        res.reduce();
        return res;
    }
    fraction operator-(const fraction &f) {
        fraction res(q * f.p - f.q * p, p * f.p);
        res.reduce();
        return res;
    }
}; */

using pll = pair<long long, long long>;
pll ar[101];

bool eq(pll a, pll b) {
    return a.first * b.second == a.second * b.first;
}

bool leq(pll a, pll b) {
    return a.first * b.second < a.second * b.first;
}

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        long long s, a, b, c; cin >> s >> a >> b >> c;
        vector<pair<long long, int>> v = { make_pair(a, 0), make_pair(b, 1), make_pair(c, 2) };
        sort(v.begin(), v.end());
        long long sum = 0;
        do {
            long long a = v[0].first, b = v[1].first, c = v[2].first;
            // double sc = (s - a - b) * a * b + (a > b ? a * a * b : a * a * b - (a * a * a / 6));

            long long sc = (s - a - b) * a * b * 2 + (a * b * (a + b));
            sum += sc;
        } while (next_permutation(v.begin(), v.end()));
        ar[i] = make_pair(sum, s * s * s);
    }
    // for (int i = 0; i < n; ++i) cout << ar[i] << ' '; cout << endl;
    vector<int> o(n);
    iota(o.begin(), o.end(), 0);
    sort(o.begin(), o.end(), [&](int i, int j) { return eq(ar[i], ar[j]) ? i < j : leq(ar[i], ar[j]); });
    for (int i = 0; i < n; ++i) cout << o[i] + 1 << ' ';
    cout << endl;
}
