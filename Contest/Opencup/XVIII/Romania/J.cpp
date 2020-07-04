#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int> sz(n);

    constexpr int kMod = 1'000'000'000 + 7;
    int res = 0;
    vector<vector<int>> comb(m + 1, vector<int>(m + 1));
    for (int i = 0; i <= m; ++i) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % kMod;
        }
    }

    vector<vector<int>> pw(n + 1, vector<int>(m + 1, 1));
    for (int i = 0; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            pw[i][j] = 1LL * pw[i][j - 1] * i % kMod;
        }
    }

    auto Solve = [&](int a, int b, int w) {
        int res = 0;
        vector<int> pref(m + 1);
        for (int y = 0; y <= m; ++y) {
            pref[y] = 1LL * comb[m][y] * pw[a][m - y] % kMod * pw[b][y] % kMod;
        }
        for (int y = 1; y <= m; ++y) {
            (pref[y] += pref[y - 1]) %= kMod;
        }

        auto Get = [&](int l, int r) {
            int res = pref[r];
            if (l > 0) {
                (res += kMod - pref[l - 1]) %= kMod;
            }
            return res;
        };

        for (int x = 0; x <= m; ++x) {
            int g = Get(x, m);
            int cf = 1LL * comb[m][x] * pw[a][x] % kMod * pw[b][m - x] % kMod;
            (res += 1LL * g * cf % kMod * x % kMod) %= kMod;
        }

        for (int x = 0; x <= m; ++x) {
            pref[x] = 1LL * comb[m][x] * pw[a][x] % kMod * pw[b][m - x] % kMod;
        }
        for (int y = 1; y <= m; ++y) {
            (pref[y] += pref[y - 1]) %= kMod;
        }
        for (int y = 0; y <= m; ++y) {
            int g = Get(y + 1, m);
            int cf = 1LL * comb[m][y] * pw[a][m - y] % kMod * pw[b][y] % kMod;
            (res += 1LL * g * cf % kMod * y % kMod) %= kMod;
        }
        res = 1LL * res * w % kMod;
        return res;
        // for (int x = 0; x <= m; ++x) {
        //     for (int y = 0; y <= m; ++y) {
        //         int ways = 1LL * pw[a][x] * pw[a][y] % kMod * pw[b][m - x] % kMod * pw[b][m - y] % kMod;
        //         ways = 1LL * ways * comb[m][x] % kMod * comb[m][y] % kMod;
        //         res += 1LL * min(x, m - y) * ways % kMod * w % kMod;
        //         res %= kMod;
        //     }
        // }
        return res;
    };

    auto Dfs = [&](auto dfs, int x, int p = -1) -> void {
        sz[x] = 1;
        for (int i = 0; i < g[x].size(); ++i) {
            int u = g[x][i].first;
            int w = g[x][i].second;
            if (u == p) continue;
            dfs(dfs, u, x);
            (res += Solve(sz[u], n - sz[u], w)) %= kMod;
            sz[x] += sz[u];
        }
    };

    Dfs(Dfs, 0);
    cout << (res + res) % kMod << "\n";
}

