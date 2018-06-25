namespace lagrange {
    long long pf[maxn], nf[maxn];
    void init() {
        pf[0] = nf[0] = 1;
        for (int i = 1; i < maxn; ++i) {
            pf[i] = pf[i - 1] * i % mod;
            nf[i] = nf[i - 1] * (mod - i) % mod;
        }
    } 
    // given y: value of f(a), a = [0, n], find f(x)
    long long solve(int n, vector<long long> y, long long x) {
        if (x <= n) return y[x];
        long long all = 1;
        for (int i = 0; i <= n; ++i) (all *= (x - i + mod)) %= mod;
        long long ans = 0;
        for (int i = 0; i <= n; ++i) {
            long long z = all * fpow(x - i, -1) % mod;
            long long l = pf[i], r = nf[n - i];
            (ans += y[i] * z % mod * fpow(l * r, -1)) %= mod;
        }
        return ans;
    }
}
