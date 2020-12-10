#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;

int pw(int b, int n) {
    int a = 1;
    while (n) {
        if (n & 1) a = 1ll * a * b % mod;
        b = 1ll * b * b % mod; n >>= 1;
    }
    return a;
}

int main() {
    int t, T = 0; cin >> t; while (t--) {
        cout << "Case #" << (++T) << ": ";

        int n, m, k; cin >> n >> m >> k;
        vector<int> a(n + m); 
        for (int i = 0; i < n + m; ++i) cin >> a[i];
        vector<vector<int>> pos(n + m + 2);
        while (k--) {
            int x, y, v; cin >> x >> y >> v;
            --x, --y;
            // cerr << "pos " << x + y + 1 << " val " << v << endl;
            pos[x + y + 1].push_back(v);
        }

        bool nosol = 0;
        vector<int> t(n + m, 0);
        for (int i = 1; i < n + m; ++i) t[i] = min(min(min(i, n), m), n + m - i);

        for (int i = 1; i < n + m; ++i) {
            if (pos[i].size() && *max_element(pos[i].begin(), pos[i].end()) > min(a[i], a[i - 1])) {
                cerr << "i dead " << i << endl;
                nosol = 1;
            }

            t[i] -= pos[i].size();
        }

        if (pos[1].size() && pos[1][0] != a[0]) {
            cout << 0 << '\n';
            continue;
        }

        if (pos[n + m - 1].size() && pos[n + m - 1][0] != a[n + m - 1]) {
            cout << 0 << '\n';
            continue;
        }

        auto f = [&] (int at, int val) {
            int mx = pos[at].size() ? *max_element(pos[at].begin(), pos[at].end()) : -10;
            if (mx == val) {
                return pw(val, t[at]);
            } else if (mx > val) {
                return 0;
            } else {
                int r = (pw(val, t[at]) - pw(val - 1, t[at]) + mod) % mod;
                return r;
            }
        };

        if (nosol) {
            cout << 0 << '\n';
            continue;
        }

        vector<vector<int>> dp(n + m + 1, vector<int>(2, 0));

        if (a[0] > a[1]) {
            cout << 0 << '\n';
            continue;
        }

        if (a[0] == a[1]) {
            dp[1][1] = 1;
        } else {
            dp[1][0] = 1;
        }

        for (int i = 2; i < n + m - 1; ++i) {
            // cerr << "i = " << i << endl;

            if (a[i - 1] < a[i]) dp[i][0] += 1ll * dp[i - 1][0] * f(i, a[i - 1]) % mod;
            // cerr << "dp[i][0] = " << dp[i][0] << endl;
            dp[i][0] += 1ll * dp[i - 1][1] * pw(min(a[i - 1], a[i] - 1), t[i]) % mod;
            // cerr << "dp[i][0] = " << dp[i][0] << endl;
            if (dp[i][0] >= mod) dp[i][0] -= mod;
            if (pos[i].size() && *max_element(pos[i].begin(), pos[i].end()) == a[i]) dp[i][0] = 0;

            if (a[i - 1] == a[i]) dp[i][1] += 1ll * dp[i - 1][0] * f(i, a[i]) % mod;
            // cerr << "dp[i][1] = " << dp[i - 1][0] << endl;
            if (a[i - 1] >= a[i]) dp[i][1] += 1ll * dp[i - 1][1] * f(i, a[i]) % mod;
            // cerr << "dp[i][1] = " << dp[i][1] << endl;
            if (dp[i][1] >= mod) dp[i][1] -= mod;

            // cerr << "dp " << i << " = " << dp[i][0] << ' ' << dp[i][1] << endl;
            // cerr << "t[i] = " << t[i] << endl;
        }

        int ans = 0;
        if (a[n + m - 2] >= a[n + m - 1]) ans += dp[n + m - 2][1];
        if (a[n + m - 2] == a[n + m - 1]) ans += dp[n + m - 2][0];
        if (ans >= mod) ans -= mod;

        cout << ans << '\n';
    }
}

