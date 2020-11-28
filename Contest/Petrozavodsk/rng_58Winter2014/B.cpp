#include <bits/stdc++.h>
using namespace std;

constexpr int kN = 50 + 5;
int dp[kN][kN][30][26];

int main() {
    int N;
    cin >> N;
    vector<string> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];

    constexpr int kP = 1'000'000'000 + 7;
    for (int i = 0; i < kN; ++i) {
        for (int j = 0; j < kN; ++j) {
            for (int k = 0; k < 30; ++k) {
                for (int l = 0; l < 26; ++l) {
                    dp[i][j][k][l] = -1;
                }
            }
        }
    }
    // memset(dp, -1, sizeof(dp));

    auto Dfs = [&](auto dfs, int L, int R, int X, int C) -> int {
        if (L == R) return 1;
        if (C == 26) return 0;
        if (dp[L][R][X][C] != -1) return dp[L][R][X][C];
        int Y = -1;
        for (int i = R - 1; i >= L; --i) {
            if (S[i].size() <= X) {
                Y = i;
                break;
            }
        }
        if (Y != -1) {
            if (Y == L) return dp[L][R][X][C] = dfs(dfs, L + 1, R, X, C);
            return 0;
        }
        dp[L][R][X][C] = 0;
        if (C + 1 < 26) dp[L][R][X][C] = dfs(dfs, L, R, X, C + 1);
        bool Ok = true;
        for (int i = L; i < R; ++i) {
            if (S[i].size() <= X) break;
            Ok &= S[i][X] - 'a' == C || S[i][X] == '?';
            if (!Ok) break;
            dp[L][R][X][C] += 1LL * dfs(dfs, L, i + 1, X + 1, 0) * dfs(dfs, i + 1, R, X, C + 1) % kP;
            dp[L][R][X][C] %= kP;
        }
        return dp[L][R][X][C];
    };

    cout << Dfs(Dfs, 0, N, 0, 0) << "\n";
}

