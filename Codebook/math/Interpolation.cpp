vector<int> Interp(const vector<int> &x, const vector<int> &y) {
    vector<vector<vector<int>>> v;
    int n = x.size();
    v.emplace_back(n);
    for (int i = 0; i < n; ++i) v[0][i] = {{kMod - x[i], 1}};
    while (v.back().size() > 1) {
        int n2 = v.back().size();
        vector<vector<int>> f((n2 + 1) >> 1);
        for (int i = 0; i < (n2 >> 1); ++i) f[i] = Multiply(v.back()[2 * i], v.back()[2 * i + 1]);
        if (n2 & 1) f.back() = v.back().back();
        v.push_back(f);
    }
    vector<int> df(v.back()[0].size() - 1);
    for (int i = 0; i < df.size(); ++i) df[i] = 1LL * v.back()[0][i + 1] * (i + 1) % kMod;
    vector<int> s;
    MultiEval(x, 0, n).Query(df, s, 0, n);
    vector<vector<int>> res(n);
    for (int i = 0; i < n; ++i) res[i] = {1LL * y[i] * fpow(s[i], kMod - 2) % kMod};
    for (int p = 1; p < v.size(); ++p) {
        int n2 = v[p - 1].size();
        vector<vector<int>> f((n2 + 1) >> 1);
        for (int i = 0; i < (n2 >> 1); ++i) {
            auto a = Multiply(res[i * 2], v[p - 1][2 * i + 1]);
            auto b = Multiply(res[i * 2 + 1], v[p - 1][2 * i]);
            assert(a.size() == b.size());
            f[i].resize(a.size());
            for (int j = 0; j < a.size(); ++j) f[i][j] = (a[j] + b[j]) % kMod;
        }
        if (n2 & 1) f.back() = res.back();
        res = f;
    }
    return res[0];
}
