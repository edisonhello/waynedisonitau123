#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

using matrix = vector<vector<int>>;

matrix mult(const matrix &a, const matrix &b) {
    matrix c(a.size(), vector<int>(a.size(), 0));
    for (int i = 0; i < (int)a.size(); ++i) {
        for (int j = 0; j < (int)a.size(); ++j) {
            for (int k = 0; k < (int)a.size(); ++k) {
                c[i][j] += a[i][k] * 1ll * b[k][j] % mod;
                if (c[i][j] >= mod) c[i][j] -= mod;
            }
        }
    }
    return c;
}

matrix fpow(matrix a, int n) {
    matrix c(a.size(), vector<int>(a.size(), 0));
    for (int i = 0; i < (int)a.size(); ++i) c[i][i] = 1;

    while (n > 0) {
        if (n & 1) 
            c = mult(c, a);
        a = mult(a, a);
        n >>= 1;
    }
    return c;
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    
    vector<int> shift(1 << (2 * k + 1));

    for (int s = 0; s < 1 << (2 * k + 1); ++s) {
        shift[s] = 0;
        for (int i = 1; i < 2 * k + 1; ++i) {
            if (s >> i & 1)
                shift[s] ^= (1 << (i - 1));
        }
    }

    vector<int> states;

    for (int s = 0; s < (1 << (2 * k + 1)); ++s) {
        if (__builtin_popcount(s) == k)
            states.push_back(s);
    }

    vector<int> where(1 << (2 * k + 1), -1);
    int m = (int)states.size();
    for (int i = 0; i < m; ++i)
        where[states[i]] = i;
    if (k <= 4) {
        vector<vector<int>> coef(m, vector<int>(m));
        for (int i = 0; i < m; ++i) {
            int s = states[i];
            for (int p = 0; p < (2 * k + 1); ++p) {
                if (s >> p & 1 ^ 1) continue;
                if (s & 1) continue;
                int t = shift[s ^ (1 << p)] ^ (1 << (2 * k));
                int j = where[t];
                (coef[j][i] += 1) %= mod;
            }

            if (s % 2 == 0) {
                int t = shift[s];
                int j = where[t];
                (coef[j][i] += 1) %= mod;
            }
        }

        coef = fpow(coef, n);
        int init = 0;
        for (int i = k + 1; i < 2 * k + 1; ++i) init ^= (1 << i);
        init = where[init];
        int ans = coef[init][init];

        printf("%d\n", ans);
        return 0;
    }
    

    vector<vector<int>> dp(2, vector<int>(states.size())); 

    int init = 0;
    for (int i = k + 1; i < 2 * k + 1; ++i) init ^= (1 << i);

    init = where[init];
    dp[0][init] = 1;

    for (int i = 0; i < n; ++i) {
        fill(dp[i & 1 ^ 1].begin(), dp[i & 1 ^ 1].end(), 0);
        for (int j = 0; j < (int)states.size(); ++j) {
            int s = states[j];
            if (dp[i & 1][j] == 0) continue;
            for (int p = 0; p < 2 * k + 1; ++p) {
                if (s >> p & 1 ^ 1) continue;
                if (s & 1) continue;
                if (p != 0 && (s & 1)) continue;

                int t = shift[s ^ (1 << p)];
                t ^= (1 << (2 * k));
                dp[i & 1 ^ 1][where[t]] += dp[i & 1][j];
                if (dp[i & 1 ^ 1][where[t]] >= mod) dp[i & 1 ^ 1][where[t]] -= mod;
            }

            if (s % 2 == 0) {
                int t = shift[s];
                dp[i & 1 ^ 1][where[t]] += dp[i & 1][j];
                if (dp[i & 1 ^ 1][where[t]] >= mod) dp[i & 1 ^ 1][where[t]] -= mod;
            }
        }
    }

    printf("%d\n", dp[n & 1][init]);
    return 0;
}
