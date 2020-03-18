#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> dep(n);
    vector<vector<int>> fa(n);

    function<void(int, int)> Dfs = [&](int x, int p) {
        fa[x].push_back(p);
        for (int i = 1; (1 << i) <= dep[x]; ++i) {
            fa[x].push_back(fa[fa[x][i - 1]][i - 1]);
        }
        for (int u : g[x]) {
            if (u == p) continue;
            dep[u] = dep[x] + 1;
            Dfs(u, x);
        }
    };

    Dfs(0, -1);

    auto GetLCA = [&](int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        for (int i = 0; i < fa[v].size(); ++i) {
            if ((dep[v] - dep[u]) >> i & 1) {
                v = fa[v][i];
            }
        }
        if (u == v) return u;
        for (int i = min(fa[u].size(), fa[v].size()) - 1; i >= 0; --i) {
            if (i < fa[u].size() && i < fa[v].size()) {
                if (fa[u][i] != fa[v][i]) {
                    u = fa[u][i];
                    v = fa[v][i];
                }
            }
        }
        return fa[u][0];
    };

    auto Dist = [&](int u, int v) {
        return dep[u] + dep[v] - 2 * dep[GetLCA(u, v)];
    };

    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int d = Dist(u, v) + 1;
        int64_t res = n - d + 1LL * (d + 1) * d / 2;
        cout << res << "\n";
    }
}


