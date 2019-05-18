#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
vector<int> g[maxn];
int sz[maxn], to[maxn], fa[maxn], fr[maxn], dep[maxn], md[maxn], cnt[maxn], ct[maxn], fe[maxn];
set<tuple<int, int, int>> seg[maxn];

void dfs(int x, int p) {
    sz[x] = 1;
    to[x] = -1;
    fa[x] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
    for (int u : g[x]) {
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[u] > sz[to[x]]) 
            to[x] = u;
    }
}

void hld(int x, int f) {
    fr[x] = f;
    if (to[x] == -1) return;
    hld(to[x], f);
    for (int u : g[x]) {
        if (u == fa[x]) continue;
        if (u == to[x]) continue;
        hld(u, u);
    }
}

void dec(int x, int y) {
    --ct[cnt[x]];
    cnt[x] -= y;
    ++ct[cnt[x]];
}

void inc(int x, int y) {
    --ct[cnt[x]];
    cnt[x] += y;
    ++ct[cnt[x]];
}

int main() {
    int n, c, q; scanf("%d%d%d", &n, &c, &q);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; scanf("%d%d", &x, &y);
        --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(0, -1);
    hld(0, 0);
    memset(md, -1, sizeof(md));
    for (int i = 0; i < n; ++i) md[fr[i]] = max(md[fr[i]], dep[i]);
    // for (int i = 0; i < n; ++i) printf("%d ", fr[i]); puts("");
    for (int i = 0; i < n; ++i) if (md[i] >= 0 && dep[i] != md[i]) seg[i].insert(make_tuple(dep[i], md[i], 0));
    cnt[0] = n - 1;
    ct[0] = c;
    ct[n - 1]++;
    while (q--) {
        int x, y, m; scanf("%d%d%d", &x, &y, &m);
        --x;
        while (x >= 0) {
            int f = fr[x];
            // printf("f = %d\n", f);
            vector<tuple<int, int, int>> seen;
            while ((int)seg[f].size() > 0) {
                auto it = seg[f].begin();
                if (get<0>(*it) >= dep[x]) break;
                seen.push_back(*it);
                seg[f].erase(it);
            }
            for (int i = 0; i < (int)seen.size(); ++i) {
                int l = get<0>(seen[i]);
                int r = get<1>(seen[i]);
                int cl = get<2>(seen[i]);
                // printf("l = %d r = %d cl = %d\n", l, r, cl);
                dec(cl, r - l);
                if (r > dep[x]) {
                    inc(cl, r - dep[x]);
                    seg[f].insert(make_tuple(dep[x], r, cl));
                }
            }
            inc(y, dep[x] - dep[f]);
            if (dep[f] < dep[x]) seg[f].insert(make_tuple(dep[f], dep[x], y));
            if (fa[f] >= 0) {
                dec(fe[f], 1);
                fe[f] = y;
                inc(fe[f], 1);
            }
            x = fa[f];
        }
        /* for (int i = 0; i <= c; ++i) printf("%d ", cnt[i]); puts("");
        puts("debug");
        for (int i = 0; i < n; ++i) {
            for (auto it : seg[i]) {
                printf("(%d, %d, %d) ", get<0>(it), get<1>(it), get<2>(it));
            }
            puts("");
        } */
        int ans = ct[m];
        if (cnt[0] == m) --ans;
        printf("%d\n", ans);
    }
}
