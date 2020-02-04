#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

template <int P, int R, int N>
struct NTT {
    vector<int> omega;
    NTT() {
        omega.resize(N + 1);
        int x = fpow(R, (P - 1) / N);
        omega[0] = 1;
        for (int i = 1; i <= N; ++i) omega[i] = 1LL * omega[i - 1] * x % P;
    }
    int fpow(int a, int n) {
        if (n < 0) n += P - 1;
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % P;
            a = 1LL * a * a % P;
            n >>= 1;
        }
        return res;
    }
    void Bitrev(vector<int> &v, int n) {
        int z = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
            if (x > i) swap(v[x], v[i]);
        }
    }
    void Trans(vector<int> &v, int n) {
        Bitrev(v, n);
        for (int s = 2; s <= n; s <<= 1) {
            int z = s >> 1;
            for (int i = 0; i < n; i += s) {
                for (int k = 0; k < z; ++k) {
                    int x = 1LL * v[i + k + z] * omega[N / s * k] % P;
                    v[i + k + z] = (v[i + k] + P - x) % P;
                    (v[i + k] += x) %= P;
                }
            }
        }
    }
    void InvTrans(vector<int> &v, int n) {
        Trans(v, n);
        for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]); 
        const int iv = fpow(n, P - 2) % P;
        for (int i = 0; i < n; ++i) v[i] = 1LL * v[i] * iv % P;
    }
    vector<int> Multiply(vector<int> a, vector<int> b) {
        int n = a.size(), m = b.size(), sz = 1;
        while (sz < n + m - 1) sz <<= 1;
        vector<int> c(sz);
        a.resize(sz), b.resize(sz);
        Trans(a, sz), Trans(b, sz);
        for (int i = 0; i < sz; ++i) c[i] = 1LL * a[i] * b[i] % P;
        InvTrans(c, sz);
        c.resize(n + m - 1);
        return c;
    }
};

constexpr int kMod1 = 469762049, kRoot1 = 3;
constexpr int kMod2 = 167772161, kRoot2 = 3;
const int kN = 2097152;

long long fmul(long long a, long long b, long long p) {
    long long res = 0;
    while (b > 0) {
        if (b & 1) (res += a) %= p;
        (a += a) %= p;
        b >>= 1;
    }
    return res;
}

vector<long long> Multiply(vector<int> a, vector<int> b) {
    NTT<kMod1, kRoot1, kN> conv1;
    // NTT<kMod2, kRoot2, kN> conv2;
    {
        auto res = conv1.Multiply(a, b);
        return vector<long long>(res.begin(), res.end());
    }
    // vector<int> c1 = conv1.Multiply(a, b);
    // vector<int> c2 = conv1.Multiply(a, b);
    // int x = conv2.fpow(kMod1, -1);
    // int y = conv1.fpow(kMod2, -1);
    // long long pd = 1LL * kMod1 * kMod2;
    // vector<long long> c(c1.size() + c2.size());
    // for (int i = 0; i < c1.size(); ++i) {
    //     long long z = (fmul(1LL * c1[i] * kMod2 % pd, y, pd) + fmul(1LL * c2[i] * kMod1 % pd, x, pd)) % pd;
    //     c[i] = z;
    // }
    // return c;
}

int fpow(int a, int n, int p) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = 1LL * res * a % p;
        a = 1LL * a * a % p;
        n >>= 1;
    }
    return res;
}

int Root(int p) {
    vector<int> v;
    int q = p - 1;
    for (int j = 2; j <= q; ++j) {
        int cnt = 0;
        while (q % j == 0) q /= j, ++cnt;
        if (cnt > 0) v.push_back(j);
    }
    for (int i = 1; i < p; ++i) {
        bool ok = true;
        for (int j : v) ok &= fpow(i, (p - 1) / j, p) != 1;
        if (ok) return i;
    }
    assert(false);
}

int main() {
    int p; scanf("%d", &p);
    int g = Root(p);
    vector<int> pw(p), pp(p);
    for (int i = 0, k = 1; i < p; ++i) {
        pw[k] = i;
        pp[i] = k;
        k = 1LL * k * g % p;
    }
    int n; scanf("%d", &n);
    vector<int> a(p), b(p);
    int zr = 0;
    for (int i = 0; i < n; ++i) {
        int s; scanf("%d", &s);
        if (s != 0) a[pw[s]]++, b[pw[fpow(s, p - 2, p)]]++;
        else zr++;
    }
    vector<long long> c = Multiply(a, b);
    vector<long long> d(p);
    for (int i = 0; i < c.size(); ++i) {
        int z = i % (p - 1);
        d[pp[z]] += c[i];
    }
    vector<long long> z(p);
    for (int i = 1; i < p; ++i) {
        if ((i + 3) % p == 0) continue;
        if ((i + i + 3) % p == 0) continue;
        int r = (i * 3 + 2) % p;
        r = (1LL * r * r + 5) % p;
        r = 1LL * r * fpow(1LL * (i + 3) * (i + 3) % p, p - 2, p) % p;
        int s = (i * 5 + 2) % p;
        s = 1LL * s * s % p;
        s = (s + 3LL * i * i % p) % p;
        s = 1LL * s * fpow(1LL * (i + i + 3) * (i + i + 3) % p, p - 2, p) % p;
        r = (r + s) % p;
        z[r] += d[i];
    }
    int m; scanf("%d", &m);
    long long res = 0;
    const int k913 = 13 * fpow(9, p - 2, p) % p;
    for (int i = 0; i < m; ++i) {
        int v; scanf("%d", &v);
        if (p != 3 && v == k913 && zr > 0) res += n - 1;
        if (v == 16 % p && zr > 0) res += n - 1;
        res += z[v];
    }
    printf("%lld\n", res);
    return 0;
}

