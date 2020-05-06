#include <bits/stdc++.h>
using namespace std;

int mp[404][404];
int w[404][404];
int noww[404][404];
long long dp[404][404];
int cf[404][404];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, k, W; cin >> n >> k >> W;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> w[i][j];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> mp[i][j];
            --mp[i][j];
        }
    }

    int ansz = (1 << 29) - 1;
    vector<int> ans;
    for (int z = 1; z < (1 << k); ++z) {
        if (__builtin_popcount(z) >= ansz) continue;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cf[i][j] = -1;
                dp[i][j] = 1e18;
                noww[i][j] = (z & (1 << mp[i][j])) ? w[i][j] : 1000000005;
            }
        }

        dp[1][1] = noww[1][1];
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (i > 1) {
                    if (dp[i - 1][j] + noww[i][j] < dp[i][j]) {
                        dp[i][j] = dp[i - 1][j] + noww[i][j];
                        cf[i][j] = 1;
                    } 
                }
                if (j > 1) {
                    if (dp[i][j - 1] + noww[i][j] < dp[i][j]) {
                        dp[i][j] = dp[i][j - 1] + noww[i][j];
                        cf[i][j] = 2;
                    }
                }
            }
        }

        if (dp[n][n] <= W) {
            if (__builtin_popcount(z) < ansz) {
                ansz = __builtin_popcount(z);
                int i = n, j = n;
                ans.clear();
                ans.push_back(i);
                ans.push_back(j);
                while (i != 1 || j != 1) {
                    if (cf[i][j] == 1) {
                        --i;
                    } else if (cf[i][j] == 2) {
                        --j;
                    } else assert(0);
                    ans.push_back(i);
                    ans.push_back(j);
                }
            }
        }
    }

    if (ans.empty()) {
        cout << -1 << endl;
    } else {
        cout << ansz << endl;
        for (int i = ans.size() - 2; i >= 0; i -= 2) {
            cout << ans[i] << ' ' << ans[i + 1] << ' ';
        }
        cout << endl;
    }

}

