#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 5;
const long long inf = 1e18;
int a[maxn];
long long pf[maxn], sf[maxn];
long long dp[maxn];
long long cost[maxn][maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("ebola.in", "r", stdin);
    freopen("ebola.out", "w", stdout);
#endif
    int n; 
    while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        for (int i = 1; i <= n; ++i) pf[i] = pf[i - 1] + a[i];
        for (int i = n; i >= 1; --i) sf[i] = sf[i + 1] + a[i];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                long long take = pf[i] - pf[j] - 3ll * (i - j) * a[j];
                cost[i][j] = max(take, 0ll);
            }
        }
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cost[i][j] += cost[i][j - 1];
            }
        }
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += (2 * i - 2) * 1ll * a[i];
        }
        for (int i = 0; i <= n; ++i) {
            dp[i] = -inf; 
        }
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1];
            for (int j = 1; j < i; ++j) {
                dp[i] = max(dp[i], dp[j - 1] + cost[i][i] - cost[i][j - 1] - 2 * (i - j) * sf[i + 1]);
            }
        }
        printf("%lld\n", ans - dp[n]);
    }
}
