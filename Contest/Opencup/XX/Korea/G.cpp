#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, s, t; scanf("%d%d%d%d", &n, &m, &s, &t);
    s--, t--;
    vector<vector<pair<int, int>>> g(n);
    vector<vector<int>> r(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c; scanf("%d%d%d", &u, &v, &c);
        u--, v--;
        g[u].emplace_back(v, c);
        r[v].push_back(u);
    }

    vector<int> vis(n);
    function<void(int)> Dfs = [&](int x) {
        vis[x] = 1;
        for (int u : r[x]) {
            if (!vis[u]) Dfs(u);
        }
    };

    Dfs(t);

    vector<int> vis2(n);
    vector<int> ans;

    function<void(int)> Dfs2 = [&](int x) {
        if (x == t) return;
        vis2[x] = 1;
        sort(g[x].begin(), g[x].end(), [&](auto a, auto b) { return a.second < b.second; });
        for (auto e : g[x]) {
            int u = e.first, w = e.second;
            if (vis[u]) {
                if (vis2[u]) {
                    puts("TOO LONG");
                    exit(0);
                }
                ans.push_back(w);
                Dfs2(u);
                break;
            }
        }
    };

    if (!vis[s]) {
        puts("IMPOSSIBLE");
        return 0;
    }

    Dfs2(s);
    for (int i = 0; i < ans.size(); ++i) printf("%d ", ans[i]);
    puts("");
}

