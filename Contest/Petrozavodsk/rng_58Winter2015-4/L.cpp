#include <bits/stdc++.h>
using namespace std;

int main() {
    string S, T;
    cin >> S >> T;
    int N = S.size(), M = T.size();
    if (N > M) {
        cout << "No\n";
        return 0;
    }

    vector<vector<bool>> dp(N + 1, vector<bool>(M + 1));
    vector<bool> row(N + 1);
    dp[0][0] = true;
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= M; ++j) {
            if (row[i]) dp[i][j] = true;
            if (!dp[i][j]) continue;
            if (i < N && j < M && S[i] == T[j]) {
                dp[i + 1][j + 1] = true;
                if (j + 1 < M && T[j + 1] != S[i]) {
                    row[i + 1] = true;
                }
            }
        }
    }

    cout << (dp[N][M] ? "Yes" : "No") << "\n";
}

