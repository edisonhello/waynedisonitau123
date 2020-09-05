#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int T = 0;
    while (cin >> s) {
        if (s == "0") break;
        int N = s.size();
        vector<vector<unordered_set<int>>> dp(N, vector<unordered_set<int>>(N + 1));
        for (int i = 0; i < N; ++i) {
            if (s[i] == 'I') dp[i][i + 1].insert(1);
            if (s[i] == 'V') dp[i][i + 1].insert(5);
            if (s[i] == 'X') dp[i][i + 1].insert(10);
            if (s[i] == 'L') dp[i][i + 1].insert(50);
            if (s[i] == 'C') dp[i][i + 1].insert(100);
        }
        for (int p = 2; p <= N; ++p) {
            for (int L = 0; L + p <= N; ++L) {
                int R = L + p;
                for (int M = L + 1; M < R; ++M) {
                    for (int u : dp[L][M]) {
                        for (int v : dp[M][R]) {
                            if (u >= v) dp[L][R].insert(u + v);
                            else dp[L][R].insert(v - u);
                        }
                    }
                }
                // sort(dp[L][R].begin(), dp[L][R].end());
                // dp[L][R].resize(unique(dp[L][R].begin(), dp[L][R].end()) - dp[L][R].begin());
                // cout << "L = " << L << " R = " << R << ": " << dp[L][R].size() << endl;
            }
        }
        cout << "Case " << ++T << ":";
        vector<int> V(dp[0][N].begin(), dp[0][N].end());
        sort(V.begin(), V.end());
        for (int u : V) cout << " " << u;
        cout << "\n";
    }
}

