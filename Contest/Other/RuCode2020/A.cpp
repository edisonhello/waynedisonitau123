#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }
    vector<int> dp(n);
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = 0;
        for (int u : g[i]) {
            if (s[i] == s[u]) dp[i] = max(dp[i], dp[u] + 1);
            else dp[i] = max(dp[i], -dp[u] + 1);
        }
    }
    constexpr int kMod = 998244353;
    vector<int> kdp(2 * n * n + 2);
    kdp[n * n] = 1;
    for (int i = 0; i < n; ++i) {
        vector<int> nxt(2 * n * n + 2);
        for (int j = -n * n; j <= n * n; ++j) {
            (nxt[j + n * n] += kdp[j + n * n]) >= kMod ? nxt[j + n * n] -= kMod : 0;
            if (s[i] == 'W' && j - dp[i] >= -n * n && j - dp[i] <= n * n) {
                (nxt[j + n * n] += kdp[j - dp[i] + n * n]) >= kMod ? nxt[j + n * n] -= kMod : 0;
            }
            if (s[i] == 'B' && j + dp[i] >= -n * n && j + dp[i] <= n * n) {
                (nxt[j + n * n] += kdp[j + dp[i] + n * n]) >= kMod ? nxt[j + n * n] -= kMod : 0;
            }
        }
        kdp = nxt;
    }
    int res = 0;
    for (int i = 1; i <= n * n; ++i) {
        (res += kdp[i + n * n]) >= kMod ? res -= kMod : 0;
    }
    cout << res << "\n";
}

