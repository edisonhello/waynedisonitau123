#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (int i = 0; i < N; ++i) cin >> A[i];
        vector<vector<int>> dp(K + 1, vector<int>(N + 1));
        int cnt = 0;
        for (int i = 0; i < N; ++i) cnt += A[i];
        dp[0][cnt] = 1;
        constexpr int kMod = 1000000000 + 7;
        for (int i = 0; i < K; ++i) {
            for (int j = 0; j <= N; ++j) {
                if (j > 0) {
                    dp[i + 1][j - 1] += 1LL * dp[i][j] * j % kMod;
                    dp[i + 1][j - 1] %= kMod;
                }
                if (j + 1 <= N) {
                    dp[i + 1][j + 1] += 1LL * dp[i][j] * (N - j) % kMod;
                    dp[i + 1][j + 1] %= kMod; 
                }
            }
        }
        cout << "Case #" << t << ": " << dp[K][0] << "\n";
    }
}
