#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("foreign.in", "r", stdin);
    freopen("foreign.out", "w", stdout);
    string S;
    cin >> S;
    int N = S.size();
    vector<double> dp(N + 1);
    double sum = 0;
    int64_t Ws = 0, Cs = 0;
    dp[N] = 0;
    for (int i = N - 1; i >= 0; --i) {
        dp[i] = sum;
        if (S[i] == 'W') {
            dp[i] += Cs;
        } else {
            dp[i] += Ws;
        }
        if (S[i] == 'W') {
            Ws += N - i;
        } else {
            Cs += N - i;
        }
        dp[i] /= (N - i);
        sum += dp[i];
    }
    cout << fixed << setprecision(20) << dp[0] << "\n";
}

