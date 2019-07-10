#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000009;
const int maxn = 1e6 + 5;
int dp[2][maxn];

int main() {
    int n, k; cin >> n >> k;
    // cout << dfs(0, 0) << endl;
    dp[0][0] = 1;
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= n; ++j)
            (dp[i & 1 ^ 1][j] += dp[i & 1 ^ 1][j - 1]) %= mod;

        dp[i & 1][0] = 0;
        for (int j = 1; j <= n; ++j) {
            dp[i & 1][j] = dp[i & 1 ^ 1][j / 2];
        }
    }
    printf("%d\n", dp[k & 1][n]);
}
