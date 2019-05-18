#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 20;
vector<int> g[maxn], qr[maxn];
int n, q, fw[maxn], sz[maxn], kq[maxn], ans[maxn];

void dfs(int x, int p) {
    sz[x] = 1;
    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        dfs(u, x);
        sz[x] += sz[u];
    }
}

void add(int p, int v) {
    // printf("Add p = %d v = %d\n", p, v);
    for (int i = p; i < maxn; i += i & -i)
        fw[i] += v;
}

int find(int k) {
    int mask = 0;
    for (int i = 19; i >= 0; --i) {
        if (fw[mask | (1 << i)] <= k) {
            mask |= (1 << i);
            k -= fw[mask];
        }
    }
    return mask;
}

void dfs2(int x, int p) {
    add(sz[x], -1);
    add(n, 1);
    for (int i = 0; i < (int)qr[x].size(); ++i) {
        int k = kq[qr[x][i]];
        ans[qr[x][i]] = find(k - 1) + 1;
    }
    add(sz[x], 1);
    add(n, -1);

    for (int i = 0; i < (int)g[x].size(); ++i) {
        int u = g[x][i];
        if (u == p) continue;
        add(sz[x], -1);
        add(n - sz[u], 1);
        dfs2(u, x);
        add(sz[x], 1);
        add(n - sz[u], -1);
    }
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n - 1; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(0, -1);
    
    for (int i = 0; i < q; ++i) {
        int v; scanf("%d%d", &v, &kq[i]);
        qr[v - 1].push_back(i);
    }

    for (int i = 0; i < n; ++i)
        add(sz[i], 1);

    dfs2(0, -1);
    for (int i = 0; i < q; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
