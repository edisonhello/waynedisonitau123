#pragma GCC optimize("O3", "unroll-loops")
#pragma GCC target("sse,sse2,sse3,sse4,sse4.2,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
using namespace std;

int fpow(int a, int n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = res * 1ll * a % p;
        a = a * 1ll * a % p;
        n >>= 1;
    }
    return res;
}

int root(int p) {
    int phi = p - 1;
    vector<int> d;
    for (int i = 2; i * i <= phi; ++i) {
        int c = 0;
        while (phi % i == 0) {
            phi /= i;
            ++c;
        }
        if (c > 0) d.push_back(i);
    }
    if (phi > 1) d.push_back(phi);
    for (int i = 1; i < p; ++i) {
        bool ok = true;
        for (int j = 0; j < (int)d.size(); ++j)
            ok &= fpow(i, (p - 1) / d[j], p) != 1;
        if (ok) return i;
    }
    assert(false);
}

template <typename T> tuple<T, T, T> extgcd(T a, T b) {
    if (!b) return make_tuple(a, 1, 0);
    T d, x, y;
    tie(d, x, y) = extgcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

int main() {
#ifdef ONLINE_JUDGE
    freopen("alot.in", "r", stdin);
    freopen("alot.out", "w", stdout);
#endif
    int p, q; scanf("%d%d", &p, &q);
    int g = root(p);
    vector<pair<int, int>> query;
    gp_hash_table<int, int> s;
    for (int i = 0; i < q; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        s[x]++;
        s[y]++;
        query.emplace_back(x, y);
    }
    gp_hash_table<int, int> pw;
    int x = g;
    pw[1] = 0;
    for (int i = 1; i < p - 1; ++i) {
        if (s.find(x) != s.end()) pw[x] = i;
        x = g * 1ll * x % p;
    }
    for (int i = 0; i < q; ++i) {
        int xx = query[i].first, yy = query[i].second;
        if (xx == 0) {
            if (yy == 0) puts("1");
            else if (yy == 1) puts("0");
            else puts("-1");
            continue;
        }
        if (yy == 0) {
            puts("-1");
            continue;
        }
        int a = pw[xx], b = pw[yy];
        if (b % __gcd(a, p - 1) != 0) {
            puts("-1");
            continue;
        }
        int d, x, y; tie(d, x, y) = extgcd(a, p - 1);
        long long t = x * 1ll * (b / d);
        t %= ((p - 1) / d);
        if (t < 0)
            t += (p - 1) / d;
        printf("%lld\n", t);
    }
}
