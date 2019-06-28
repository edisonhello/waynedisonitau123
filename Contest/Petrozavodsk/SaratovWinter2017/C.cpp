#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<int> g[maxn];
int fa[maxn][20], dep[maxn];
int a[maxn], b[maxn], c[maxn];
int tin[maxn], tout[maxn];
int st[maxn * 4], tg[maxn * 4];

void dfs(int x, int p) {
    dep[x] = ~p ? dep[p] + 1 : 0;
    static int tk = 0;
    tin[x] = tk++;

    fa[x][0] = p;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
    }

    tout[x] = tk;
}

void push(int o) {
    st[o * 2 + 1] += tg[o];
    tg[o * 2 + 1] += tg[o];
    st[o * 2 + 2] += tg[o];
    tg[o * 2 + 2] += tg[o];
    tg[o] = 0;
}

void modify(int l, int r, int ql, int qr, int v, int o = 0) {
    if (l >= qr || ql >= r) return;
    if (l >= ql && r <= qr) {
        st[o] += v;
        tg[o] += v;
        return;
    }

    push(o);

    modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
    modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
}

int query(int l, int r, int p, int o = 0) {
    if (r - l == 1)
        return st[o];

    push(o);

    if (p < (l + r) >> 1)
        return query(l, (l + r) >> 1, p, o * 2 + 1);
    else
        return query((l + r) >> 1, r, p, o * 2 + 2);
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = 0; i < 20; ++i) {
        if ((dep[v] - dep[u]) >> i & 1)
            v = fa[v][i];
    }

    if (u == v)
        return u;

    for (int i = 19; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) g[i].clear();

    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 20; ++j)
            fa[i][j] = -1;
    }

    dfs(0, -1);

    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &a[i], &b[i]);
        --a[i], --b[i];
        c[i] = lca(a[i], b[i]);
    }

    vector<int> qr(m);
    iota(qr.begin(), qr.end(), 0);

    sort(qr.begin(), qr.end(), [&](int i, int j) {
        return dep[c[i]] > dep[c[j]];
    });

    vector<int> ans;

    for (int i = 0; i < m; ++i) {
        int j = qr[i];
        if (query(0, n, tin[a[j]]) || query(0, n, tin[b[j]])) continue;
        ans.push_back(c[j]);
        modify(0, n, tin[c[j]], tout[c[j]], 1);
    }

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < (int)ans.size(); ++i)
        printf("%d ", ans[i] + 1);
    puts("");
    return 0;
}
