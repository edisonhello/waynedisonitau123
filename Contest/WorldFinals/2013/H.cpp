#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    vector<vector<bool>> goods(n, vector<bool>(n));
    vector<vector<int>> ups(n, vector<int>(n));
    vector<vector<int>> gvs(n, vector<int>(n));
    vector<vector<vector<int>>> pf(n, vector<vector<int>>(n, vector<int>(500)));
    vector<int> cnt(500);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            fill(cnt.begin(), cnt.end(), 0);
            bool good = true;
            int gv = 500;
            for (int k = i; k <= j; ++k) {
                good &= pf[i][j][a[k]]++ == 0;
                cnt[a[k]]++;
                gv = min(gv, a[k]);
            }
            for (int k = 1; k < 500; ++k) pf[i][j][k] += pf[i][j][k - 1];
            gvs[i][j] = gv;
            if (good) {
                int up = gv;
                while (up < 500 && cnt[up]) up++;
                if (gv == 0 && up == j - i + 1) goods[i][j] = true;
            } 
        }
    }
    vector<int> dp(n + 1);
    vector<vector<int>> dp2(n, vector<int>(n, -1));

    function<int(int, int)> Dfs = [&](int l, int r) {
        if (l == r) return 0;
        if (dp2[l][r] >= 0) return dp2[l][r];
        dp2[l][r] = 1'000'000'000;
        for (int m = l; m < r; ++m) {
            int ld = Dfs(l, m);
            int rd = Dfs(m + 1, r);
            assert(gvs[l][m] != gvs[m + 1][r]);
            if (gvs[l][m] < gvs[m + 1][r]) {
                dp2[l][r] = min(dp2[l][r], ld + rd + r - l + 1 - pf[l][m][gvs[m + 1][r]]);
            } else {
                dp2[l][r] = min(dp2[l][r], ld + rd + r - l + 1 - pf[m + 1][r][gvs[l][m]]);
            }
        }
        // printf("dp2[%d][%d] = %d\n", l, r, dp2[l][r]);
        return dp2[l][r];
    };

    for (int i = 1; i <= n; ++i) {
        dp[i] = 1'000'000'000;
        for (int j = 0; j < i; ++j) {
            if (!goods[j][i - 1]) continue;
            dp[i] = min(dp[i], dp[j] + Dfs(j, i - 1));
        }
        // printf("dp[%d] = %d\n", i, dp[i]);
    }
    if (dp[n] == 1'000'000'000) puts("impossible");
    else printf("%d\n", dp[n]);
}
