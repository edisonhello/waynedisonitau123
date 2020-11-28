#include <bits/stdc++.h>
using namespace std;

int main() {
    int D;
    cin >> D;
    vector<int> L(D);
    for (int i = 0; i < D; ++i) cin >> L[i];
    int S;
    cin >> S;

    vector<vector<int>> dp(S + 1, vector<int>(2));
    dp[0][0] = 1;

    constexpr int kP = 1'000'000'000 + 7;
    for (int i = 0; i < D; ++i) {
        vector<vector<int>> ndp = dp;
        for (int j = 0; j <= S; ++j) {
            if (j + L[i] <= S) {
                (ndp[j + L[i]][1] += dp[j][0]) %= kP;
                (ndp[j + L[i]][0] += dp[j][1]) %= kP;
            }
        }
        dp = ndp;
    }

    auto fpow = [&](int a, int n) {
        int res = 1;
        while (n > 0) {
            if (n & 1) res = 1LL * res * a % kP;
            a = 1LL * a * a % kP;
            n >>= 1;
        }
        return res;
    };

    int res = 0;
    for (int v = 0; v <= S; ++v) {
        int Value = fpow(S - v, D);
        (res += 1LL * dp[v][0] * Value % kP) %= kP;
        (res += 1LL * dp[v][1] * (kP - Value) % kP) %= kP;
    }
    cout << res << "\n";
    return 0;
}

