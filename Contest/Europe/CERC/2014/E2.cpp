#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

int dp[1001][(1 << 13) + 1][14];
bitset<14> cf[1001][(1 << 13) + 1];
int a[1005], sum[1005];

int lv(int x) {
    if (x == 0) return -1;
    if ((x & -x) == x) return __builtin_ctz(x);
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; 
    for (int tc = 1; tc <= t; ++tc) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];

        if (lv(sum[n]) == -1) { cout << "no" << '\n'; continue; }

        // for (int i = 0; i <= n; ++i) for (int j = 0; j <= (1 << 12); ++j) for (int k = 0; k < 14; ++k) dp[i][j][k] = 0;
        
        dp[1][0][lv(a[1])] = tc;
        for (int i = 2; i <= n; ++i) for (int j = 0; j <= min(1 << 12, sum[i - 1]); ++j) for (int k = 0; k < 14; ++k) {
            if (dp[i - 1][j][k] != tc) continue;
		    int rs = sum[i - 1] - j - (1 << k);	
            if (rs < 0) break;
            auto can_go = [&] (int nl, int nlv, int tcf) {
                dp[i][nl][nlv] = tc;
                cf[i][nl][nlv] = tcf;
            };
            int now = a[i];
            
            if (j == 0 || j % now == 0) {
                int nl = j + now;
                if (lv(nl) > k) {
                    can_go(0, lv(nl), 0); // biggest changed
                } else if (lv(nl) == k) {
                    can_go(0, k + 1, 0); // left merged
                } else can_go(nl, k, 0); // append to l
            }
            if (rs == 0 || rs % now == 0) {
                int nr = rs + now;
                if (lv(nr) > k) {
                    can_go(j + (1 << k), lv(nr), 1); // biggest changed
                } else if (lv(nr) == k) {
                    can_go(j, k + 1, 1); // right merged
                } else can_go(j, k, 1); // append to r
            }
        }

        if (dp[n][0][lv(sum[n])] == tc) {
            string ans;
            int i = n, j = 0, k = lv(sum[n]);
            while (i > 1) {
                int rs = sum[i] - j - (1 << k);
                ans += (cf[i][j][k] ? "r" : "l");
                int now = a[i];
                if (!cf[i][j][k]) { // left
                    if (j >= now) --i, j -= now;
                    else if ((1 << k) == now) --i, j = 0, k = 31 - __builtin_clz(rs);
                    else --i, j = (1 << (k - 1)) - now, --k;
                } else {
                    if (rs >= now) --i;
                    else if ((1 << k) == now) --i, k = 31 - __builtin_clz(j), j -= (1 << (31 - __builtin_clz(j)));
                    else --i, --k;
                }
            }
            ans += "l";
            reverse(ans.begin(), ans.end());
            cout << ans << '\n';
        } else cout << "no" << '\n';
    }
}
