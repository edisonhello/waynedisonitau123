#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

struct Q {
    int x, y, d;
};

vector<int> G[300005];
int pa[20][300005], dep[300005];
int LG;

void dfs(int now, int p, int d) {
    dep[now] = d;
    pa[0][now] = p;
    for (int i = 1; (1 << i) <= d; ++i) 
        pa[i][now] = pa[i - 1][pa[i - 1][now]];
    for (int i : G[now]) if (i != p) {
        dfs(i, now, d + 1);
    }
}

int lca(int u, int v) {
    if (dep[u] > dep[v]) swap(u, v);
    for (int i = LG; i >= 0; --i) if ((dep[v] - dep[u]) & (1 << i)) v = pa[i][v];
    if (u == v) return u;
    for (int i = LG; i >= 0; --i) if (pa[i][u] != pa[i][v]) u = pa[i][u], v = pa[i][v];
    return pa[0][u];
}

int get_pa(int u, int x) {
    for (int i = 0; (1 << i) <= x; ++i) if (x & (1 << i)) u = pa[i][u];
    return u;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while (t--) {
        int n, m; cin >> n >> m;
        LG = __lg(n);
        for (int i = 1; i <= n; ++i) G[i].clear();
        for (int i = 0; i <= LG; ++i) for (int j = 1; j <= n; ++j) pa[i][j] = 0;
        for (int i = 1; i < n; ++i) {
            int u, v; cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0, 0);
        vector<Q> qs;
        qs.reserve(m);
        int tsu = 1;
        while (m--) {
            // cout << "q" << endl;
            int x, y, d; cin >> x >> y >> d;
            if (tsu == -1) continue;
            qs.push_back(Q{x, y, d});
            int l = lca(x, y);
            int dxy = dep[x] + dep[y] - dep[l] * 2;
            if (dxy > d) {
                tsu = -1;
                continue;
            }
            if (dep[x] + dep[y] <= d) continue;
            int g = (d - dxy) / 2;
            int la = get_pa(l, g);
            // cout << "la = " << la << " , g = " << g << endl;
            if (dep[la] > dep[tsu]) tsu = la;
        }
        // cout << "tsu = " << tsu << endl;
        if (tsu == -1) {
            cout << "NIE\n";
            continue;
        }
        // for (int i = 0; i < 20; ++i) for (int j = 1; j <= n; ++j) pa[i][j] = 0;
        // dfs(tsu, 0, 0);
        bool ok = true;
        for (Q &q : qs) {
            int l1 = lca(q.x, tsu);
            int l2 = lca(q.y, tsu);
            int l = dep[q.x] + dep[tsu] - dep[l1] * 2 + dep[q.y] + dep[tsu] - dep[l2] * 2;
            if (l > q.d) { ok = false; break; }
        }
        if (ok) cout << "TAK " << tsu << "\n";
        else cout << "NIE\n";
    }
}
