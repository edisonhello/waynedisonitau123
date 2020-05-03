vector<int> SubsetConv(int n, const vector<int> &f, const vector<int> &g) {
    const int m = 1 << n;
    vector<vector<int>> a(n + 1, vector<int>(m)), b(n + 1, vector<int>(m));
    for (int i = 0; i < m; ++i) {
        a[__builtin_popcount(i)][i] = f[i];
        b[__builtin_popcount(i)][i] = g[i];
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int s = 0; s < m; ++s) {
                if (s >> j & 1) {
                    a[i][s] += a[i][s ^ (1 << j)];
                    b[i][s] += b[i][s ^ (1 << j)];
                }
            }
        }
    }
    vector<vector<int>> c(n + 1, vector<int>(m));
    for (int s = 0; s < m; ++s) {
        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j <= i; ++j) c[i][s] += a[j][s] * b[i - j][s];
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int s = 0; s < m; ++s) {
                if (s >> j & 1) c[i][s] -= c[i][s ^ (1 << j)];
            }
        }
    }
    vector<int> res(m);
    for (int i = 0; i < m; ++i) res[i] = c[__builtin_popcount(i)][i];
    return res;
}
