#include <bits/stdc++.h>
using namespace std;

const int kN = 2e5 + 5;
const int kK = 12;
const long long kInf = 1e15;
pair<int, int> v[kN];
long long dp[kN][kK];

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, k; scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; ++i) scanf("%d%d", &v[i].first, &v[i].second);
        sort(v + 1, v + n + 1);
        int ans = 0;

        auto Check = [&](int x) {
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= k + 1; ++j)
                    dp[i][j] = kInf;
            }
            dp[0][0] = 0;
            for (int i = 1; i <= n; ++i) {
                for (int j = 0; j <= k + 1; ++j) {
                    dp[i][j] = dp[i - 1][j];
                    if (j > 0 && v[i].first - dp[i - 1][j - 1] - v[i].second >= x)
                        dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + v[i].second);
                }
            }
            return dp[n][k + 1] != kInf;
        };

        for (int d = 20; d >= 0; --d) {
            if (Check(ans + (1 << d))) ans += (1 << d);
        }
        printf("%d\n", ans);
    }
    return 0;
}
