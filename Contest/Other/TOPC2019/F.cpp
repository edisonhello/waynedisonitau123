#include <bits/stdc++.h>
#define int long long
using namespace std;

int fpow(int a, int n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1)
            res = 1LL * res * a % p;
        a = 1LL * a * a % p;
        n >>= 1;
    }
    return res;
}

int PrimitiveRoot(int p) {
    if (p == 2) return 1;
    vector<int> dv;
    for (int d = 2; 1LL * d * d <= (p - 1); ++d) {
        if ((p - 1) % d == 0) {
            dv.push_back(d);
            dv.push_back((p - 1) / d);
        }
    }
    for (int g = 2; g < p; ++g) {
        bool fl = false;
        for (int z : dv) {
            if (fpow(g, z, p) == 1) {
                fl = true;
                break;
            }
        }
        if (!fl) return g;
    }
    throw;
}

tuple<int, int, int> ExtendGcd(int a, int b) {
    if (!b) return make_tuple(a, 1, 0);
    int d, x, y; tie(d, x, y) = ExtendGcd(b, a % b);
    return make_tuple(d, y, x - (a / b) * y);
}

int DiscreteLog(int a, int b, int p) {
    if (p == 1) {
        if (!b) return a != 1;
        return -1;
    }
    if (b == 1) {
        if (a) return 0;
        return -1;
    }
    if (a % p == 0) {
        if (!b) return 1;
        return -1;
    }
    int num = 0, d = 1;
    while (true) {
        int r = __gcd(a, p);
        if (r == 1) break;
        if (b % r) return -1;
        ++num;
        b /= r, p /= r;
        d = (1LL * d * a / r) % p;
    }
    for (int i = 0, now = 1; i < num; ++i, now = 1LL * now * a % p) {
        if (now == b) return i;
    }
    int m = ceil(sqrt(p)), base = 1;
    map<int, int> mp;
    for (int i = 0; i < m; ++i) {
        if (mp.find(base) == mp.end()) mp[base] = i;
        else mp[base] = min(mp[base], i);
        base = 1LL * base * a % p;
    }
    for (int i = 0; i < m; ++i) {
        int r, x, y; tie(r, x, y) = ExtendGcd(d, p);
        x = (1LL * x * b % p + p) % p;
        if (mp.find(x) != mp.end()) return i * m + mp[x] + num;
        d = 1LL * d * base % p;
    }
    return -1;

}

int32_t main() {
    int t; scanf("%lld", &t);
    while (t--) {
        int p, a0, a1; scanf("%lld%lld%lld", &p, &a0, &a1);
        if (p == 2) {
            vector<int> z;
            for (int x = 0; x < 2; ++x) {
                if (((x * x - a1 * x + a0) % 2 + 2) % 2 == 0) z.push_back(x);
            }
            if (z.empty()) puts("-1");
            else if (z.size() == 1) printf("%lld %lld\n", z[0], z[0]);
            else printf("%lld %lld\n", z[0], z[1]);
            continue;
        }
        int g = PrimitiveRoot(p);
        int z = ((1LL * a1 * a1 - 4 * a0) % p + p) % p;
        int iv = fpow(2, p - 2, p);
        if (z == 0) {
            int ans = 1LL * a1 * iv % p;
            printf("%lld %lld\n", ans, ans);
            continue;
        }
        int r = DiscreteLog(g, z, p);
        if (r & 1) {
            puts("-1");
            continue;
        }
        int s = fpow(g, r / 2, p);
        int k0 = 1LL * (a1 + s) * iv % p;
        int k1 = 1LL * (a1 + p - s) * iv % p;
        assert((k0 * k0 % p + a0 + p - a1 * k0 % p) % p == 0);
        assert((k1 * k1 % p + a0 + p - a1 * k1 % p) % p == 0);
        if (k0 > k1) swap(k0, k1);
        printf("%lld %lld\n", k0, k1);

    }
    return 0;
}
