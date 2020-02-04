#include <bits/stdc++.h>
using namespace std;

int cost[1 << 20][2];
long long sum[1 << 20][2];
long long dp[1 << 20][2], dp2[1 << 20][2];
const long long kInf = 1'000'000'000'000'000'000;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    for (int i = 0; i < (1 << n); ++i) cin >> cost[i][0];
    for (int i = 0; i < (1 << n); ++i) cin >> cost[i][1];
    for (int b = 0; b < 2; ++b) {
        for (int i = 0; i < (1 << n); ++i) sum[i][b] = cost[i][b];
        for (int i = 0; i < n; ++i) {
            for (int s = (1 << n) - 1; s >= 0; --s) {
                if (s >> i & 1) sum[s][b] += sum[s ^ (1 << i)][b];
            }
        }
    }
    dp[0][0] = dp2[0][0] = sum[0][0] - sum[0][1];
    dp[0][1] = dp2[0][1] = sum[0][1] - sum[0][0];
    for (int s = 1; s < (1 << n); ++s) {
        dp[s][0] = sum[s][0] - sum[s][1];
        dp[s][1] = sum[s][1] - sum[s][0];
        for (int i = 0; i < n; ++i) {
            if (s >> i & 1) {
                dp[s][0] = min(dp[s][0], dp2[s ^ (1 << i)][1] + sum[s][0] - sum[s][1]);
                dp[s][1] = min(dp[s][1], dp2[s ^ (1 << i)][0] + sum[s][1] - sum[s][0]);
            }
        }
        dp2[s][0] = dp[s][0];
        dp2[s][1] = dp[s][1];
        for (int i = 0; i < n; ++i) {
            if (s >> i & 1) {
                dp2[s][0] = min(dp2[s][0], dp2[s ^ (1 << i)][0]);
                dp2[s][1] = min(dp2[s][1], dp2[s ^ (1 << i)][1]);
            }
        }
    }
    const int mask = (1 << n) - 1;
    printf("%lld\n", min(dp[mask][0] + sum[mask][1], dp[mask][1] + sum[mask][0]));
}

