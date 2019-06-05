#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 36;
long long adj[maxn];
int a[maxn], p;

int dfs(long long s) {
    if (s == 0) return 1;
    int x = __builtin_ctzll(s & -s);
    long long ed = adj[x] & s;
    if (ed == 0) 
        return (a[x] + 1) * 1ll * dfs(s ^ (1ll << x)) % p;

    int in = dfs(s ^ (1ll << x));
    int out = dfs(s ^ (1ll << x) ^ ed);
    int pd = 1;
    while (ed > 0) {
        int y = __builtin_ctzll(ed & -ed);
        if (s >> y & 1ll) pd = pd * 1ll * a[y] % p;
        ed ^= (1ll << y);
    }
    return (a[x] * 1ll * in % p + pd * 1ll * out % p) % p;
}

int main() {
    int t; scanf("%d", &t);
    for (int tc = 1; tc <= t; ++tc) {
        int n, m; scanf("%d%d%d", &n, &m, &p);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        memset(adj, 0, sizeof(adj));
        for (int i = 0; i < m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            adj[u] ^= (1ll << v);
            adj[v] ^= (1ll << u);
        }
        printf("Case #%d: %d\n", tc, dfs((1ll << n) - 1));
    }
}
