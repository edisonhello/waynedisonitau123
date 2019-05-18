#include <bits/stdc++.h>
using namespace std;

const int maxn = 100;
const long long inf = 1e15;
int p[maxn], c[maxn];
int cand[20000];
long long dp[2][maxn][20000];
long long pref[maxn][20000];

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i) scanf("%d%d", &p[i], &c[i]);
    int sz = 0;
    vector<int> cand { 0 };
    for (int i = 1; i <= n; ++i) {
        for (int j = -n; j <= n; ++j) {
            if (p[i] + j >= 1) cand.push_back(p[i] + j);
        }
    }
    sort(cand.begin(), cand.end());
    cand.resize(unique(cand.begin(), cand.end()) - cand.begin());
    for (int i = 0; i < maxn; ++i) {
        for (int j = 0; j < 20000; ++j) dp[0][i][j] = inf;
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < maxn; ++j) {
            for (int k = 0; k < 20000; ++k) dp[i & 1][j][k] = inf;
        }
        for (int j = 0; j <= n; ++j) {
            pref[j][0] = dp[i & 1 ^ 1][j][0];
            for (int k = 1; k < cand.size(); ++k) pref[j][k] = min(dp[i & 1 ^ 1][j][k], pref[j][k - 1]);
        }
        for (int j = 0; j <= n; ++j) {
            for (int k = 1; k < cand.size(); ++k) {
                if (j && k) dp[i & 1][j][k] = min(dp[i & 1][j][k], pref[j - 1][k - 1] + 1ll * abs(cand[k] - p[i]) * c[i]);
                dp[i & 1][j][k] = min(dp[i & 1][j][k], dp[i & 1 ^ 1][j][k] + 1ll * abs(min(cand[k], p[i]) - p[i]) * c[i]);
                // printf("dp[%d][%d][%d] = %lld\n", i, j, k, dp[i & 1][j][k]);
            }
        }
    }
    long long ans = inf;
    for (int i = k; i <= n; ++i) {
        for (int j = 1; j < cand.size(); ++j) ans = min(ans, dp[n & 1][i][j]);
    }
    printf("%lld\n", ans);
    return 0;
}
