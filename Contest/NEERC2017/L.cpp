#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 5;
vector<int> g[maxn];
int dep[maxn], sz[maxn], to[maxn], fa[maxn], fr[maxn], dfn[maxn], tk;

void dfs(int x, int p) {
    dep[x] = ~p ? dep[p] + 1 : dep[x];
    sz[x] = 1;
    to[x] = -1;
    fa[x] = p;
    for (const int &u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[to[x]] < sz[u]) to[x] = u;
    }
}

void hld(int x, int t) {
    fr[x] = t;
    dfn[x] = tk++;
    if (!~to[x]) return;
    hld(to[x], t);
    for (const int &u : g[x]) {
        if (u == fa[x] || u == to[x]) continue;
        hld(u, u);
    }
}

int lca(int x, int y) {
    int fx = fr[x], fy = fr[y];
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        x = fa[fx];
        fx = fr[x];
    }
    if (x == y) return x;
    return dep[x] < dep[y] ? x : y;
}

int dist(int x, int y) {
    return dep[x] + dep[y] - 2 * dep[lca(x, y)];
}

/* pair<int, int> merge(pair<int, int> x, pair<int, int> y) {
    if (x.first == -1) return make_pair(-1, 0);
    if (y.first == -1) return make_pair(-1, 0);
    if (x.first == 0 && x.second) return make_pair(y.first, 1);
    if (y.first == 0 && y.second) return make_pair(x.first, 1);
    if (x.first == 0 && !x.second) return make_pair(y.first, 0);
    if (y.first == 0 && !y.second) return make_pair(x.first, 0);
    if (x.first != y.first) return make_pair(-1, 0);
    if (x.second || y.second) return make_pair(x.first, 1);
    return make_pair(x.first, 0);
} */

int merge(int x, int y) {
    if (x == -1) return -1;
    if (y == -1) return -1;
    if (x != y) return -1;
    return x;
}

namespace segtree {
    int color[maxn * 4];
    int tg[maxn * 4];
    void init() {
        memset(color, 0, sizeof(color));
        memset(tg, 0, sizeof(tg));
    }
    void push(int o) {
        if (tg[o] == 0) return;
        color[o * 2 + 1] = tg[o];
        color[o * 2 + 2] = tg[o];
        tg[o * 2 + 1] = tg[o];
        tg[o * 2 + 2] = tg[o];
        tg[o] = 0;
    }
    void modify(int l, int r, int ql, int qr, int v, int o = 0) {
        // if (o == 0) printf("ql = %d qr = %d v = %d\n", ql, qr, v);
        if (r - l > 1) push(o);
        if (l >= qr || ql >= r) return;
        if (l >= ql && r <= qr) return color[o] = v, tg[o] = v, void();
        modify(l, (l + r) >> 1, ql, qr, v, o * 2 + 1);
        modify((l + r) >> 1, r, ql, qr, v, o * 2 + 2);
        color[o] = merge(color[o * 2 + 1], color[o * 2 + 2]);
    }
    int query(int l, int r, int ql, int qr, int o = 0) {
        if (r - l > 1) push(o);
        if (l >= ql && r <= qr) return color[o];
        if (qr <= (l + r) >> 1) return query(l, (l + r) >> 1, ql, qr, o * 2 + 1);
        if (ql >= (l + r) >> 1) return query((l + r) >> 1, r, ql, qr, o * 2 + 2);
        return merge(query(l, (l + r) >> 1, ql, qr, o * 2 + 1),
                     query((l + r) >> 1, r, ql, qr, o * 2 + 2));
    }
}

vector<pair<int, int>> get(int x, int y) {
    int fx = fr[x], fy = fr[y];
    vector<pair<int, int>> res;
    while (fx != fy) {
        if (dep[fx] < dep[fy]) {
            swap(fx, fy);
            swap(x, y);
        }
        res.emplace_back(dfn[fx], dfn[x] + 1);
        x = fa[fx];
        fx = fr[x];
    }
    res.emplace_back(min(dfn[x], dfn[y]), max(dfn[x], dfn[y]) + 1);
    return res;
}

int main() {
    int n, f; scanf("%d%d", &n, &f);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0, -1);
    hld(0, 0);
    /* for (int i = 0; i < n; ++i) printf("%d ", dep[i]); puts("");
    for (int i = 0; i < n; ++i) printf("%d ", dfn[i]); puts("");
    for (int i = 0; i < n; ++i) printf("%d ", fr[i]); puts("");
    for (int i = 0; i < n; ++i) printf("%d ", fa[i]); puts("");
    for (int i = 0; i < n; ++i) printf("%d ", to[i]); puts(""); */
    vector<pair<int, int>> qf;
    for (int i = 0; i < f; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        qf.emplace_back(x, y);
    }
    sort(qf.begin(), qf.end(), [&](pair<int, int> i, pair<int, int> j) {
        return dist(i.first, i.second) > dist(j.first, j.second);
    });
    segtree::init();
    int paint = 0;
    for (int i = 0; i < f; ++i) {
        int x, y; tie(x, y) = qf[i];
        // printf("x = %d y = %d\n", x, y);
        vector<pair<int, int>> v = get(x, y);
        // for (int j = 0; j < (int)v.size(); ++j) printf("%d %d\n", v[j].first, v[j].second);
        int color = segtree::query(0, n, v[0].first, v[0].second);
        for (int j = 1; j < (int)v.size(); ++j) color = merge(color, segtree::query(0, n, v[j].first, v[j].second));
        // printf("color = %d\n", color);
        if (color == -1) {
            puts("No");
            return 0;
        }
        paint++;
        for (int j = 0; j < (int)v.size(); ++j) segtree::modify(0, n, v[j].first, v[j].second, paint);
    }
    puts("Yes");
    return 0;
}

