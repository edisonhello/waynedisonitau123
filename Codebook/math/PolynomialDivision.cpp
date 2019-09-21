vector<int> inverse(const vector<int> &v, int n) {
    vector<int> q(1, fpow(v[0], mod - 2));
    for (int i = 2; i <= n; i <<= 1) {
        vector<int> fv(v.begin(), v.begin() + i); 
        vector<int> fq(q.begin(), q.end());
        fv.resize(2 * i), fq.resize(2 * i);
        ntt(fq, 2 * i), ntt(fv, 2 * i);
        for (int j = 0; j < 2 * i; ++j) {
            fv[j] = fv[j] * 1ll * fq[j] % mod * 1ll * fq[j] % mod;
        }
        intt(fv, 2 * i);
        vector<int> res(i);
        for (int j = 0; j < i; ++j) {
            res[j] = mod - fv[j];
            if (j < (i >> 1)) (res[j] += 2 * q[j] % mod) %= mod;
        }
        q = res;
    }
    return q;
}
vector<int> divide(const vector<int> &a, const vector<int> &b) {
    // leading zero should be trimmed
    int n = (int)a.size(), m = (int)b.size();
    int k = 2;
    while (k < n - m + 1) k <<= 1;
    vector<int> ra(k), rb(k);
    for (int i = 0; i < min(n, k); ++i) ra[i] = a[n - i - 1];
    for (int i = 0; i < min(m, k); ++i) rb[i] = b[m - i - 1];
    vector<int> rbi = inverse(rb, k);
    vector<int> res = convolution(rbi, ra);
    res.resize(n - m + 1);
    reverse(res.begin(), res.end());
    return res;
}
