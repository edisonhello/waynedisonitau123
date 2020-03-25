#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> x(m), y(m);
    for (int i = 0; i < m; ++i) {
        cin >> x[i] >> y[i];
        x[i]--, y[i]--;
    }
    vector<int64_t> dp(1 << n);
    dp[0] = 1;
    for (int s = 0; s < (1 << n) - 1; ++s) {
        if (!dp[s]) continue;
        int v = n - 1 - __builtin_popcount(s);
        // cout << "dp[" << s << "] = " << dp[s] << endl;
        // cout << "v = " << v << endl;
        for (int i = 0; i < n; ++i) {
            if (s >> i & 1) continue;
            int mask = s, nmask = ((1 << n) - 1) ^ s ^ (1 << i);
            int p = i;
            for (int j = 0; j < m; ++j) {
                if (y[j] == p) {
                    if (mask >> x[j] & 1) {
                        mask ^= (1 << x[j]);
                        p = x[j];
                        mask ^= (1 << y[j]);
                    }
                } else if (x[j] == p) {
                    if (nmask >> y[j] & 1) {
                        nmask ^= (1 << y[j]);
                        p = y[j];
                        nmask ^= (1 << x[j]);
                    }
                } else if ((mask >> x[j] & 1) && (nmask >> y[j] & 1)) {
                    mask ^= (1 << x[j]);
                    mask ^= (1 << y[j]);
                    nmask ^= (1 << x[j]);
                    nmask ^= (1 << y[j]);
                }
            }
            if (p == v) {
                dp[s ^ (1 << i)] += dp[s];
            }
        }
    }
    int64_t fc = 1;
    for (int i = 1; i <= n; ++i) fc *= i;
    cout << fc - dp[(1 << n) - 1] << endl;
    return 0;
}

