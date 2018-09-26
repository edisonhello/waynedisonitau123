const int maxn = 262144;
const long long mod = 2013265921, root = 31;
long long omega[maxn + 1];

long long fpow(long long a, long long n) {
    (n += mod - 1) %= mod - 1;
    long long r = 1;
    for (; n; n >>= 1) {
        if (n & 1) (r *= a) %= mod;
        (a *= a) %= mod;
    }
    return r;
}

void prentt() {
    long long x = fpow(root, (mod - 1) / maxn);
    omega[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        omega[i] = omega[i - 1] * x % mod;
}

void bitrev(vector<long long> &v, int n) {
    int z = __builtin_ctz(n) - 1;
    for (int i = 0; i < n; ++i) {
        int x = 0;
        for (int j = 0; j <= z; ++j) x ^= ((i >> j & 1) << (z - j));
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
    reverse(v.begin() + 1, v.end());
    long long inv = fpow(n, mod - 2);
    for (int i = 0; i < n; ++i) (v[i] *= inv) %= mod;
}

vector<long long> conv(vector<long long> a, vector<long long> b) {
    int sz = 1;
    while (sz < a.size() + b.size() - 1) sz <<= 1;
    vector<long long> c(sz);
    while (a.size() < sz) a.push_back(0);
    while (b.size() < sz) b.push_back(0);
    ntt(a, sz), ntt(b, sz);
    for (int i = 0; i < sz; ++i) c[i] = a[i] * b[i] % mod;
    intt(c, sz);
    while (c.size() && c.back() == 0) c.pop_back();
    return c;
}
