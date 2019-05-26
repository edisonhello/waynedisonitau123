#include <bits/stdc++.h>
using namespace std;

int dp[105][1 << 16][2];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        int d; cin >> d;
        int co[16]; for (int j = 0; j < m; ++j) cin >> co[j];
        for (int j = 0; j < (1 << m); ++j) dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1]);
        for (int j = 0; j < (1 << m); ++j) {
            for (int k = 0; k < m; ++k) {
                dp[i][j | (1 << k)][1] = min(dp[i][j | (1 << k)][1], dp[i][j][0] + d + co[k]);
            }
        }
        for (int j = 0; j < (1 << m); ++j) {
            for (int k = 0; k < m; ++k) {
                dp[i][j | (1 << k)][1] = min(dp[i][j | (1 << k)][1], dp[i][j][1] + co[k]);
            }
        }
    }
    cout << min(dp[n][(1 << m) - 1][0], dp[n][(1 << m) - 1][1]) << endl;
}
