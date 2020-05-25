#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> w(n + 1);
    for (int i = 0; i < n + 1; ++i) cin >> w[i];
    vector<int> s(n);
    vector<vector<int>> g(n + n + 1);
    vector<bool> root(n, true);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        for (int j = 0; j < 2; ++j) {
            int x;
            cin >> x;
            if (x > 0) {
                g[i].push_back(x - 1);
                root[x - 1] = false;
            } else {
                g[i].push_back(-x - 1 + n);
            }
        }
    }
    int rt = 0;
    while (rt < n && !root[rt]) rt++;
    assert(rt < n);
    vector<int> fa(n + n + 1);
    vector<int> dep(n + n + 1);
    vector<int> tin(n + n + 1), tout(n + n + 1);

    function<void(int, int)> Dfs = [&](int x, int p) {
        static int stamp = 0;
        tin[x] = stamp++;
        for (int u : g[x]) {
            dep[u] = dep[x] + 1;
            Dfs(u, x);
        }
        tout[x] = stamp;
    };

    Dfs(rt, -1);
    int m = n + n + 1;
    vector<int64_t> tree(4 * m);
    vector<int> rev(n + n + 1);
    for (int i = 0; i < n + n + 1; ++i) rev[tin[i]] = i;
    
    auto Build = [&]() {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (r -  l == 1) {
                if (rev[l] >= n) tree[o] = w[rev[l] - n];
                return;
            }
            int m = (l + r) >> 1;
            self(self, l, m, o * 2 + 1);
            self(self, m, r, o * 2 + 2);
            tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
        };

        _(_, 0, m);
    };

    auto Query = [&](int ql, int qr) {
        auto _ = [&](auto self, int l, int r, int o = 0) -> int64_t {
            if (l >= qr || ql >= r) return 0;
            if (l >= ql && r <= qr) return tree[o];
            int m = (l + r) >> 1;
            return self(self, l, m, o * 2 + 1) + self(self, m, r, o * 2 + 2);
        };

        return _(_, 0, m);
    };

    auto Modify = [&](int p, int v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (r -  l == 1) {
                tree[o] = v;
                return;
            }
            int m = (l + r) >> 1;
            if (p < m) self(self, l, m, o * 2 + 1);
            else self(self, m, r, o * 2 + 2);
            tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
        };
        _(_, 0, m);
    };

    Build();
    while (q--) {
        int t;
        cin >> t;
        if (t == 2) {
            int x;
            cin >> x;
            x--;
            assert(g[x].size() == 2);
            int64_t a = Query(tin[g[x][0]], tout[g[x][0]]);
            int64_t b = Query(tin[g[x][1]], tout[g[x][1]]);
            long double r = (long double)(s[x] * b) / (a + b);
            cout << fixed << setprecision(20) << r << "\n";
        } else {
            int x, v;
            cin >> x >> v;
            x--;
            Modify(tin[x + n], v);
        }
    }
}

