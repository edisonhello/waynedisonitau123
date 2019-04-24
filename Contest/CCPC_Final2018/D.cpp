#include <bits/stdc++.h>
using namespace std;
#define cend ftgyhujiko
#define end dtrfgyuhij

const int mod = 1000000007;

int fpow(int b, int n, int m, int a = 1){
    while (n) {
        if (n & 1) a = a * 1ll * b % m;
        b = b * 1ll * b % m; n >>= 1;
    } return a;
}

int inv(int x, int m) {
    return fpow(x, m - 2, m);
}

vector<int> g[100005];
int v[100005], pr[3][3][maxn], dp[3][maxn];

void dfs(int x, int p) {
    int deg = (int)g[x].size();
    pr[1][2][x] = 0;
    pr[2][2][x] = 0;
    dp[1][x] = dp[2][x] = 0;
    for (int i = 0; i < deg; ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
        (pr[1][2][x] += pr[1][2][u] * 1ll * inv(deg - 1, mod) % mod) %= mod;
        (pr[1][2][x] += pr[1][1][u] * 1ll * inv(deg, mod) % mod) %= mod;
        (dp[1][x] += pr[1][1][u] * 1ll * inv(deg, mod) % mod * dp[2][u] % mod) %= mod;

        if (deg > 2) {
            (pr[2][2][x] += pr[1][2][u] * 1ll * inv(deg - 2, mod) % mod) %= mod;
        } else {
            (dp[2][x] += pr[1][2][u] * 1ll * v[x] % mod) %= mod;
        }
        (pr[2][2][x] += pr[1][1][u] * 1ll * inv(deg - 1, mod) % mod) %= mod;
        (dp[2][x] += pr[1][1][u] * 1ll * inv(
    }
    pr[1][2][x] = pr[1][2][x] * 1ll * inv(deg, mod) % mod;
    pr[1][1][x] = inv(deg, mod);

    for (
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; for (int T = 1; T <= t; ++T) {
        cout << "Case " << T << ": ";
        int n; cin >> n; 
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n; ++i) cin >> v[i];
        for (int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int st; cin >> st; --st;
        dfs(st, -1);
    }
    return 0;
}
