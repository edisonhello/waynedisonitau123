#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> A(N, vector<int>(M));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> A[i][j];
            }
        }

        auto Check = [&](int V) {
            vector<vector<int>> dp(N, vector<int>(M, -1'000'000'000));
            if (V + A[0][0] <= 0) return false;
            if (A[0][0] == -1001) return false;
            dp[0][0] = V + A[0][0];
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < M; ++j) {
                    if (i == 0 && j == 0) continue;
                    if (A[i][j] == -1001) continue;
                    if (i > 0 && dp[i - 1][j] >= 0) {
                        dp[i][j] = max(dp[i][j], dp[i - 1][j] + A[i][j]);
                    }
                    if (j > 0 && dp[i][j - 1] >= 0) {
                        dp[i][j] = max(dp[i][j], dp[i][j - 1] + A[i][j]);
                    }
                }
            }
            return dp[N - 1][M - 1] > 0;
        };

        int res = 1'000'000'001;
        for (int bit = 30; bit >= 0; --bit) {
            if (res - (1 << bit) >= 0 && Check(res - (1 << bit))) res -= (1 << bit);
        }
        if (res == 1'000'000'001) res = -1;
        cout << res << "\n";
    }
}
