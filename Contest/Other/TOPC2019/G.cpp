#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<int> g[maxn];
vector<int> tr[maxn];
vector<int> tt[maxn];
int dist[maxn], dep[maxn], deg[maxn];

set<pair<int, int>> ed;

void dfs(int x, int p) {
    for (int i = 0; i < (int)tr[x].size(); ++i) {
        for (int j = i + 1; j < (int)tr[x].size(); ++j)
            ed.insert(minmax(tr[x][i], tr[x][j]));
    }
    for (int u : tr[x]) {
        // printf("tree edge %d -> %d\n", x, u);
        ed.insert(minmax(x, u));
        for (int z : tr[u]) {
            // printf("cross %d -> %d\n", x, z);
            ed.insert(minmax(x, z));
        }
        dfs(u, x);
    }
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &deg[i]);
            g[i].clear();
            dist[i] = -1;
            for (int j = 0; j < deg[i]; ++j) {
                int u; scanf("%d", &u);
                --u;
                g[i].push_back(u);
            }
        }
        int r = -1;
        for (int i = 0; i < n; ++i) {
            if (r == -1 || deg[i] < deg[r]) r = i;
        }
        assert(deg[r] <= 3);

        queue<int> q;
        q.push(r);
        dist[r] = 0;
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int u : g[x]) {
                if (dist[u] == -1) {
                    dist[u] = dist[x] + 1;
                    q.push(u);
                }
            }
        }
        vector<int> e;
        bool ok = false;
        for (int i = 0; i < n; ++i) {
            if (dist[i] >= 2) {
                int c = 0;
                for (int u : g[i]) {
                    if (dist[u] == dist[i] - 1) ++c;
                }
                if (c == 1) dep[i] = 2 * dist[i];
                else dep[i] = 2 * dist[i] - 1;
            } else {
                if (dist[i] == 1) e.push_back(i);
            }
        }
        int m = (int)e.size();
        assert(m <= 3);
        dep[r] = 0;
        for (int s = 0; s < (1 << m); ++s) {
            for (int i = 0; i < m; ++i) {
                if (s >> i & 1) dep[e[i]] = 1;
                else dep[e[i]] = 2;
            }
            for (int i = 0; i < n; ++i) tr[i].clear();
            for (int i = 0; i < n; ++i) {
                for (int u : g[i]) if (dep[u] == dep[i] - 1) tr[u].push_back(i);
            }
            ed.clear();
            dfs(r, -1);
            bool fl = false;
            for (int i = 0; !fl && i < n; ++i) {
                for (int u : g[i]) {
                    if (i < u) {
                        if (ed.count(make_pair(i, u)) == 0) {
                            // printf("no (%d, %d)\n", i, u);
                            fl = true;
                        }
                        ed.erase(make_pair(i, u));
                    }
                }
            }
            if (!fl && ed.empty()) {
                for (int i = 0; i < n; ++i) tt[i].clear();
                for (int i = 0; i < n; ++i) {
                    for (int u : tr[i]) {
                        tt[i].push_back(u);
                        tt[u].push_back(i);
                    }
                }
                for (int i = 0; i < n; ++i) {
                    printf("%d", (int)tt[i].size());
                    sort(tt[i].begin(), tt[i].end());
                    for (int j = 0; j < (int)tt[i].size(); ++j) 
                        printf(" %d", tt[i][j] + 1);
                    puts("");
                }
                ok = true;
                break;
            }
        }
        assert(ok);
    }
    return 0;
}
