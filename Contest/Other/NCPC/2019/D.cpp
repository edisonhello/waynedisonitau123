#include <bits/stdc++.h>
using namespace std;

const int maxn = 500 + 5;
int adj[maxn][maxn];
vector<int> g[maxn];

namespace matching {

int fa[maxn], pre[maxn], match[maxn], s[maxn], v[maxn];
vector<int> g[maxn];
queue<int> q;

void init(int n) {
    for (int i = 0; i <= n; ++i) match[i] = pre[i] = n;
    for (int i = 0; i < n; ++i) g[i].clear();
}

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

int find(int u) {
    if (u == fa[u]) return u;
    return fa[u] = find(fa[u]);
}

int lca(int x, int y, int n) {
    static int tk = 0;
    ++tk;
    x = find(x), y = find(y);
    for (; ; swap(x, y)) {
        if (x != n) {
            if (v[x] == tk) return x;
            v[x] = tk;
            x = find(pre[match[x]]);
        }
    }
}

void blossom(int x, int y, int l) {
    while (find(x) != l) {
        pre[x] = y;
        y = match[x];
        if (s[y] == 1) {
            q.push(y);
            s[y] = 0;
        }
        if (fa[x] == x) fa[x] = l;
        if (fa[y] == y) fa[y] = l;
        x = pre[y];
    }
}

bool bfs(int r, int n) {
    for (int i = 0; i <= n; ++i) {
        fa[i] = i;
        s[i] = -1;
    }
    while (!q.empty()) q.pop();
    q.push(r);
    s[r] = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int u : g[x]) {
            if (s[u] == -1) {
                pre[u] = x;
                s[u] = 1;
                if (match[u] == n) {
                    for (int a = u, b = x, last; b != n; a = last, b = pre[a]) {
                        last = match[b];
                        match[b] = a;
                        match[a] = b;
                    }
                    return true;
                }
                q.push(match[u]);
                s[match[u]] = 0;
            } else if (!s[u] && find(u) != find(x)) {
                int l = lca(u, x, n);
                blossom(x, u, l);
                blossom(u, x, l);
            }
        }
    }
    return false;
}

int solve(int n) {
    int res = 0;
    for (int x = 0; x < n; ++x) {
        if (match[x] == n) res += bfs(x, n);
    }
    return res;
}

}

int main() {
    int t; scanf("%d", &t);
    while (t--) {
        int n, m; scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                adj[i][j] = 0;
        }
        for (int i = 0; i < m; ++i) {
            int x, y; scanf("%d%d", &x, &y);
            adj[x][y] = adj[y][x] = 1;
        }
        matching::init(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (i != j && !adj[i][j]) {
                    matching::add_edge(i, j);
                }
            }
        }
        int mk = matching::solve(n);
        printf("%d\n", mk + n - 2 *  mk);
    }
}
