#include <bits/stdc++.h>
using namespace std;

int main() {
    int q;
    cin >> q;
    while (q--) {
        int n, m, p;
        cin >> n >> m >> p;
        vector<vector<int>> dp(n + 1, vector<int>(n + 1));
        dp[1][n - 1] = 1;
        for (int E = 1; E <= m; ++E) {
            vector<vector<int>> nxt(n + 1, vector<int>(n + 1));
            for (int C = 0; C <= n; ++C) {
                for (int V = 0; V <= n; ++V) {
                    if (!dp[C][V]) continue;
                    if (V > 0) {
                        (nxt[C + 1][V - 1] += dp[C][V]) %= p;
                    } else {
                        if (C > 0 && (n - C + 1) * (n - 1) + (C - 2) * (C - 1) / 2 > E - 1) {
                            (nxt[C][V] += dp[C][V]) %= p;
                        }
                    }
                    for (int k = 1; k < C; ++k) {
                        (nxt[C - k][V] += dp[C][V]) %= p;
                    }
                }
            }
            dp = nxt;
            int sum = 0;
            for (int C = 0; C <= n; ++C) {
                for (int V = 0; V <= n; ++V) {
                    (sum += dp[C][V]) %= p;
                }
            }
            cout << sum << " ";
        }
        cout << endl;
    }
}

