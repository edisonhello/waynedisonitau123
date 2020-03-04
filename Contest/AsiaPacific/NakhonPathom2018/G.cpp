#include <bits/stdc++.h>
using namespace std;

const int maxn = 200 + 5;
vector<int> g[maxn], r[maxn], tp;
bool v[maxn];
int scc[maxn];

void dfs(int x) {
    v[x] = true;
    for (int u : g[x]) {
        if (!v[u]) dfs(u);
    }
    tp.push_back(x);
}

void rdfs(int x, int z) {
    scc[x] = z;
    for (int u : r[x]) {
        if (scc[u] == -1) rdfs(u, z);
    }
}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n; scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            r[i].clear();
        }

        int m; scanf("%d", &m);
        while (m--) {
            int u, v; scanf("%d%d", &u, &v);
            g[u].push_back(v);
            r[v].push_back(u);
        }

        memset(v, false, sizeof(v));
        tp.clear();
        for (int i = 0; i < n; ++i) {
            if (!v[i]) dfs(i);
        }
        memset(scc, -1, sizeof(scc));
        int sz = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (scc[tp[i]] == -1) rdfs(tp[i], sz++);
        }
        printf("%d\n", sz);
    }
}
