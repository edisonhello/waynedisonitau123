#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int maxw = 50000 + 5;
int dp[maxw][2][2];
pair<int, int> p[maxn];

int main() {
    int n, s; scanf("%d%d", &n, &s);
    for (int i = 0; i < n; ++i) 
        scanf("%d%d", &p[i].first, &p[i].second);

    sort(p, p + n);
    for (int i = 0; i < maxw; ++i)
        dp[i][0][1] = dp[i][1][1] = -1e9;

    dp[0][0][1] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < maxw; ++j)
            dp[j][0][i & 1] = dp[j][1][i & 1] = -1e9;


        for (int j = 0; j <= s; ++j) {
            dp[j][0][i & 1] = max(dp[j][0][i & 1], dp[j][0][i & 1 ^ 1]);
            if (i == 0 || p[i].first != p[i - 1].first)
                dp[j][0][i & 1] = max(dp[j][0][i & 1], dp[j][1][i & 1 ^ 1]);
            else
                dp[j][1][i & 1] = max(dp[j][1][i & 1], dp[j][1][i & 1 ^ 1]);

            if (j >= p[i].second) {
                dp[j][1][i & 1] = max(dp[j][1][i & 1], dp[j - p[i].second][0][i & 1 ^ 1] + 1);
                if (i == 0 || p[i].first != p[i - 1].first)
                    dp[j][1][i & 1] = max(dp[j][1][i & 1], dp[j - p[i].second][1][i & 1 ^ 1] + 1);
                else
                    dp[j][1][i & 1] = max(dp[j][1][i & 1], dp[j - p[i].second][1][i & 1 ^ 1]);
            }
        }
    }

    int ans = max(dp[s][0][n & 1 ^ 1], dp[s][1][n & 1 ^ 1]);
    if (ans < 0)
        puts("Impossible");
    else
        printf("%d\n", ans);
    return 0;
}
