#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
int u[maxn], v[maxn], w[maxn];
int fa[maxn], dep[maxn], sz[maxn], to[maxn];
int fr[maxn], dfn[maxn], st[maxn * 4], tk;
vector<int> g[maxn];

void dfs(int x, int p) {
    dep[x] = ~p ? dep[p] + 1 : 0;
    fa[x] = p;
    sz[x] = 1;
    to[x] = -1;

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[u] > sz[to[x]]) swap(to[x], u);
    }
}

void hld(int x, int f) {
    fr[x] = f; dfn[x] = tk++;
    if (~to[x]) hld(to[x], f);

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == fa[x] || u == to[x]) continue;
        hld(u, u);
    }
}

void modify(int l, int r, int ql, int qr, int v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) return st[o] = min(st[o], v), void();
    modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
}

int query(int l, int r, int p, int o = 0) {
    if (r - l == 1) return st[o];
    if (p < (l + r) >> 1) return min(st[o], query(l, (l + r) >> 1, p, o * 2 + 1));
    else return min(st[o], query((l + r) >> 1, r, p, o * 2 + 2));
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < m; ++i) {
            scanf("%d%d%d", &u[i], &v[i], &w[i]);
            --u[i], --v[i];
            if (i < n - 1) {
                g[u[i]].push_back(v[i]);
                g[v[i]].push_back(u[i]);
            }
        }

        tk = 0;
        dfs(0, -1);
        hld(0, 0);

        for (int i = 0; i < 4 * n; ++i) st[i] = 1e9;

        for (int i = n - 1; i < m; ++i) {
            int x = u[i], y = v[i];
            int fx = fr[x], fy = fr[y];
            while (fx != fy) {
                if (dep[fx] < dep[fy]) {
                    swap(fx, fy);
                    swap(x, y);
                }
                modify(0, n, dfn[fx], dfn[x] + 1, w[i]);
                x = fa[fx];
                fx = fr[x];
            }
            if (dfn[x] > dfn[y]) swap(x, y);
            modify(0, n, dfn[x] + 1, dfn[y] + 1, w[i]);
        }

        int ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (dep[u[i]] < dep[v[i]]) swap(u[i], v[i]);
            int f = query(0, n, dfn[u[i]]);
            ans += max(0, w[i] - f);
        }
        printf("%d\n", ans);
    }
    return 0;
}
