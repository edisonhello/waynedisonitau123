#include <bits/stdc++.h>
#define data __float128
using namespace std;

// using data = __float128;

struct cplx {
    data re, im;
    cplx(): re(0), im(0) {}
    cplx(data r, data i): re(r), im(i) {}
    cplx(double r, double i): re(r), im(i) {}
    cplx operator+(const cplx &rhs) const { return cplx(re + rhs.re, im + rhs.im); }
    cplx operator-(const cplx &rhs) const { return cplx(re - rhs.re, im - rhs.im); }
    cplx operator*(const cplx &rhs) const { return cplx(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re); }
    cplx conj() const { return cplx(re, -im); }
};

const int maxn = 1048576;
const int mod = 1000000 + 3;
const long long mod1 = 1107296257;
const long long mod2 = 2013265921;
const long long root1 = 10;
const long long root2 = 31;
const double pi = acos(-1);

template <long long mod, long long root> 
struct NTT {
    vector<long long> omega;
    long long fpow(long long a, long long n) {
        omega.resize(maxn + 1);
        (n += mod - 1) %= (mod - 1);
        long long r = 1;
        for (; n; n >>= 1) {
            if (n & 1) (r *= a) %= mod;
            (a *= a) %= mod;
        }
        return r;
    }
    NTT() {
        long long x = fpow(root, (mod - 1) / maxn);
        omega[0] = 1;
        for (int i = 1; i <= maxn; ++i)
            omega[i] = omega[i - 1] * x % mod;
    }
    void bitrev(vector<long long> &v, int n) {
        int z = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (int j = 0; (1 << j) < n; ++j) x ^= (((i >> j & 1)) << (z - j));
            if (x > i) swap(v[i], v[x]);
        }
    }
    void ntt(vector<long long> &v, int n) {
        bitrev(v, n);
        for (int s = 2; s <= n; s <<= 1) {
            int z = s >> 1;
            for (int i = 0; i < n; i += s) {
                for (int k = 0; k < z; ++k) {
                    long long x = v[i + z + k] * omega[maxn / s * k] % mod;
                    v[i + z + k] = (v[i + k] + mod - x) % mod; 
                    v[i + k] = (v[i + k] + x) % mod;
                }
            }
        }
    }
    void intt(vector<long long> &v, int n) {
        ntt(v, n);
        reverse(v.begin() + 1, v.end());
        long long inv = fpow(n, mod - 2);
        for (int i = 0; i < n; ++i) v[i] = v[i] * inv % mod;
    }
    vector<long long> conv(vector<long long> a, vector<long long> b) {
        int sz = 1;
        while (sz < a.size() + b.size() - 1) sz <<= 1;
        while (a.size() < sz) a.push_back(0);
        while (b.size() < sz) b.push_back(0);
        ntt(a, sz), ntt(b, sz);
        vector<long long> c(sz);
        for (int i = 0; i < sz; ++i) c[i] = a[i] * b[i] % mod;
        intt(c, sz);
        return c;
    }
};


int l[maxn], t[maxn];
int f[maxn], inv[maxn];

int fpow(int x, int n) {
    int r = 1;
    while (n) {
        if (n & 1) r = r * 1ll * x % mod;
        x = x * 1ll * x % mod;
        n >>= 1;
    }
    return r;
}

int cnk(int n, int k) {
    if (n < k || k < 0) return 0;
    return f[n] * 1ll * inv[k] % mod * inv[n - k] % mod;
}

long long fmul(long long a, long long b, long long p) {
    long long r = 0;
    b %= p;
    while (b) {
        if (b & 1) (r += a) %= p;
        (a += a) %= p;
        b >>= 1;
    }
    return r;
}

int main() {
    int n, a, b, c; scanf("%d%d%d%d", &n, &a, &b, &c);
    for (int i = 1; i <= n; ++i) scanf("%d", &l[i]);
    for (int i = 1; i <= n; ++i) scanf("%d", &t[i]);
    f[0] = inv[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        f[i] = f[i - 1] * 1ll * i % mod;
        inv[i] = fpow(f[i], mod - 2);
    }
    int ans = 0;
    int x = 0;
    for (int i = 2; i <= n; ++i) {
        int comb = cnk(n + n - 2 - i, n - 2);
        comb = comb * 1ll * fpow(b, n - i) % mod * l[i] % mod;
        x += comb;
        x %= mod;
    }
    ans = ans + 1ll * fpow(a, n - 1) * x % mod;
    // printf("%d\n", 1ll * fpow(a, n - 1) * x % mod);
    ans %= mod;
    int y = 0;
    for (int i = 2; i <= n; ++i) {
        int comb = cnk(n + n - 2 - i, n - 2);
        comb = comb * 1ll * fpow(a, n - i) % mod * t[i] % mod;
        y += comb;
        y %= mod;
    }
    ans = ans + 1ll * fpow(b, n - 1) * y % mod;
    // printf("%d\n", 1ll * fpow(b, n - 1) * y % mod);
    ans %= mod;
    vector<long long> p(n + n + 1), q(n + 1);
    for (int i = 0; i <= n + n; ++i) p[i] = f[i];
    for (int i = 0; i <= n - 2; ++i) q[n - i] = fpow(b, i) * 1ll * inv[i] % mod;
    NTT<mod1, root1> solver1;
    NTT<mod2, root2> solver2;
    vector<long long> res1 = solver1.conv(p, q);
    vector<long long> res2 = solver2.conv(p, q);
    int z = 0;
    for (int i = 0; i <= n - 2; ++i) {
        long long inv1 = solver1.fpow(mod2, mod1 - 2);
        long long inv2 = solver2.fpow(mod1, mod2 - 2);
        long long all = mod1 * mod2;
        long long x = fmul(inv1 * res1[n + i] % all, mod2, all) + fmul(inv2 * res2[n + i] % all, mod1, all);
        x = x % all;
        assert(x <= all / 2);
        x = x % mod;
        z = z + x * 1ll * fpow(a, i) % mod * inv[i] % mod;
        z %= mod;
        /* int x = 0;
        for (int j = 0; j <= n - 2; ++j) {
            x = x + 1ll * f[i + j] * fpow(b, j) % mod * inv[j] % mod;
            x %= mod;
        }
        z = z + x * 1ll * fpow(a, i) % mod * 1ll * inv[i] % mod;
        z %= mod; */
    }
    ans = ans + 1ll * c * z % mod;
    // printf("%d\n", c * z);
    ans %= mod;
    printf("%d\n", ans);
    return 0;
}
