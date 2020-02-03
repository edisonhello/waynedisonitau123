template <int P>
int LinearRec(const vector<int> &s, const vector<int> &coeff, int k) {
    int n = s.size();
    auto Combine = [&](const vector<int> &a, const vector<int> &b) {
        vector<int> res(n * 2 + 1);
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= n; ++j)
                (res[i + j] += 1LL * a[i] * b[j] % P) %= P;
        }
        for (int i = 2 * n; i > n; --i) {
            for (int j = 0; j < n; ++j) 
                (res[i - 1 - j] += 1LL * res[i] * coeff[j] % P) %= P;
        }
        res.resize(n + 1);
        return res;
    };
    vector<int> p(n + 1), e(n + 1);
    p[0] = e[1] = 1;
    for (; k > 0; k >>= 1) {
        if (k & 1) p = Combine(p, e);
        e = Combine(e, e);
    }
    int res = 0;
    for (int i = 0; i < n; ++i) (res += 1LL * p[i + 1] * s[i] % P) %= P;
    return res;
}
