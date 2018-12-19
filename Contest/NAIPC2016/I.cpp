#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int dep[maxn], fa[20][maxn];
vector<int> g[maxn];

void dfs(int x, int p) {
    fa[0][x] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        fa[i][x] = fa[i - 1][fa[i - 1][x]];
    for (const int &u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
    }
}

int lca(int x, int y) {
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = 19; i >= 0; --i) {
        if ((dep[y] - dep[x]) >> i & 1) {
            y = fa[i][y];
        }
    }
    if (x == y) return x;
    for (int i = 19; i >= 0; --i) {
        if (fa[i][x] != fa[i][y]) {
            x = fa[i][x];
            y = fa[i][y];
        }
    }
    if (x == y) return x;
    return fa[0][x];
}

int dist(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)] + 1;
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0, -1);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + i; j <= n; j += i) ans += dist(i - 1, j - 1);
    }
    printf("%lld\n", ans);
    return 0;
}
