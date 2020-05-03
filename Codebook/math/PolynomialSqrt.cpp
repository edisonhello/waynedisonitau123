vector<int> solve(vector<int> b, int n) {
    if (n == 1) return {sqr[b[0]]};
    vector<int> h = solve(b, n >> 1); h.resize(n);
    vector<int> c = inverse(h, n);
    h.resize(n << 1); c.resize(n << 1);
    vector<int> res(n << 1);
    conv.ntt(h, n << 1);
    for (int i = n; i < (n << 1); ++i) b[i] = 0;
    conv.ntt(b, n << 1);
    conv.ntt(c, n << 1);
    for (int i = 0; i < (n << 1); ++i) res[i] = 1ll * (h[i] + 1ll * c[i] * b[i] % mod) % mod * inv2 % mod;
    conv.intt(res, n << 1);
    for (int i = n; i < (n << 1); ++i) res[i] = 0;
    return res;
}

