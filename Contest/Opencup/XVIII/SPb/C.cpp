#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> c(n), e(n);
    for (int i = 0; i < n; ++i) cin >> c[i];
    for (int i = 0; i < n; ++i) cin >> e[i];
    vector<int> dp(1 << n);
    dp[0] = 1;
    for (int s = 0; s < (1 << n); ++s) {
        int p = __builtin_popcount(s);
        for (int i = 0; i < n; ++i) {
            if ((s >> i & 1) == 0) {
                if (c[p] <= e[i]) {
                    dp[s ^ (1 << i)] += dp[s];
                }
            }
        }
    }
    cout << dp[(1 << n) - 1] << endl;
}

