#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000;
const int mod = 1e9 + 7;
vector<int> g[maxn];
int dp[maxn], cnk[maxn][maxn], ans[maxn], inv[maxn];

int fpow(int a, int n) {
    int r = 1;
    for (; n; n >>= 1) {
        if (n & 1) r = r * 1ll * a % mod;
        a = a * 1ll * a % mod;
    }
    return r;
}

void dfs(int x, int k) {
    dp[x] = k;
    for (const int &u : g[x]) {
        dfs(u, k);
        int f = dp[u] * 1ll * (k - 1) % mod * 1ll * inv[k] % mod;
        dp[x] = dp[x] * 1ll * f % mod;
    }
}

int solve(int k) {
    dfs(0, k);
    return dp[0];
}

int main() {
    int n, k; scanf("%d%d", &n, &k);
    for (int i = 1; i<=k;++i)inv[i]=fpow(i, mod-2);
    for (int i = 1; i < n; ++i) {
        int p; scanf("%d", &p);
        g[p].push_back(i);
    }
    for (int i = k; i >= 1; --i) ans[i] = solve(i);
    int res = ans[k];
    cnk[0][0] = 1;
    for (int i = 1; i < maxn; ++i) {
        for (int j = 0; j < maxn; ++j) {
            cnk[i][j] = cnk[i - 1][j];
            if (j) cnk[i][j] += cnk[i - 1][j - 1];
            if(cnk[i][j] >= mod) cnk[i][j] -= mod;
        }
    }
    int c = -1;
    for (int i = k - 1; i >= 1; --i) {
        int w = ans[i] * 1ll * cnk[k][k - i] % mod;
        if (c == -1) w = mod - w;
        (res += w) %= mod;
        c = -c;
    }
    printf("%d\n", res);
}
