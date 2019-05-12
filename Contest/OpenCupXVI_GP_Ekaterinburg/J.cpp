#include <bits/stdc++.h>
using namespace std;

const int maxn = 150 + 5;
vector<pair<int, int>> g[maxn];
int a[maxn][maxn], lev[maxn];
bool v[maxn];

void dfs(int x) {
    v[x] = true;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i].first;
        int w = g[x][i].second;
        if (!v[u]) {
            lev[u] = lev[x] + w;
            dfs(u);
        }
    }
}

int main() {
    int n; scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            scanf("%d", &a[i][j]);
    }

    int m; scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int u, v, d; scanf("%d%d%d", &u, &v, &d);
        --u, --v;
        g[u].emplace_back(v, +d);
        g[v].emplace_back(u, -d);
    }

    for (int i = 0; i < n; ++i) {
        if (!v[i]) 
            dfs(i);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)g[i].size(); ++j) {
            int u = g[i][j].first;
            int w = g[i][j].second;
            if (lev[u] != lev[i] + w) {
                puts("Impossible");
                return 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf("%d ", a[i][j] + lev[j] - lev[i]);
        puts("");
    }
}
