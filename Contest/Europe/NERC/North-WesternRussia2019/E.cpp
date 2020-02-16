#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> mark(n), sz(n), dep(n), dmk(n, -1), gd(n);
    for (int i = 0; i < m; ++i) {
        int v; scanf("%d", &v);
        mark[v - 1] = 1;
    }

    function<void(int, int)> Dfs = [&](int x, int p) {
        sz[x] = mark[x];
        dep[x] = ~p ? dep[p] + 1 : 0;
        if (mark[x]) dmk[x] = dep[x];
        gd[x] = 1;
        for (int u : g[x]) {
            if (u == p) continue;
            Dfs(u, x);
            gd[x] &= gd[u];
            if (dmk[u] != -1) {
                if (dmk[x] != -1 && dmk[u] != dmk[x]) gd[x] = 0;
            }
            dmk[x] = max(dmk[x], dmk[u]);
        }
    };

    int root = -1;
    for (int i = 0; i < n; ++i) {
        if (!mark[i]) root = i;
    }
    if (root == -1) {
        if (n == 1) printf("YES\n1\n");
        else printf("NO\n");
        return 0;
    }

    function<void(int, int, int)> Dfs2 = [&](int x, int p, int nd) {
        // printf("x = %d p = %d nd = %d\n", x, p, nd);
        if (gd[x] && (nd == -1 || dmk[x] == -1 || nd == dmk[x] - dep[x])) {
            puts("YES");
            printf("%d\n", x + 1);
            exit(0);
        } 
        multiset<int> s;
        int gdc = 0, ch = 0;
        for (int u : g[x]) {
            if (u == p) continue;
            if (gd[u]) {
                gdc++;
                if (dmk[u] != -1) s.insert(dmk[u] - dep[x]);
            }
            ch += 1;
        }
        for (int u : g[x]) {
            if (u == p) continue;
            int tnd = nd == -1 ? -1 : nd + 1;
            bool ok = true;
            if (mark[x]) {
                if (tnd == -1) tnd = 1;
                else ok = false;
            }
            if (!ok) continue;
            int kd = gdc - gd[u];
            if (kd == ch - 1) {
                if (dmk[u] != -1 && gd[u]) s.erase(s.find(dmk[u] - dep[x]));
                if (s.empty() || *s.begin() == *s.rbegin()) {
                    if (!s.empty()) {
                        int rnd = *s.begin() + 1;
                        if (tnd == -1) tnd = rnd;
                        else if (tnd != rnd) ok = false;
                    }
                    if (ok) Dfs2(u, x, tnd);
                }
                if (dmk[u] != -1 && gd[u]) s.insert(dmk[u] - dep[x]);
            }
        }
    };

    Dfs(root, -1);
    // for (int i = 0; i < n; ++i) printf("%d %d\n", gd[i], dmk[i]);
    Dfs2(root, -1, -1);
    puts("NO");
    return 0;
}

