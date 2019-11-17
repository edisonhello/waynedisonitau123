#include <bits/stdc++.h>
using namespace std;

const int kN = 600 + 5;
const long long kInf = 1e15;
int a[kN], b[kN], d[kN], cost[kN];
long long dp[kN][kN];
bool cl[kN][kN];

long long Dfs(int l, int r, int n) {
    if (l > r) return 0;
    if (cl[l][r]) return dp[l][r];
    int dd = -1, ch = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] >= l && b[i] <= r) {
            if (d[i] > dd) {
                dd = d[i];
                ch = i;
            }
        }
    }
    if (ch == -1) {
        cl[l][r] = true;
        dp[l][r] = 0;
        return 0;
    }
    dp[l][r] = kInf;
    for (int i = a[ch]; i <= b[ch]; ++i) dp[l][r] = min(dp[l][r], Dfs(l, i - 1, n) + Dfs(i + 1, r, n) + d[ch]);
    cl[l][r] = true;
    return dp[l][r];
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        vector<int> ds;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d%d", &a[i], &b[i], &d[i]);
            ds.push_back(a[i]);
            ds.push_back(b[i]);
        }
        sort(ds.begin(), ds.end());
        ds.resize(unique(ds.begin(), ds.end()) - ds.begin());
        memset(cost, 0, sizeof(cost));
        for (int i = 0; i < n; ++i) {
            a[i] = lower_bound(ds.begin(), ds.end(), a[i]) - ds.begin();
            b[i] = lower_bound(ds.begin(), ds.end(), b[i]) - ds.begin();
        }
        for (int i = 0; i <= ds.size(); ++i) {
            for (int j = 0; j <= ds.size(); ++j)
                cl[i][j] = false;
        }
        printf("%lld\n", Dfs(0, ds.size() - 1, n));
    }
}
