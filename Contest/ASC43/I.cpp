#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e4 + 5;
int a[maxn], f[maxn];
long long dp[maxn];

int main() {
#ifdef ONLINE_JUDGE
    freopen("iq.in", "r", stdin);
    freopen("iq.out", "w", stdout);
#endif
    int n; while (scanf("%d", &n) != EOF) {
        if (n == 0) break;
        for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
        vector<int> v(n + 1);
        for (int i = 0; i <= n; ++i) v[i] = i;
        sort(v.begin(), v.end(), [&](int i, int j) { return a[i] < a[j]; });
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = 1e18;
            for (int j = 0; j < i; ++j) {
                if (dp[j] + a[v[i]] * 1ll * (n - j) < dp[i]) {
                    dp[i] = dp[j] + a[v[i]] * 1ll * (n - j);
                    f[i] = j;
                }
            }
        }
        printf("%lld\n", dp[n]);
        vector<pair<int, int>> ans;
        int x = n;
        while (x) {
            ans.emplace_back(f[x] + 1, x);
            x = f[x];
        }
        reverse(ans.begin(), ans.end());
        printf("%d\n", ans.size());
        for (int i = 0; i < (int)ans.size(); ++i) {
            printf("%d ", ans[i].second - ans[i].first + 1);
            for (int j = ans[i].first; j <= ans[i].second; ++j) printf("%d ", v[j]);
            puts("");
        }
    }
}
