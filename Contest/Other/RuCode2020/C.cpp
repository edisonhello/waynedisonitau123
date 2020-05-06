#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    constexpr int64_t kInf = 1'000'000'000'000'000;
    vector<vector<vector<int64_t>>> dp(n, vector<vector<int64_t>>(3, vector<int64_t>(3, kInf)));
    dp[0][0][0] = 0;
    dp[0][1][1] = a[0];
    dp[0][2][2] = a[0] * 2;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                for (int p = 0; p < 3; ++p) {
                    if (j + k >= 2) {
                        dp[i][j][p] = min(dp[i][j][p], dp[i - 1][k][p] + a[i] * j);
                    }
                }
            }
        }
    }
    for (int i = 2; i < n; ++i) {
        int64_t res = kInf;
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                if (j + k >= 2) {
                    res = min(res, dp[i][j][k]);
                }
            }
        }
        cout << res / 2;
        if (res & 1) cout << ".5";
        cout << " ";
    }
}

