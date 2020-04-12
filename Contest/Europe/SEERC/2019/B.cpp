#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    constexpr int kS = 1000;
    constexpr int64_t kInf = 1'000'000'000'000'000;
    vector<vector<int64_t>> dp(s1, vector<int64_t>(kS + 1, kInf));
    dp[0][0] = 0;
    vector<vector<int64_t>> suff(n + 1, vector<int64_t>(kS + 1, kInf));
    suff[n][0] = 0;
    vector<int> x(n), y(n), t(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> t[i] >> y[i] >> r[i];
    }
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int i, int j) { return x[i] < x[j]; });
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j <= kS; ++j) {
            if (suff[i + 1][j] == kInf) continue;
            suff[i][j] = min(suff[i][j], suff[i + 1][j]);
            if (j + y[ord[i]] <= kS) {
                suff[i][j + y[ord[i]]] = min(suff[i][j + y[ord[i]]], suff[i + 1][j] + r[ord[i]]);
            }
        }
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = kS - 1; j >= 0; --j) {
            suff[i][j] = min(suff[i][j], suff[i][j + 1]);
        }
    }
    vector<vector<int64_t>> nxt(s1, vector<int64_t>(kS + 1, kInf));
    int64_t res = kInf;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < s1; ++j) {
            for (int k = 0; k <= kS; ++k) {
                nxt[j][k] = kInf;
            }
        }
        for (int j = 0; j < s1; ++j) {
            for (int k = 0; k <= kS; ++k) {
                if (dp[j][k] == kInf) continue;
                if (j + x[ord[i]] >= s1) {
                    int need = max(0, s1 + s2 - k - (j + x[ord[i]]));
                    res = min(res, dp[j][k] + t[ord[i]] + suff[i + 1][need]);
                }
                if (j + x[ord[i]] < s1) {
                    nxt[j + x[ord[i]]][k] = min(nxt[j + x[ord[i]]][k], dp[j][k] + t[ord[i]]);
                }
                if (k + y[ord[i]] <= kS) {
                    nxt[j][k + y[ord[i]]] = min(nxt[j][k + y[ord[i]]], dp[j][k] + r[ord[i]]);
                }
            }
        }
        for (int j = 0; j < s1; ++j) {
            for (int k = 0; k <= kS; ++k) {
                dp[j][k] = min(dp[j][k], nxt[j][k]);
            }
        }
    }
    if (res == kInf) res = -1;
    cout << res << "\n";
    return 0;
}

