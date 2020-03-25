#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    constexpr int kMod = 1'000'000'000 + 7;
    vector<int> dp(n);

    function<void(int, int)> Dfs = [&](int x, int p) {
        dp[x] = 1;
        for (int u : g[x]) {
            if (u == p) continue;
            Dfs(u, x);
            dp[x] = 1LL * dp[x] * (dp[u] + 1) % kMod;
        } 
    };

    Dfs(0, -1);
    int res = 0;
    for (int i = 0; i < n; ++i) {
        (res += dp[i]) >= kMod ? res -= kMod : 0;
    }

    
    vector<int> ans(n);

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kMod;
            a = 1LL * a * a % kMod;
            n >>= 1;
        }
        return res;
    };

    function<void(int, int, int)> Dfs2 = [&](int x, int p, int f) {
        ans[x] = 1LL * dp[x] * (f + 1) % kMod;
        for (int u : g[x]) {
            if (u == p) continue;
            ans[x] = 1LL * ans[x] * fpow(dp[u] + 1, kMod - 2) % kMod;
            Dfs2(u, x, ans[x]);
            ans[x] = 1LL * ans[x] * (dp[u] + 1) % kMod;
        } 
    };
    Dfs2(0, -1, 0);

    cout << res << " ";
    res = 0;
    for (int i = 0; i < n; ++i) {
        (res += ans[i]) >= kMod ? res -= kMod : 0;
    }
    cout << res << "\n";
}

