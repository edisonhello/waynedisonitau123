#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int N, B, S;
    cin >> N >> B >> S;
    vector<int> s(N), a(N), b(N), c(N), w(N), v(N);
    vector<vector<int>> event(S);
    for (int i = 0; i < N; ++i) {
        cin >> s[i] >> a[i] >> b[i] >> c[i] >> w[i] >> v[i];
        s[i]--;
        event[s[i]].push_back(i);
    }

    constexpr int64_t kInf = 1'000'000'000'000'000;
    auto GetDP = [&](int p) {
        vector<int> ds;
        for (int u : event[p]) ds.push_back(b[u]);
        sort(ds.begin(), ds.end());
        ds.resize(unique(ds.begin(), ds.end()) - ds.begin());

        int M = ds.size();
        vector<vector<int64_t>> dp(M, vector<int64_t>(B + 1, -kInf));
        vector<int64_t> res(B + 1, 0);

        vector<vector<int>> ev(M);
        for (int u : event[p]) {
            int t = lower_bound(ds.begin(), ds.end(), b[u]) - ds.begin();
            ev[t].push_back(u);
        }
        for (int i = 0; i < M; ++i) {
            for (int u : ev[i]) {
                int l = lower_bound(ds.begin(), ds.end(), a[u]) - ds.begin();
                for (int j = c[u] * w[u]; j <= B; ++j) {
                    if (j == c[u] * w[u]) dp[i][j] = max(dp[i][j], static_cast<int64_t>(v[u]));
                    if (l > 0) {
                        dp[i][j] = max(dp[i][j], dp[l - 1][j - c[u] * w[u]] + v[u]);
                    }
                }
            }
            for (int j = 0; j <= B; ++j) res[j] = max(res[j], dp[i][j]);
            if (i > 0) {
                for (int j = 0; j <= B; ++j) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
            }
        }
        return res;
    };

    vector<vector<int64_t>> dps(S);
    for (int i = 0; i < S; ++i) dps[i] = GetDP(i);

    vector<int64_t> dp(B + 1, -kInf);
    dp[0] = 0;
    for (int i = 0; i < S; ++i) {
        vector<int64_t> nxt(B + 1, -kInf);
        for (int j = 0; j <= B; ++j) {
            for (int k = 0; j + k <= B; ++k) nxt[j + k] = max(nxt[j + k], dp[j] + dps[i][k]);
        }
        dp = nxt;
    }
    int64_t ans = -kInf;
    for (int i = 0; i <= B; ++i) ans = max(ans, dp[i]);
    cout << ans << "\n";
}
