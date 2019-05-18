#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
int x[maxn];
int dp[maxn];

int main() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> x[i];
    int j = 0, pmax = 0;
    for (int i = m + 1; i <= n; ++i) {
        while (j <= n && i - j >= m) pmax = max(pmax, dp[j]), ++j;
        dp[i] = pmax + x[i];
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) ans = max(ans, dp[i]);
    cout << ans << endl;
}
