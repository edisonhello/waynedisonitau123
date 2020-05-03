#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }
        int m;
        cin >> m;
        vector<vector<int>> g(n);
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<vector<vector<double>>> dp(n, vector<vector<double>>(n, vector<double>(2)));
        vector<vector<vector<bool>>> used(n, vector<vector<bool>>(n, vector<bool>(2)));

        auto Between = [&](int l, int r, int u) {
            if (l < r) {
                return u >= l && u <= r;
            }
            return u >= l || u <= r;
        };

        auto Dist = [&](int u, int v) {
            return hypot(x[u] - x[v], y[u] - y[v]);
        };

        function<double(int, int, int)> Dfs = [&](int l, int r, int p) {
            if (l == r) return 0.0;
            if (used[l][r][p]) return dp[l][r][p];
            double res = 0.0;
            if (p == 0) {
                for (int u : g[l]) {
                    if (!Between(l, r, u)) continue;
                    if (u == r) continue;
                    res = max(res, Dist(l, u) + max(Dfs(l, u, 1), Dfs(u, r, 0)));
                }
            } else {
                for (int u : g[r]) {
                    if (!Between(l, r, u)) continue;
                    if (u == l) continue;
                    res = max(res, Dist(u, r) + max(Dfs(u, r, 0), Dfs(l, u, 1)));
                }
            }
            used[l][r][p] = true;
            dp[l][r][p] = res;
            return res;
        };

        double res = 0.0;
        for (int i = 0; i < n; ++i) {
            for (int u : g[i]) {
                res = max(res, Dist(i, u) + max(Dfs(i, u, 1), Dfs(u, i, 0)));
            }
        }
        cout << fixed << setprecision(20) << res << "\n";
    }
    return 0;
}

