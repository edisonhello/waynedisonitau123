template <long long mod, long long root>
struct NTT {
    vector<long long> omega;
    NTT() {
        omega.resize(maxn + 1);
        long long x = fpow(root, (mod - 1) / maxn);
        omega[0] = 1ll;
        for (int i = 1; i <= maxn; ++i)
            omega[i] = omega[i - 1] * x % mod;
    }
    long long fpow(long long a, long long n) {
        (n += mod - 1) %= mod - 1;
        long long r = 1;
        for (; n; n >>= 1) {
            if (n & 1) (r *= a) %= mod;
            (a *= a) %= mod;
        }
        return r;
    }
    void bitrev(vector<long long> &v, int n) {
        int z = __builtin_ctz(n) - 1;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            for (int j = 0; j <= z; ++j) x ^= (i >> j & 1) << (z - j);
            if (x > i) swap(v[x], v[i]);
        }
    }
    void ntt(vector<long long> &v, int n) {
        bitrev(v, n);
        for (int s = 2; s <= n; s <<= 1) {
            int z = s >> 1;
            for (int i = 0; i < n; i += s) {
                for (int k = 0; k < z; ++k) {
                    long long x = v[i + k + z] * omega[maxn / s * k] % mod; 
                    v[i + k + z] = (v[i + k] + mod - x) % mod;
                    (v[i + k] += x) %= mod; 
                }
            }
        }
    }
    void intt(vector<long long> &v, int n) {
        ntt(v, n);
        for (int i = 1; i < n / 2; ++i) swap(v[i], v[n - i]);
        long long inv = fpow(n, -1);
        for (int i = 0; i < n; ++i) (v[i] *= inv) %= mod;
    }
    vector<long long> operator()(vector<long long> a, vector<long long> b) {
        int sz = 1;
        while (sz < a.size() + b.size() - 1) sz <<= 1;
        while (a.size() < sz) a.push_back(0);
        while (b.size() < sz) b.push_back(0);
        ntt(a, sz), ntt(b, sz);
        vector<long long> c(sz);
        for (int i = 0; i < sz; ++i) c[i] = a[i] * b[i] % mod;
        intt(c, sz);
        while (c.size() && c.back() == 0) c.pop_back();
        return c;
    }
};

vector<long long> conv(vector<long long> a, vector<long long> b) {
    NTT<mod1, root1> conv1;
    NTT<mod2, root2> conv2;
    vector<long long> pa(a.size()), pb(b.size());
    for (int i = 0; i < (int)a.size(); ++i) pa[i] = (a[i] % mod1 + mod1) % mod1;
    for (int i = 0; i < (int)b.size(); ++i) pb[i] = (b[i] % mod1 + mod1) % mod1;
    vector<long long> c1 = conv1(pa, pb);
    for (int i = 0; i < (int)a.size(); ++i) pa[i] = (a[i] % mod2 + mod2) % mod2;
    for (int i = 0; i < (int)b.size(); ++i) pb[i] = (b[i] % mod2 + mod2) % mod2;
    vector<long long> c2 = conv2(pa, pb);
    long long x = conv2.fpow(mod1, -1);
    long long y = conv1.fpow(mod2, -1);
    long long prod = mod1 * mod2;
    vector<long long> res(c1.size());
    for (int i = 0; i < c1.size(); ++i) {
        long long z = ((ull)fmul(c1[i] * mod2 % prod, y, prod) + (ull)fmul(c2[i] * mod1 % prod, x, prod)) % prod;
        if (z >= prod / 2) z -= prod;
        res[i] = z;
    }
    return res;
}
