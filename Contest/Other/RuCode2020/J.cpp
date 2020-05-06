#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    const int m = 3 * n;
    vector<int> c(m);
    vector<vector<int>> p(n);
    for (int i = 0; i < m; ++i) {
        cin >> c[i];
        c[i]--;
        p[c[i]].push_back(i);
    }
    constexpr int kMod = 998244353;
    int res = 0;
    vector<int> dp(m);
    vector<vector<int>> q(n);
    vector<int> ord;
    for (int i = 0; i < 3; ++i) {
        vector<int> g(m);
        for (int j = 0; j < m; ++j) {
            g[(j - p[0][i] + m) % m] = c[j];
        }
        for (int j = 0; j < n; ++j) q[j].clear();
        ord = {0};
        for (int j = 0; j < m; ++j) {
            q[g[j]].push_back(j);
            if (g[j] != 0 && q[g[j]].size() == 2) ord.push_back(g[j]);
        }
        fill(dp.begin(), dp.end(), 0);
        dp[q[0][1]] = 1;
        for (int j = 1; j < n; ++j) {
            for (int k : {0, 2}) {
                for (int r = 1; r < 3; ++r) {
                    int x = q[ord[j]][min(k, 1)];
                    int y = q[ord[j]][max(k, 1)];
                    if (x > q[ord[j - 1]][r]) {
                        dp[y] += dp[q[ord[j - 1]][r]];
                        dp[y] >= kMod ? dp[y] -= kMod : 0;
                    }
                }
            } 
        }
        int add = 0;
        for (int j = 1; j < 3; ++j) {
            res += dp[q[ord[n - 1]][j]];
            res >= kMod ? res -= kMod : 0;
        }
    }
    cout << res << "\n";
}

