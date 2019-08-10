#include <bits/stdc++.h>
using namespace std;

struct P {
    long long x, y;
} p[2500];

long long operator ^ (const P a, const P b) { return a.x * b.y - a.y * b.x; }

struct L {
    long long a, b, c;
    L(P pa, P pb) : a(pa.y - pb.y), b(pb.x - pa.x), c(pa ^ pb) {
        long long g = __gcd(__gcd(a, b), c);
        a /= g, b /= g, c /= g;
        if (c < 0) a = -a, b = -b, c = -c; 
    }
    bool operator < (const L r) const {
        return a != r.a ? a < r.a : (b != r.b ? b < r.b : (c < r.c));
    }
};

map<long long, long long> table;

int main() {
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i].x >> p[i].y;
    }
    map<L, int> mp;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            mp[L(p[i], p[j])]++;
        }
    }
    for (int i = 1; i <= n; ++i) {
        table[1ll * i * (i - 1) / 2] = 1ll * i * (i - 1) * (i - 2) / 6;
    }
    long long ans = 1ll * n * (n - 1) * (n - 2) / 6;
    for (auto &p : mp) {
        assert(table.count(p.second));
        ans -= table[p.second];
    }
    cout << ans << endl;
}
