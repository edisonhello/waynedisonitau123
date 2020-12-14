#include <bits/stdc++.h>
using namespace std;

int dp[2005];

int cost[] = {1, 6, 28, 88, 198, 328, 648};
int g[] = {8, 18, 28, 58, 128, 198, 388};

int main() {
    for (int z = 0; z < (1 << 7); ++z) {
        int sum = 0;
        int bo = 0;
        for (int i = 0; i < 7; ++i) if (z & (1 << i)) {
            sum += cost[i];
            bo += g[i];
        }

        dp[sum] = max(dp[sum], sum * 10 + bo);
    }

    for (int i = 0; i < 7; ++i) {
        for (int j = cost[i]; j <= 2000; ++j) {
            dp[j] = max(dp[j], dp[j - cost[i]] + cost[i] * 10);
        }
    }

    int n; cin >> n;
    cout << dp[n] << endl;
}

