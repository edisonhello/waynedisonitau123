#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
const int mod = 1e9 + 7;
vector<int> g[maxn];
int dp[maxn][maxn][2], sz[maxn];
int nxt[maxn][2];

void dfs(int x, int p) {
    dp[x][0][1] = 1;
    sz[x] = 1;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;

        dfs(u, x);
        
        for (int j = 0; j <= sz[x] + sz[u]; ++j) {
            nxt[j][0] = 0;
            nxt[j][1] = 0;
        }

        for (int j = 0; j <= sz[x]; ++j) {
            for (int k = 0; k <= sz[u]; ++k) {
                nxt[j + k][1] += dp[x][j][1] * 1ll * (dp[u][k][0] + dp[u][k][1]) % mod;
                nxt[j + k][1] %= mod;
                if (k < sz[u]) {
                    nxt[j + k + 1][0] += dp[x][j][1] * 1ll * dp[u][k][1] % mod;
                    nxt[j + k + 1][0] %= mod;
                    nxt[j + k + 1][0] += dp[x][j][0] * 1ll * dp[u][k][1] % mod;
                    nxt[j + k + 1][0] %= mod;
                }
                nxt[j + k][0] += dp[x][j][1] * 1ll * dp[u][k][0] % mod;
                nxt[j + k][0] %= mod;
                nxt[j + k][0] += dp[x][j][0] * 1ll * dp[u][k][0] % mod;
                nxt[j + k][0] %= mod;
                nxt[j + k][0] += dp[x][j][0] * 1ll * dp[u][k][0] % mod;
                nxt[j + k][0] %= mod;
                nxt[j + k][0] += dp[x][j][0] * 1ll * dp[u][k][1] % mod;
                nxt[j + k][0] %= mod;
            }
        }

        for (int j = 0; j <= sz[x] + sz[u]; ++j) {
            dp[x][j][0] = nxt[j][0];
            dp[x][j][1] = nxt[j][1];
        }

        sz[x] += sz[u];
    }


}

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, -1);

    int ans = dp[0][m][0];
    if (m > 0) {
        ans += dp[0][m - 1][1];
        ans %= mod;
    }
    printf("%d\n", ans);
    return 0;
}
