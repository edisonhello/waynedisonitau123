#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, s, t;
    cin >> n >> k >> s >> t;
    s--;
    vector<int> a(k), b(k), uf(n), ed(n), fa(n, -1);
    for (int i = 0; i < n; ++i) uf[i] = i;

    function<int(int)> Find = [&](int x) {
        if (x == uf[x]) return x;
        return uf[x] = Find(uf[x]);
    };

    auto Merge = [&](int x, int y) {
        x = Find(x);
        y = Find(y);
        uf[x] = y;
    };

    vector<vector<int>> g(n + 1);
    vector<bool> root(n, true);
    for (int i = 0; i < k; ++i) {
        cin >> a[i] >> b[i];
        a[i]--;
        b[i]--;
        if (Find(a[i]) == Find(b[i])) {
            cout << "0\n";
            return 0;
        }
        Merge(a[i], b[i]);
        g[b[i]].push_back(a[i]);
        root[a[i]] = false;
        fa[a[i]] = b[i];
    }

    for (int i = 0; i < n; ++i) {
        if (root[i]) {
            fa[i] = n;
            g[n].push_back(i);
        }
    }

    constexpr int kMod = 1'000'000'000 + 7;
    vector<vector<int>> comb(n + 2, vector<int>(n + 2));
    for (int i = 0; i <= n + 1; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % kMod;
        }
    }
    vector<int> fc(n + 2, 1), iv(n + 2, 1);
    for (int i = 1; i <= n + 1; ++i) {
        fc[i] = 1LL * fc[i - 1] * i % kMod;
    }

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    iv[n + 1] = fpow(fc[n + 1], kMod - 2);
    for (int i = n; i >= 0; --i) {
        iv[i] = 1LL * iv[i + 1] * (i + 1) % kMod;
    }
    vector<int> sz(n + 1);
    vector<vector<int>> dp(n + 1, vector<int>(n + 2));
    vector<int> ndp(n + 1);
    vector<int> cover(n + 1);

    auto Dfs = [&](auto self, int x, int p) -> void {
        cover[x] = (x == s);
        sz[x] = 1;
        for (int u : g[x]) {
            self(self, u, x);
            cover[x] |= cover[u];
            sz[x] += sz[u];
        }
        if (!cover[x] || x == s) {
            int prv = 0;
            ndp[x] = 1;
            for (int u : g[x]) {
                prv += sz[u];
                ndp[x] = 1LL * ndp[x] * ndp[u] % kMod;
                ndp[x] = 1LL * ndp[x] * comb[prv][sz[u]] % kMod;
            }
            if (x == s) {
                dp[x][sz[x]] = ndp[x];
            }
        } else {
            int z = -1;
            for (int u : g[x]) {
                if (cover[u]) z = u;
            }
            assert(z != -1);
            int prod = 1, prv = 0;
            for (int u : g[x]) {
                if (u == z) continue;
                prv += sz[u];
                prod = 1LL * prod * ndp[u] % kMod;
                prod = 1LL * prod * comb[prv][sz[u]] % kMod;
            }
            int other = sz[x] - sz[z] - 1;
            for (int i = 1; i <= sz[z]; ++i) {
                for (int k = 0; k <= other; ++k) {
                    int j = i + k;
                    int ways = 1LL * comb[j - 1][i - 1] * comb[sz[x] - j - 1][sz[z] - i] % kMod;
                    dp[x][j] += 1LL * dp[z][i] * ways % kMod;
                    if (dp[x][j] >= kMod) dp[x][j] -= kMod;
                }
            }
            for (int j = 1; j < sz[x]; ++j) dp[x][j] = 1LL * dp[x][j] * prod % kMod;
        }
        // cout << "ndp[" << x << "] = " << ndp[x] << endl;
        // for (int i = 1; i <= sz[x]; ++i) cout << "dp[" << x << "][" << i << "] = " << dp[x][i] << endl;
    };

    Dfs(Dfs, n, -1);
    cout << dp[n][t] << endl;
}

