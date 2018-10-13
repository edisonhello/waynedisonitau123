#include <bits/stdc++.h>
using namespace std;

long long dp[101][2];

int main() {
    int l, k; cin >> l >> k;
    dp[1][1] = 1;
    if (k <= l) dp[k][1] += 1;
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (dp[i][j] == 0) continue;
            if (j == 0) {
                dp[i + 1][1] += dp[i][j];
                if (i + k <= l) dp[i + k][1] += dp[i][j];
            } else {
                dp[i + 1][0] += dp[i][j];
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= l; ++i) ans += dp[i][1];
    cout << ans << endl;
}
