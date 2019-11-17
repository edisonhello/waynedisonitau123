#include <bits/stdc++.h>
using namespace std;

bitset<14> dp[1001][(1 << 13) + 1];
bitset<14> cf[1001][(1 << 13) + 1];
int a[1005], sum[1005];

int lv(int x) {
    if ((x & -x) == x) return __builtin_ctz(x);
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n; cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + a[i];

        if (lv(sum[n]) == -1) { cout << "no" << '\n'; continue; }

        for (int i = 0; i <= n; ++i) for (int j = 0; j <= (1 << 13); ++j) for (int k = 0; k < 14; ++k) dp[i][j][k] = 0;
        
        dp[1][0][lv(a[1])] = 1;
        for (int i = 2; i <= n; ++i) for (int j = 0; j <= (1 << 13); ++j) for (int k = 0; k < 14; ++k) {
            if (dp[i - 1][j][k] == 0) continue;
            auto ls = [&] () { return j; };
            auto rs = [&] () { return sum[i - 1] - j - (1 << k); };
            auto can_go = [&] (int nl, int nlv, int tcf) {
                dp[i][nl][nlv] = 1;
                // cf[i][nl][nlv] = ((i - 1) << 24) | (j << 16) | (k << 8) | tcf;
                cf[i][nl][nlv] = tcf;
            };
            int now = a[i];
            
            if (ls() % now == 0) {
                int nl = ls() + now;
                if (lv(nl) > k) {
                    can_go(0, lv(nl), 0); // biggest changed
                } else if (lv(nl) == k) {
                    can_go(0, k + 1, 0); // left merged
                } else can_go(nl, k, 0); // append to l
            }
            if (rs() % now == 0) {
                int nr = rs() + now;
                if (lv(nr) > k) {
                    can_go(ls() + (1 << k), lv(nr), 1); // biggest changed
                } else if (lv(nr) == k) {
                    can_go(ls(), k + 1, 1); // right merged
                } else can_go(ls(), k, 1); // append to r
            }
        }

        if (dp[n][0][lv(sum[n])]) {
            string ans;
            int i = n, j = 0, k = lv(sum[n]);
            auto ls = [&] () { return j; };
            auto rs = [&] () { return sum[i] - j - (1 << k); };
            while (i > 1) {
                ans += (cf[i][j][k] ? "r" : "l");
                int nj = -1, nk = -1;
                int now = a[i];
                if (!cf[i][j][k]) { // left
                    if (ls() >= now) tie(i, j, k) = make_tuple(i - 1, j - now, k);
                    else if ((1 << k) == now) tie(i, j, k) = make_tuple(i - 1, 0, 31 - __builtin_clz(rs()));
                    else tie(i, j, k) = make_tuple(i - 1, (1 << (k - 1)) - now, k - 1);
                } else {
                    if (rs() >= now) tie(i, j, k) = make_tuple(i - 1, j, k);
                    else if ((1 << k) == now) tie(i, j, k) = make_tuple(i - 1, j - (1 << (31 - __builtin_clz(ls()))), 31 - __builtin_clz(ls()));
                    else tie(i, j, k) = make_tuple(i - 1, j, k - 1);
                }
            }
            ans += "l";
            reverse(ans.begin(), ans.end());
            cout << ans << '\n';
        } else cout << "no" << '\n';
    }
}
