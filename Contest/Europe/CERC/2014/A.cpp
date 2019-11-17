#include <bits/stdc++.h>
using namespace std;

const int kN = 1000 + 5;
vector<int> g[kN];
int dep[kN], fa[kN][20], s[kN], mk[kN];

void Dfs(int x, int p) {
    fa[x][0] = p;
    dep[x] = ~p ? dep[p] + 1 : 0;
    for (int i = 1; (1 << i) <= dep[x]; ++i)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs(u, x);
    }
}

void Dfs2(int x, int p, int ac = 0) {
    s[x] = ac + mk[x];
    for (int u : g[x]) {
        if (u == p) continue;
        Dfs2(u, x, s[x]);
    }
}

void Mark(int u, int v, int z) {
    for (int x = u; x != z; x = fa[x][0]) mk[x] = 1;
    for (int x = v; x != z; x = fa[x][0]) mk[x] = 1;
    Dfs2(0, -1);
}

int LCA(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = 0; i < 20; ++i) {
        if ((dep[v] - dep[u]) >> i & 1)
            v = fa[v][i];
    }
    if (u == v) return u;
    for (int i = 19; i >= 0; --i) {
        if (fa[u][i] != fa[v][i]) {
            u = fa[u][i];
            v = fa[v][i];
        }
    }
    return fa[u][0];
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 20; ++j)
                fa[i][j] = -1;
        }
        for (int i = 0; i < n; ++i) g[i].clear();
        for (int i = 0; i < n - 1; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        Dfs(0, -1);
        int m; scanf("%d", &m);
        vector<tuple<int, int, int>> qr;
        for (int i = 0; i < m; ++i) {
            int u, v; scanf("%d%d", &u, &v);
            --u, --v;
            qr.emplace_back(u, v, LCA(u, v));
        }
        sort(qr.begin(), qr.end(), [&](auto a, auto b) {
            return dep[get<2>(a)] > dep[get<2>(b)];
        });
        for (int i = 0; i < n; ++i) s[i] = mk[i] = 0;
        int ans = 0;
        for (auto &q : qr) {
            int u, v, z;
            tie(u, v, z) = q;
            if (s[u] - s[z] > 0 || s[v] - s[z] > 0) continue;
            Mark(u, v, z);
            ans += 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
