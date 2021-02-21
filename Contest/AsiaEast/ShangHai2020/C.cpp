#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int dp[32][4];
void solve() {
    int n, m; cin >> n >> m;

    long long ans = 0;
    if (n >= 1) ++ans;
    if (m >= 1) ++ans;

    for (int z = 1; z <= 30; ++z) {
        for (int i = 0; i <= z + 1; ++i) dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = 0;
        // int y = 0;
        // if (n >= (1 << (z + 1))); else y |= 1; // n touch top
        // if (m >= (1 << (z + 1))); else y |= 2; // m touch top
        // dp[z][y] = 1;
        if (n >= (1 << z)) {
            int y = 0;
            if (m < (1 << z)) y = 2;
            if (n >= (1 << (z + 1))) dp[z][0 | y]++;
            else dp[z][1 | y]++; // n touch top
        } 
        if (m >= (1 << z)) {
            int y = 0;
            if (n < (1 << z)) y = 1;
            if (m >= (1 << (z + 1))) dp[z][0 | y]++;
            else dp[z][2 | y]++; // m touch top
        }

        for (int zz = z - 1; zz >= 0; --zz) {
            for (int y = 0; y < 4; ++y) {
                if ((n & (1 << zz)) || !(y & 1)) {
                    int yy = y;
                    // if ((y & 1) && (n & (1 << zz))) yy ^= 1;
                    if ((y & 2) && (m & (1 << zz))) yy ^= 2;
                    dp[zz][yy] += dp[zz + 1][y];
                    if (dp[zz][yy] >= mod) dp[zz][yy] -= mod;
                }
                if ((m & (1 << zz)) || !(y & 2)) {
                    int yy = y;
                    if ((y & 1) && (n & (1 << zz))) yy ^= 1;
                    // if ((y & 2) && (m & (1 << zz))) yy ^= 2;
                    dp[zz][yy] += dp[zz + 1][y];
                    if (dp[zz][yy] >= mod) dp[zz][yy] -= mod;
                }
                {
                    int yy = y;
                    if ((y & 1) && (n & (1 << zz))) yy ^= 1;
                    if ((y & 2) && (m & (1 << zz))) yy ^= 2;
                    dp[zz][yy] += dp[zz + 1][y];
                    if (dp[zz][yy] >= mod) dp[zz][yy] -= mod;
                }
            }
        }

        ans += (0ll + dp[0][0] + dp[0][1] + dp[0][2] + dp[0][3]) * 1ll * (z + 1);
    }

    cout << ans % 1000000007 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) solve();
}

