#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 5;
const int mod = 998244353;
const int inv2 = 499122177;
long long d[maxn][maxn], w[maxn][maxn];

int main() {
    int n; scanf("%d", &n);
    int all = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%lld", &d[i][j]);
            w[i][j] = d[i][j];
            all += w[i][j] % mod;
            if (all >= mod) all -= mod;
        }
    }
    all = all * 1ll * inv2 % mod;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    /* for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%lld ", d[i][j]);
        }
        puts("");
    } */
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            vector<long long> v;
            for (int k = 0; k < n; ++k) {
                if (i == k || k == j) continue;
                v.push_back(min(d[i][k], d[j][k]));
            }
            sort(v.begin(), v.end());
            reverse(v.begin(), v.end());
            int cur = 0;
            for (int k = 0; k < (int)v.size(); ++k) {
                int add = v[k] % mod * (2 * k) % mod;
                ans += add;
                cur += add;
                if (ans >= mod) ans -= mod;
                if (cur >= mod) cur -= mod;
            }
            int add = w[i][j] % mod * (n * (n - 1) / 2 - 2) % mod;
            ans += add;
            cur += add;
            if (ans >= mod) ans -= mod;
            if (cur >= mod) cur -= mod;
            ans += all;
            cur += all;
            if (ans >= mod) ans -= mod;
            // if (cur 
        }   
    }
    ans = ans * 1ll * inv2 % mod;
    printf("%d\n", ans);
    return 0;
}
