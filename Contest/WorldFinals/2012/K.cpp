#include <bits/stdc++.h>
using namespace std;

const int kN = 50 + 5;
const int kC = kN * kN;
const int kInf = 1'000'000'000;
vector<int> h[kN], w[kC];
bool has[kN][kC];
int dp[kC][kN];

int main() {
    int n, tc = 0; 
    while (scanf("%d", &n) == 1) {
        printf("Case %d: ", ++tc);
        vector<int> ds;
        for (int i = 0; i < n; ++i) {
            int k; scanf("%d", &k);
            h[i].resize(k);
            for (int j = 0; j < k; ++j) {
                scanf("%d", &h[i][j]);
                ds.push_back(h[i][j]);
            }
            h[i].resize(unique(h[i].begin(), h[i].end()) - h[i].begin());
        }
        sort(ds.begin(), ds.end());
        ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
        int m = ds.size();
        for (int i = 0; i < m; ++i) w[i].clear();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) has[i][j] = false;
            for (int j = 0; j < h[i].size(); ++j) {
                h[i][j] = lower_bound(ds.begin(), ds.end(), h[i][j]) - ds.begin();
                w[h[i][j]].push_back(i);
                has[i][h[i][j]] = true;
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) dp[i][j] = kInf;
        }
        for (int i : w[0]) dp[0][i] = w[0].size();
        for (int i = 0; i + 1 < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i][j] == kInf) continue;
                if (has[j][i + 1]) {
                    if (w[i + 1].size() == 1) {
                        dp[i + 1][j] = min(dp[i][j], dp[i + 1][j]);
                    } else {
                        for (int k : w[i + 1]) {
                            if (k != j) dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + (int)w[i + 1].size() - 1);
                            else dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + (int)w[i + 1].size());
                        }
                    }
                } else {
                    for (int k : w[i + 1]) {
                        dp[i + 1][k] = min(dp[i + 1][k], dp[i][j] + (int)w[i + 1].size());
                    }
                }
            }
        }
        int ans = kInf;
        for (int i = 0; i < n; ++i) ans = min(ans, dp[m - 1][i]);
        printf("%d\n", ans * 2 - n - 1);
    }
    return 0;
}

