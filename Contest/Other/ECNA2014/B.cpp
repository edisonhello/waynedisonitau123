#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    int T = 0;
    while (cin >> s) {
        if (s == "0") break;
        int N = s.size();
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, N));
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j <= N; ++j) {
                dp[i][j] = j - i;
            }
        }
        vector<vector<vector<pair<int, int>>>> trans(N + 1, vector<vector<pair<int, int>>>(N + 1));
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j <= N; ++j) {
                bool ok = true;
                for (int k = j; k + j - i <= N; k += j - i) {
                    for (int p = 0; p < j - i; ++p) {
                        ok &= s[k + p] == s[i + p];
                    } 
                    if (!ok) break;
                    trans[i][k + j - i].emplace_back(i, j);
                }
            }
        }
        for (int p = 1; p <= N; ++p) {
            for (int i = 0; i + p <= N; ++i) {
                int j = i + p;
                for (int k = 0; k < trans[i][j].size(); ++k) {
                    int l = trans[i][j][k].first;
                    int r = trans[i][j][k].second;
                    assert((j - i) % (r - l) == 0);
                    int cnt = (j - i) / (r - l);
                    int cost = dp[l][r];
                    if (cnt > 1) {
                        if (r - l > 1) cost += 2;
                        cost += to_string(cnt).size();
                    }
                    dp[i][j] = min(dp[i][j], cost);
                }
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
        }
        cout << "Case " << ++T << ": " << dp[0][N] << "\n";
    }
}

