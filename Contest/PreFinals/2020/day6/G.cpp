#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    vector<int> x(n), c(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0; i < n; ++i) cin >> c[i];

    for (int i = 1; i < n; ++i) {
        assert(x[i] > x[i - 1]);
    }
    vector<int> dp(n), prv(n);
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && c[i] == c[j]) prv[j++] = i;
    }
    int res = n;

    vector<int> tree(n * 4, n);

    auto Modify = [&](int p, int v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (r - l == 1) {
                tree[o] = min(tree[o], v);
                return;
            }
            int m = (l + r) >> 1;
            if (p < m) self(self, l, m, o * 2 + 1);
            else self(self, m, r, o * 2 + 2);
            tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
        };

        _(_, 0, n);
    };

    auto Query = [&](int ql, int qr) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return n;
            if (l >= ql && r <= qr) return tree[o];
            int m = (l + r) >> 1;
            return min(self(self, l, m, o * 2 + 1), self(self, m, r, o * 2 + 2));
        };

        return _(_, 0, n);
    };

    for (int i = 0; i < n; ++i) {
        if (prv[i] == 0) {
            dp[i] = 1;
        } else {
            dp[i] = Query(prv[i], i) + 1;
            int d = x[i] - x[prv[i]];
            int y = x[prv[i] - 1];
            int z = x[prv[i]];
            int l = lower_bound(x.begin(), x.end(), 2 * y - x[i]) - x.begin();
            l = max(l, prv[prv[i] - 1]);
            int r = upper_bound(x.begin(), x.end(), 2 * z - x[i]) - x.begin();
            r = min(r, prv[i]);
            if (l < r) dp[i] = min(dp[i], Query(l, r) + 1);
        }
        Modify(i, dp[i]);
        if (prv[n - 1] == prv[i]) res = min(res, dp[i]);
    }
    cout << res << "\n";
}

