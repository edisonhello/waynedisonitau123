#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
int n, r, c, k;
const int maxn = 1e6 + 5;
int dx[maxn], dy[maxn], dp[maxn];

int fpow(int x, int n) {
    int r = 1;
    while (n) {
        if (n & 1) r = r * 1ll * x % mod;
        x = x * 1ll * x % mod;
        n >>= 1;
    }
    return r;
}

int f(int x) {
    if (dp[x] != -1) return dp[x];
    return dp[x] = (fpow(x, n) + mod - fpow((x + mod - 1) % mod, n)) % mod;
}


int main() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> r >> c >> k;
    for (int h = 1; h <= r; ++h) {
        for (int j = 1; j <= r; ++j) {
            int rem = r + 2 - h - j;
            if (rem < 1) continue;
            dx[h] += f(j) * 1ll * f(rem) % mod;
            dx[h] %= mod;
        }
    }
    for (int w = 1; w <= c; ++w) {
        for (int j = 1; j <= c; ++j) {
            int rem = c + 2 - w - j;
            if (rem < 1) continue;
            dy[w] += f(j) * 1ll * f(rem) % mod;
            dy[w] %= mod;
        }
    }
    // for (int i = 1; i <= r; ++i) cout << dx[i] << ' '; cout << endl;
    // for (int i = 1; i <= c; ++i) cout << dy[i] << ' '; cout << endl;
    int ans = 0;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            if (i * j < k) continue;
            ans += dx[i] * 1ll * dy[j] % mod;
            ans %= mod;
        }
    }
    cout << ans << endl;
    return 0;
    /* int ans = 0;
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j <= c; ++j) {
            for (int a = i; a <= r; ++a) {
                for (int b = j; b <= c; ++b) {
                    int area = (a - i + 1) * (b - j + 1);
                    if (area < k) continue;
                    vector<int> v = { i, j, r - a + 1, c - b + 1 };
                    int x = 1;
                    for (int p = 0; p < 4; ++p) x = x * 1ll * f(v[p]) % mod;
                    (ans += x) %= mod;
                    continue;
                    for (int s = 0; s < 16; ++s) {
                        int k = 1;
                        for (int p = 0; p < 4; ++p) {
                            if (s >> p & 1) k *= v[p] - 1;
                            else k *= v[p];
                        }
                        k = fpow(k, n);
                        if (__builtin_popcount(s) % 2 == 0) ans += k % mod;
                        else ans -= k % mod;
                        ans += mod;
                        ans %= mod;
                    }
                }
            }
        }
    }
    cout << ans << endl; */
} 
