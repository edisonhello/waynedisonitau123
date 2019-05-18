#include <bits/stdc++.h>
using namespace std;

const int maxn = 2000 + 5;
int dp[maxn][maxn], a[maxn];
int fwL[maxn][maxn], fwR[maxn][maxn];

void add(int x, int v, int *fw) {
    for (int i = x + 1; i < maxn; i += i & -i)
        fw[i] = max(fw[i], v);
}

int query(int x, int *fw) {
    int res = -1e9;
    for (int i = x + 1; i > 0; i -= i & -i)
        res = max(res, fw[i]);
    return res;
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        vector<int> ds;
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]), ds.push_back(a[i]);
        sort(ds.begin(), ds.end());
        ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
        for (int i = 0; i < n; ++i) a[i] = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                dp[i][j] = -1e9;
        }
        /* for (int i = 0; i < n; ++i) {
            dp[i][i] = max(dp[i][i], 1);
            if (i > 0) {
                for (int j = 0; j < i; ++j) {
                    if (a[i] < a[i - 1])
                        dp[i][j] = max(dp[i][j], dp[i - 1][j] + 1);
                    if (a[i] < a[j])
                        dp[i][i - 1] = max(dp[i][i - 1], dp[j][i - 1] + 1);
                    if (a[i] > a[i - 1]) 
                        dp[j][i] = max(dp[j][i], dp[j][i - 1] + 1);
                    if (a[i] > a[j])
                        dp[i - 1][i] = max(dp[i - 1][i], dp[i - 1][j] + 1);
                }
            }
        } */
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < maxn; ++j) {
                fwL[i][j] = -1e9;
                fwR[i][j] = -1e9;
            }
        }
        for (int i = 0; i < n; ++i) {
            dp[i][i] = max(dp[i][i], 1);
            for (int j = 0; j < i; ++j) {
                dp[i][j] = max(dp[i][j], query(n - a[i] - 2, fwR[j]) + 1);
                dp[j][i] = max(dp[j][i], query(a[i] - 1,  fwL[j]) + 1);
            }
            for (int j = 0; j <= i; ++j) {
                add(n - 1 - a[j], dp[j][i], fwR[i]);
                add(a[j], dp[i][j], fwL[i]);
                add(a[i], dp[j][i], fwL[j]);
                add(n - 1 - a[i], dp[i][j], fwR[j]);
                // printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
                // printf("dp[%d][%d] = %d\n", j, i, dp[j][i]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                ans = max(ans, dp[i][j]);
        }
        printf("%d\n", ans);
    }
}
