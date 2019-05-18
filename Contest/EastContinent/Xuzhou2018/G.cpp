#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 5;
const int mod = 1e9 + 7;
vector<int> g[maxn];
int fa[20][maxn], dep[maxn], sv[maxn], se[maxn];
int fc[maxn], iv[maxn];

void dfs(int x, int p) {
    dep[x] = ~p ? dep[p] + 1 : 0;
    fa[0][x] = p;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        fa[i][x] = fa[i - 1][fa[i - 1][x]];
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
    }
}

int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = 0; i < 20; ++i) {
        if ((dep[y] - dep[x]) >> i & 1)
            y = fa[i][y];
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (fa[i][x] == fa[i][y]) continue;
        x = fa[i][x];
        y = fa[i][y];
    }
    return fa[0][x];
}

int cnk(int n, int k) {
    if (n < k) return 0;
    return fc[n] * 1ll * iv[k] % mod * iv[n - k] % mod;
}

int dfs2(int x, int p, int k) {
    int res = 0;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        res += dfs2(u, x, k);
        if (res >= mod) 
            res -= mod;
        sv[x] += sv[u];
        se[x] += se[u];
    }
    res += cnk(sv[x], k);
    if (res >= mod)
        res -= mod;
    if (p >= 0) {
        res += mod - cnk(se[x], k);
        if (res >= mod)
            res -= mod;
    }
    return res;
}

int fpow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) res = res * 1ll * a % mod;
        a = a * 1ll * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    fc[0] = iv[0] = 1;
    for (int i = 1; i < maxn; ++i) {
        fc[i] = fc[i - 1] * 1ll * i % mod;
        iv[i] = fpow(fc[i], mod - 2);
    }
    int t; scanf("%d", &t);
    while (t--) {
        int n, m, k; scanf("%d%d%d", &n, &m, &k);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 20; ++j)
                fa[j][i] = -1;
        }
        dfs(0, -1);
        for (int i = 0; i < n; ++i) sv[i] = se[i] = 0;
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            --x, --y;
            if (dep[x] > dep[y]) swap(x, y);
            int z = lca(x, y);
            // printf("lca x = %d y = %d => %d\n", x, y, z);
            if (z == x) {
                ++sv[y];
                if (x != 0) --sv[fa[0][x]];
                ++se[y];
                --se[x];
            } else {
                ++sv[x];
                ++sv[y];
                --sv[z];
                if (z != 0) --sv[fa[0][z]];
                ++se[x];
                ++se[y];
                se[z] -= 2;
            }
        }
        // for (int i = 0; i < n; ++i) printf("%d ", in[i]); puts("");
        // for (int i = 0; i < n; ++i) printf("%d ", out[i]); puts("");
        printf("%d\n", dfs2(0, -1, k));
    }
    return 0;
}
