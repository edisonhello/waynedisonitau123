#include <bits/stdc++.h>
using namespace std;

int main() {
    string S;
    cin >> S;
    int M;
    cin >> M;

    int N = S.size();

    vector<pair<int, int>> V;
    for (int i = 0, j = 0; i < N; i = j) {
        while (j < N && S[i] == S[j]) j++;
        V.emplace_back(S[i], j - i); 
    }
    int K = V.size();
    vector<vector<int>> dp(K, vector<int>(K, -1));

    auto Dfs = [&](auto dfs, int L, int R) -> int {
        if (dp[L][R] != -1) return dp[L][R];
        if (L == R) return V[L].second;
        dp[L][R] = 0;
        if (dfs(dfs, L + 1, R) >= M) dp[L][R] = V[L].second;
        for (int i = L + 1; i <= R; ++i) {
            if (V[i].first == V[L].first) {
                if (dfs(dfs, L + 1, i - 1) < M) continue;
                if (dfs(dfs, i, R) == 0) continue;
                dp[L][R] = max(dp[L][R], V[L].second + dfs(dfs, i, R));
            }
        }
        return dp[L][R];
    };

    if (Dfs(Dfs, 0, K - 1) >= M) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}
