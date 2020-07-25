#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

double gdp[2][501][501];

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    vector<vector<int>> tree(n * 4);

    auto Modify = [&](int ql, int qr, int v) {
        auto _ = [&](auto self, int l, int r, int o = 0) {
            if (l >= qr || ql >= r) return;
            if (l >= ql && r <= qr) {
                tree[o].push_back(v);
                return;
            }
            int m = (l + r) >> 1;
            self(self, l, m, o * 2 + 1);
            self(self, m, r, o * 2 + 2);
        };

        _(_, 0, n);
    };

    for (int i = 0; i < n; ++i) {
        Modify(0, i, i);
        Modify(i + 1, n, i);
    }

    constexpr double kEps = 1E-9;
    double res = 0.0;

    auto Dfs = [&](auto self, int l, int r, int cnt, const vector<vector<double>> &dp, int o = 0) -> void  {
        for (int i = 0; i <= cnt; ++i) {
            for (int j = 0; j <= a; ++j) gdp[0][i][j] = dp[i][j];
        }
        int cur = 0;
        for (int u : tree[o]) {
            cur ^= 1;
            // vector<vector<double>> nxt(cnt + 2, vector<double>(a + 1));
            for (int j = 0; j <= cnt + 1; ++j) {
                for (int k = 0; k <= a; ++k) gdp[cur][j][k] = 0;
            }
            for (int j = 0; j <= cnt; ++j) {
                for (int k = 0; k <= a; ++k) {
                    double p = 1.0 * (j + 1) / (cnt + 2);
                    if (k + x[u] <= a) {
                        gdp[cur][j + 1][k + x[u]] += p * gdp[cur ^ 1][j][k];
                    }
                    gdp[cur][j][k] += (1 - p) * gdp[cur ^ 1][j][k];
                }
            }
            cnt++;
        } 
        // for (int j = 0; j < n; ++j) {
        //     for (int k = 0; k <= a; ++k) {
        //         cout << "dp[" << j << "][" << k << "] = " << dp[j][k] << endl;
        //     }
        // }
        if (r - l == 1) {
            for (int i = 0; i <= cnt; ++i) {
                for (int j = 0; j <= a; ++j) {
                    if (j + x[l] <= b) continue;
                    res += gdp[cur][i][j];
                    // res += dp[i][j] / n;
                }
            }
        } else {
            int m = (l + r) >> 1;
            vector<vector<double>> cdp(cnt + 1, vector<double>(a + 1));
            for (int i = 0; i <= cnt; ++i) {
                for (int j = 0; j <= a; ++j) cdp[i][j] = gdp[cur][i][j];
            }
            self(self, l, m, cnt, cdp, o * 2 + 1);
            self(self, m, r, cnt, cdp, o * 2 + 2);
        }
    };
    
    vector<vector<double>> dp(1, vector<double>(a + 1));
    dp[0][0] = 1.0;
    Dfs(Dfs, 0, n, 0, dp);
    cout << fixed << setprecision(20) << 1 - res << "\n";
}

