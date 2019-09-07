#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 5;
vector<int> g[maxn];
int sz[maxn], to[maxn], fa[maxn], fr[maxn], dep[maxn];
set<pair<int, int>> mark[maxn];
char cmd[4];

void dfs(int x) {
    sz[x] = 1, to[x] = -1;
    if (fa[x] != -1) dep[x] = dep[fa[x]] + 1;
    for (int u : g[x]) {
        dfs(u);
        sz[x] += sz[u];
        if (to[x] == -1 || sz[to[x]] < sz[u]) to[x] = u;
    }
}

void hld(int x, int f) {
    fr[x] = f;
    if (to[x] != -1) hld(to[x], f);
    for (int u : g[x]) {
        if (u == to[x]) continue;
        hld(u, u);
    }
}

int main() {
    int n, q; scanf("%d%d", &n, &q);
    fa[0] = -1;
    for (int i = 1; i < n; ++i) {
        int p; scanf("%d", &p); --p;
        g[p].push_back(i);
        fa[i] = p;
    }

    dfs(0), hld(0, 0);
    mark[0].insert(make_pair(0, 0));

    long long ans = 0;

    while (q--) {
        int v; scanf("%d", &v);
        scanf("%s%d", cmd, &v), --v;
        if (cmd[0] == 'M') {
            mark[fr[v]].insert(make_pair(dep[v], v));
        } else {
            int z = -1;
            while (v != -1) {
                auto it = mark[fr[v]].upper_bound(make_pair(dep[v], 1e9));
                if (it != mark[fr[v]].begin()) {
                    it = prev(it);
                    if (z == -1 || dep[z] < it->first) {
                        z = it->second;
                    }
                }
                v = fa[fr[v]];
            }
            assert(z != -1);
            ans += z + 1;
        }
    }
    printf("%lld\n", ans);
}
