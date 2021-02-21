#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    constexpr int kP = 998244353;
    vector<int> dp(N + 1);
    dp[0] = 1;
    for (int i = 1; i <= N; ++i) {
        dp[i] = dp[i - 1];
        for (int bit = 0; bit < 20; ++bit) {
            if (i >> bit & 1) {
                int L = (1 << bit);
                int R = (1 << (bit + 1)) - 1;
                if (R < i) {
                    (dp[i] += kP - dp[R]) %= kP;
                    if (L > 0) (dp[i] += dp[L - 1]) %= kP;
                }
            }
        }
        (dp[i] += dp[i - 1]) %= kP;
    }
    cout << (dp[N] + kP - 1) % kP << "\n";
}

